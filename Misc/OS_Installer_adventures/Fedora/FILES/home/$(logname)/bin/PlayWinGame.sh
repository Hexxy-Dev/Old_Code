#!/bin/bash

export STEAM_COMPAT_DATA_PATH=~/.local/share/Steam/steamapps/compatdata
export STEAM_COMPAT_CLIENT_INSTALL_PATH=~/.local/share/Steam
~/.local/share/Steam/compatibilitytools.d/GE-Proton7-49/proton run "$1"
