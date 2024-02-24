#!/bin/bash

clear
#gcc -m32 -flto -Os -s -nostdlib -nostartfiles -fno-builtin -fno-ident -I. -fno-asynchronous-unwind-tables -ffreestanding -fuse-ld=gold -Wl,--gc-sections -Wl,--strip-all -g0  ./NoStdLib.c # -nostdinc -nostdinc++
gcc -m32 -Os -s -nostdlib -nostartfiles -fno-builtin -fno-ident -I. -fno-asynchronous-unwind-tables -ffreestanding -fuse-ld=gold -Wl,--gc-sections -Wl,--strip-all -g0 -S -o NoStdLib.s  ./NoStdLib.c
#gcc -m32 -Os -s -nostdlib -nostartfiles -fno-builtin -fno-ident -I. -fno-asynchronous-unwind-tables -ffreestanding -fuse-ld=gold -Wl,--gc-sections -Wl,--strip-all -g0 -S  ./NoStdLib.c
#-Wl,--file-alignment,16,--section-alignment,16
#gcc -m32 -Os -s -nostdlib -nostartfiles -fno-builtin -fno-ident -I. -c -o NoStdLib.coff ./NoStdLib.c # -nostdinc -nostdinc++
#gcc -m32 -Os -s -nostdlib -nostartfiles ./NoStdLib.c -S
objcopy --remove-section=.comment --remove-section=.note.gnu.property --remove-section=.note.gnu.build-id --remove-section=.note.gnu.gold-version a.out as.out
./as.out ; echo -ne "\nreturn: $?   size: $(wc -c < as.out) bytes\n"
objcopy -O binary as.out as.bin
#objcopy -I binary -O elf64-x86-64 -B i386:x86-64 as.bin as.elf