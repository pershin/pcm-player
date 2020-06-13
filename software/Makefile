# build
build: .build .avr-size

.build:
	mkdir -p "build"
	avr-gcc -Wall -Wextra -Os -g -fuse-linker-plugin -mmcu=atmega328p -o "build/pcm-player.elf" "display.c" "spi.S" "sd.c" "fat32.c" "main.S" "main.c"
	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 "build/pcm-player.elf" "build/pcm-player.eep"
	avr-objcopy -O ihex -R .eeprom "build/pcm-player.elf" "build/pcm-player.hex"

.avr-size:
	avr-size -A "build/pcm-player.elf"

# clean
clean:
	rm -f "build/pcm-player.eep"
	rm -f "build/pcm-player.elf"
	rm -f "build/pcm-player.hex"
