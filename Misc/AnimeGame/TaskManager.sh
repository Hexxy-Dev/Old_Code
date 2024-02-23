#!/bin/bash

function main() {
    local CompatTools=/home/hexxy/.local/share/Steam/compatibilitytools.d
    local CompatData=/home/hexxy/.local/share/Steam/steamapps/compatdata

    local prefix="/AnimeGame"
    local binary="taskmgr"

    local version=$(ls -vr $CompatTools | head -n 1)

    proton() {
        export STEAM_COMPAT_DATA_PATH=$CompatData$prefix
        export STEAM_COMPAT_CLIENT_INSTALL_PATH=/home/hexxy/.local/share/Steam

        /home/hexxy/.local/share/Steam/compatibilitytools.d/$version/proton "$@"
    }
    proton run "$binary"
}
main "$@"