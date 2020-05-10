# PCM Player

Pulse-width modulation (PWM) audio player on ATmega328P-PU

## Requirements

### SD card

SDHC 2-32GB must be formatted to FAT32

### Audio files

Property          | Value
------------------|----------------------------
| Format:         | Unsigned 8-bit PCM (RAW)  |
| Sample rate:    | 44100 kHz                 |
| Channels:       | 2                         |
| File extension: | *.PCM                     |

#### Convert FLAC to PCM with FFmpeg

```bash
ffmpeg -i 'example.flac' -ar 44100 -acodec pcm_u8 -f u8 -ac 2 'EXAMPLE.PCM'
```
