#!/bin/bash

fullfile="$1"
filename=$(basename -- "$fullfile")
extension="${filename##*.}"
filename="${filename%.*}"

mkdir "./$filename"
mv "$fullfile" "./$filename/"
cd "./$filename"

case "$extension" in
    zip) 7z x "$fullfile"
        ;;
    7z) 7z x "$fullfile"
        ;;
    rar) unrar x "$fullfile"
        ;;
    *) echo "NOT IMPLEMENTED" ;;
esac