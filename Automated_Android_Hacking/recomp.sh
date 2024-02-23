#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd "$SCRIPT_DIR"

rm -rf './1.OUTPUT'
mkdir './1.OUTPUT'

APK_PATH="$(realpath "./0.INPUT/$(ls './0.INPUT')")"
APK_NAME=$(basename -- "$APK_PATH")

java -jar './TOOLS/apktool_2.9.0.jar' b './2.UNPACK'

export PATH=${PATH}:/home/hexxy/Android/Sdk/build-tools/33.0.1/
zipalign -p -f 4 "./2.UNPACK/dist/$APK_NAME" "./2.UNPACK/dist/$APK_NAME"

java -jar './TOOLS/uber-apk-signer-1.3.0.jar' --skipZipAlign --apks './2.UNPACK/dist' --out './1.OUTPUT'

rm ./1.OUTPUT/*.idsig
mv ./1.OUTPUT/*.apk ./1.OUTPUT/$APK_NAME