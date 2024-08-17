#!/bin/bash

#########################################
#                  WIP                  #
#  S H O U L D  B E  A V A I L A B L E  #
#         S Y S T E M  W I D E          #
#########################################
#maybe make it add itself to bashrc??  idk but this needs to be easly accessible

if [[ $(/usr/bin/id -u) -ne 0 ]]; then
	echo "Must run as root"
	exit
fi

#IDf=$(cat /etc/os-release | grep ID -m1)
#ID="${IDf:3}"
#
#if [[ "$ID" !=  "fedora"  ]]; then
#    echo "OS Not Supported OR Tested"
#    echo "Edit and run at your own risk!"
#    exit
#fi

current=$(pwd)

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd $SCRIPT_DIR

find . -type f -iname "*.sh" -exec chmod +x {} \;

source ./utils.sh
source ./installers.sh

while getopts 'FU' flag; do
  case "${flag}" in
    F)  echo "Installing custom Fedora Spin" 1>&2 #REDIRECT
        firstInstall_ALL
        optionals_ALL
        customInstalls_ALL
        utils_Update_ALL_Configs
        utils_Clean_Custom_Installs_Binaries
        ################
        #ONLY TEMPORARY#
        ################
        cp -r '../TEMP/oomox-Cyberpunk-Neon' "/home/$(logname)/.themes/"
        ################
        #ONLY TEMPORARY#
        ################ 
        echo "REBOOTING" 1>&2 #REDIRECT
        reboot
    ;;

    U)  utils_Update_ALL_Configs ;;
    
    *)  echo "Usage:"
        echo "FRESH INSTALL -F"
        echo "-U update all configs"
        ;;
  esac
done

#implement -u to update a certain custom install  ie remove previous and reinstall???? keep important files though

cd $current