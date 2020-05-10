/*
 * File:   fat32.c
 * Author: Sergey Pershin <sergey.pershin at hotmail.com>
 *
 * Created on May 8, 2020, 7:39 PM
 */

#include "player.h"
#include "sd.h"
#include "fat32.h"

uint8_t buffer[BUFFER_SIZE];
uint8_t temp_buffer[512];

uint8_t fat32_mount(void) {
  uint32_t sector, RootDirSectors, TotSec, DataSec;
  BPB32_structure *bpb32;

  if (sd_read(buffer, 0)) {
    return 1;
  }

  sector = buffer[454 + 3];
  sector = sector << 8 | buffer[454 + 2];
  sector = sector << 8 | buffer[454 + 1];
  sector = sector << 8 | buffer[454 + 0];

  bpb32 = (BPB32_structure *) buffer;

  if (sd_read(buffer, sector)) {
    return 1;
  }

  /* First, determine the count of sectors occupied by the root directory: */
  RootDirSectors = ((bpb32->BPB_RootEntCnt * 32) + (bpb32->BPB_BytsPerSec - 1)) / bpb32->BPB_BytsPerSec;

  /* Next, determine the count of sectors in the data region of the volume: */
  if (0 != bpb32->BPB_FATSz16) {
    fat32_fs.FATSz = bpb32->BPB_FATSz16;
  } else {
    fat32_fs.FATSz = bpb32->BPB_FATSz32;
  }

  if (0 != bpb32->BPB_TotSec16) {
    TotSec = bpb32->BPB_TotSec16;
  } else {
    TotSec = bpb32->BPB_TotSec32;
  }

  DataSec = TotSec - (bpb32->BPB_RsvdSecCnt + (bpb32->BPB_NumFATs * fat32_fs.FATSz) + RootDirSectors);

  /* Lastly, determine the count of clusters as: */
  fat32_fs.CountofClusters = DataSec / bpb32->BPB_SecPerClus;

  /* To determine the FAT type, the following algorithm is used: */
  if (fat32_fs.CountofClusters < 4085) {
    /* Volume is FAT12 */
    return 1;
  } else if (fat32_fs.CountofClusters < 65525) {
    /* Volume is FAT16 */
    return 1;
  } else {
    /* Volume is FAT32 */
  }

  fat32_fs.BPB_BytsPerSec = bpb32->BPB_BytsPerSec;
  fat32_fs.BPB_SecPerClus = bpb32->BPB_SecPerClus;
  fat32_fs.BPB_RsvdSecCnt = bpb32->BPB_RsvdSecCnt;
  fat32_fs.BPB_RootClus = bpb32->BPB_RootClus;
  fat32_fs.FAT_start_sector = sector + bpb32->BPB_RsvdSecCnt;
  fat32_fs.FirstDataSector = bpb32->BPB_RsvdSecCnt + (bpb32->BPB_NumFATs * fat32_fs.FATSz) + sector;

  return 0;
}

uint32_t get_sector_by_cluster(uint32_t cluster) {
  cluster -= 2;
  return cluster * fat32_fs.BPB_SecPerClus + fat32_fs.FirstDataSector;
}

uint8_t next_cluster(void) {
  uint16_t FATOffset, ThisFATEntOffset;
  uint32_t SectorNumber;

  FATOffset = fat32_fs.current_cluster * 4;
  ThisFATEntOffset = FATOffset % fat32_fs.BPB_BytsPerSec;

  SectorNumber = fat32_fs.FAT_start_sector + fat32_fs.current_cluster / 128;

  if (sd_read(temp_buffer, SectorNumber)) {
    return 1;
  }

  fat32_fs.current_cluster = temp_buffer[ThisFATEntOffset + 3];
  fat32_fs.current_cluster = fat32_fs.current_cluster << 8 | temp_buffer[ThisFATEntOffset + 2];
  fat32_fs.current_cluster = fat32_fs.current_cluster << 8 | temp_buffer[ThisFATEntOffset + 1];
  fat32_fs.current_cluster = fat32_fs.current_cluster << 8 | temp_buffer[ThisFATEntOffset + 0];
  fat32_fs.current_cluster = fat32_fs.current_cluster & 0x0FFFFFFF;

  return 0;
}

uint8_t file_open(uint16_t file_num) {
  uint8_t disk_result;
  uint16_t i, track;
  uint32_t sector;
  Directory_Structure *dir;

  track = 0;
  sector = get_sector_by_cluster(fat32_fs.BPB_RootClus);

  do {
    disk_result = sd_read(buffer, sector);

    for (i = 0; 512 > i; i += 32) {
      dir = (Directory_Structure *) & buffer[i];

      /* All directory entries following the current free entry are also free */
      if (0 == dir->DIR_Name[0]) {
        return 1;
      }

      /* The directory entry is free */
      if (0xE5 == dir->DIR_Name[0]) {
        continue;
      }

      /* Names cannot start with a space character */
      if (0x20 == dir->DIR_Name[0]) {
        continue;
      }

      if ('P' != dir->DIR_Name[8]) {
        continue;
      }

      if ('C' != dir->DIR_Name[9]) {
        continue;
      }

      if ('M' != dir->DIR_Name[10]) {
        continue;
      }

      /* Not a directory */
      if ((dir->DIR_Attr & ATTR_DIRECTORY)) {
        continue;
      }

      track++;

      if (track == file_num) {
        fat32_fs.current_cluster = dir->DIR_FstClusHI;
        fat32_fs.current_cluster <<= 16;
        fat32_fs.current_cluster |= dir->DIR_FstClusLO;
        fat32_file.filesize = dir->DIR_FileSize;
        fat32_file.file_position = 0;

        return 0;
      }
    }

    sector++;
  } while (0 == disk_result);

  return 1;
}

int16_t file_read(void *buffer) {
  uint8_t cs, *rbuff = buffer;
  uint16_t size;
  int16_t result;
  uint32_t sector, remain;

  sector = 0;
  result = 0;
  remain = fat32_file.filesize - fat32_file.file_position;
  size = BUFFER_CHUNK;

  if (size > remain) {
    size = (uint16_t) remain;
  }

  cs = (uint8_t) (fat32_file.file_position / 512 & (fat32_fs.BPB_SecPerClus - 1));

  if (!cs) {
    if (fat32_file.file_position != 0) {
      if (0 != next_cluster()) {
        return -1;
      }
    }

    if (fat32_fs.current_cluster <= 1) {
      return -1;
    }
  }

  sector = get_sector_by_cluster(fat32_fs.current_cluster);
  sector += cs;

  result = 512;

  if (512 > size) {
    result = size;
  }

  if (0 != sd_read(rbuff, sector)) {
    return -1;
  }

  fat32_file.file_position += result;

  return result;
}
