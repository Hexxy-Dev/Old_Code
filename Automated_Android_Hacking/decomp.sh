#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd "$SCRIPT_DIR"

APK_PATH="$(realpath "./0.INPUT/$(ls './0.INPUT')")"
java -jar './TOOLS/apktool_2.9.0.jar' d -r -f "$APK_PATH" -o './2.UNPACK'

./TOOLS/jadx-1.4.7/bin/jadx "$APK_PATH" -d './3.DECOMP'
./TOOLS/jadx-1.4.7/bin/jadx "$APK_PATH" --show-bad-code -d './4.BAD_DECOMP'