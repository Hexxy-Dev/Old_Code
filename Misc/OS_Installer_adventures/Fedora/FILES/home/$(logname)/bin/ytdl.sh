#!/bin/bash
if [ $# -lt 4 ]; then
    echo "Missing arguments. uage: url fileName artist isNightcore(y/n) album?"
    exit
fi
#echo "1:$1 2:$2 3:$3 4:$4 5:$5"

yt-dlp --prefer-ffmpeg --extract-audio --audio-format mp3 $1 -o "$2"
eyeD3 -a "$3" -t "$2" "$2.mp3"
if [ $4 == "y" ];then
    eyeD3 --non-std-genres -G "Nightcore" "$2.mp3"
fi
if [ $# -gt 4 ]; then
    eyeD3 -A "$5" "$2.mp3"
fi

read -p "Press key to continue.. " -n1 -s

mv "$2.mp3" ~/Music/ 