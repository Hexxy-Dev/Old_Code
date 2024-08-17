#!/bin/bash

source './utils.sh'
#
#utils_ShowLogo ""
#
#function MockOutput() {
#    I=1
#    while true; do
#        echo "HMMMMMMM$I"
#        echo "ERR$I" >&2
#        I=$(( $I + 1 ))
#        sleep 0.1
#
#        if [ $I -gt 100 ]; then
#            break
#        fi
#    done
#}
#
##exec 2> '../TEMP/ERROR.log'
#
##MockOutput |& tee '../TEMP/test2.log' | utils_StdinNtail
##MockOutput | tee '../TEMP/test2.log' | utils_StdinNtail
#
##utils_ShowLogo "" "Done - Please Eject Install Media and Reboot"
#
#CONFIG_FILE="../TEMP/setup.conf"
#
#source './userPreferences.sh'
##userPreferences_getUserPreferences
#
#utils_ShowLogo "" "HMM" "" "HMM"
#
#NAME_OF_MACHINE="noom"
#echo -ne "127.0.0.1\tlocalhost\n::1\t\tlocalhost\n127.0.1.1\t$NAME_OF_MACHINE.localdomain\t$NAME_OF_MACHINE\n" > hmm.txt
#
##utils_ShowLogo "" "Please review the setup settings for your system"
##userPreferences_showFinalPreferences
#
#
#
#
setup_customDataDirs() {
    local links=('Downloads' 'Documents' 'Music' 'Videos' 'Pictures' 'Public' 'Games' 'Coding' 'Configs' 'Servers')

    for ((i = 0; i  < ${#links[@]}; ++i)); do
        #mkdir "/DATA/"
        echo "${links[i]}"
    done
}

setup_customDataDirs