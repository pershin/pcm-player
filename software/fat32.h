/*
 * File:   fat32.h
 * Author: Sergey Pershin <sergey.pershin at hotmail.com>
 *
 * Created on May 8, 2020, 7:39 PM
 */

#ifndef FAT32_H
#define FAT32_H

#include <stdint.h>

/* BPB (BIOS Parameter Block) structure for FAT32 volumes */
typedef struct {
  uint8_t BS_jmpBoot[3];
  uint8_t BS_OEMName[8];
  uint16_t BPB_BytsPerSec;
  uint8_t BPB_SecPerClus;
  uint16_t BPB_RsvdSecCnt;
  uint8_t BPB_NumFATs;
  uint16_t BPB_RootEntCnt;
  uint16_t BPB_TotSec16;
  uint8_t BPB_Media;
  uint16_t BPB_FATSz16;
  uint16_t BPB_SecPerTrk;
  uint16_t BPB_NumHeads;
  uint32_t BPB_HiddSec;
  uint32_t BPB_TotSec32;
  uint32_t BPB_FATSz32;
  uint16_t BPB_ExtFlags;
  uint16_t BPB_FSVer;
  uint32_t BPB_RootClus;
  uint16_t BPB_FSInfo;
  uint16_t BPB_BkBootSec;
  uint8_t BPB_Reserved[12];
  uint8_t BS_DrvNum;
  uint8_t BS_Reserved1;
  uint8_t BS_BootSig;
  uint32_t BS_VolID;
  uint8_t BS_VolLab[11];
  uint8_t BS_FilSysType[8];
  uint8_t Reserved[420];
  uint16_t Signature_word;
} BPB32_structure; /* 512 bytes */

/* Directory Structure */
typedef struct {
  uint8_t DIR_Name[11];
  uint8_t DIR_Attr;
  uint8_t DIR_NTRes;
  uint8_t DIR_CrtTimeTenth;
  uint16_t DIR_CrtTime;
  uint16_t DIR_CrtDate;
  uint16_t DIR_LstAccDate;
  uint16_t DIR_FstClusHI;
  uint16_t DIR_WrtTime;
  uint16_t DIR_WrtDate;
  uint16_t DIR_FstClusLO;
  uint32_t DIR_FileSize;
} Directory_Structure; /* 32 bytes */

/* File/Directory Attributes */
#define ATTR_READ_ONLY 0x01
#define ATTR_HIDDEN    0x02
#define ATTR_SYSTEM    0x04
#define ATTR_VOLUME_ID 0x08
#define ATTR_DIRECTORY 0x10
#define ATTR_ARCHIVE   0x20

typedef struct {
  uint16_t BPB_BytsPerSec;
  uint8_t BPB_SecPerClus;
  uint16_t BPB_RsvdSecCnt;
  uint32_t BPB_RootClus;
  uint32_t FATSz;
  uint32_t CountofClusters;
  uint32_t FAT_start_sector;
  uint32_t FirstDataSector;
  uint32_t current_cluster;
} FAT32_FS;

typedef struct {
  uint32_t filesize;
  uint32_t file_position;
} FAT32_FILE;

FAT32_FS fat32_fs;
FAT32_FILE fat32_file;

uint8_t fat32_mount(void);
uint32_t get_sector_by_cluster(uint32_t cluster);
uint8_t next_cluster(void);
uint8_t file_open(uint16_t file_num);
int16_t file_read(void *);

#endif /* FAT32_H */
