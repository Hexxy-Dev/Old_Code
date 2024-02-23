#!/bin/bash

function main() {

    cd '/home/hexxy/.local/share/Steam/steamapps/compatdata/AnimeGame/pfx/drive_c/Program Files/Genshin Impact'

    local CompatTools=/home/hexxy/.local/share/Steam/compatibilitytools.d
    local CompatData=/home/hexxy/.local/share/Steam/steamapps/compatdata

    local prefix="/AnimeGame"
    local binary="launcher.exe"

    local version=$(ls -vr $CompatTools | head -n 1)

    proton() {
        export STEAM_COMPAT_DATA_PATH=$CompatData$prefix
        export STEAM_COMPAT_CLIENT_INSTALL_PATH=/home/hexxy/.local/share/Steam

        /home/hexxy/.local/share/Steam/compatibilitytools.d/$version/proton "$@"
    }
    proton run "$binary"
}
main "$@"