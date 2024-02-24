#!/bin/bash

clear
g++ -std=c++20 -m32 -flto -Os -s -nostdlib -nostartfiles -fno-builtin -fno-ident -I. -fno-asynchronous-unwind-tables -ffreestanding -fuse-ld=gold -Wl,--gc-sections -Wl,--strip-all -g0 ./NoStdLib.cpp # -nostdinc -nostdinc++
#g++ -std=c++20 -m32 -flto -Os -s -nostdlib -nostartfiles -fno-builtin -fno-ident -I. -fno-asynchronous-unwind-tables -ffreestanding -fuse-ld=gold -Wl,--gc-sections -Wl,--strip-all -g0 -E  ./NoStdLib.cpp
objcopy --remove-section=.comment --remove-section=.note.gnu.property --remove-section=.note.gnu.build-id --remove-section=.note.gnu.gold-version a.out as.out
./as.out ; echo -ne "\nreturn: $?   size: $(wc -c < as.out) bytes\n"
objcopy -O binary as.out as.bin