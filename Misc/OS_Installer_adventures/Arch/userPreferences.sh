#!/bin/bash
cd "$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
source './utils.sh'

userPreferences_getPassword() {
    local PASSWORD1
    local PASSWORD2
    IFS= read -rs -p "Please enter $1: " PASSWORD1 2>&1
    echo -ne "\n"
    IFS= read -rs -p "Please re-enter $1: " PASSWORD2 2>&1
    echo -ne "\n"
    if [[ "$PASSWORD1" == "$PASSWORD2" ]]; then
        utils_setOption "$1" "$PASSWORD1"
    else
        echo -ne "ERROR! Passwords do not match. \n"
        userPreferences_getPassword
    fi
}

userPreferences_getUserinfo() {
    local username
    read -p "Please enter your username: " username 2>&1
    utils_setOption 'USERNAME' "${username,,}"
    
    userPreferences_getPassword 'PASSWORD'
    
    local nameofmachine
    read -rep "Please enter your hostname: " nameofmachine 2>&1
    utils_setOption 'NAME_OF_MACHINE' "$nameofmachine"


    userPreferences_getPassword 'ROOT_PASSWORD'
}

userPreferences_getDisk() {
    echo -e "
--------------------------------------------------------------------------
    THIS WILL FORMAT AND DELETE ALL DATA ON THE DISK
    Please make sure you know what you are doing because
    after formating your disk there is no way to get data back
--------------------------------------------------------------------------

Select the disk to install on:\n"

    local options=($(lsblk -n --output TYPE,KNAME,SIZE | awk '$1=="disk"{print "/dev/"$2"|"$3}'))

    utils_selectColumnOption $? 1 "${options[@]}"
    local disk=${options[$?]%|*}

    echo -e "Try to preserve the DATA partition?? (if it exists??)\nWARNING: MAKE A BACKUP!!!!!!!"
    options=("Yes" "No")
    utils_selectColumnOption $? 1 "${options[@]}"
    local keep=${options[$?]%|*}

    echo -e "\n${disk%|*} selected \n"
    utils_setOption 'DISK' "${disk%|*}"
    utils_setOption 'MOUNT_OPTIONS' 'noatime,compress=zstd,ssd,commit=120'
    utils_setOption 'FS' 'ext4'
    utils_setOption 'TRY_KEEP_DATA' "${keep%|*}"
    utils_setOption 'BOOT_PATH' '/boot' #I'd much rather prefer /efi but we need to set up additional hooks for that
}

userPreferences_showFinalPreferences() {
    echo 'Final options:'
    grep -v 'PASSWORD' "$CONFIG_FILE"
    echo 'Is this correct?' 
    local options=("Yes" "No")
    utils_selectColumnOption $? 1 "${options[@]}"

    case ${options[$?]} in
        Yes) ;;
        No) rm -f "$CONFIG_FILE"
            echo 'ERROR: INSTALLATION ABORTED BY USER'
            exit 0
            ;;
    esac
}

userPreferences_getUserPreferences() {

    utils_setOption 'CUSTOM_OS_NAME' 'HexxyOS'

    utils_ShowLogo "" "Please configure the setup settings for your system"
    userPreferences_getUserinfo

    utils_setOption 'TIMEZONE' "$(curl --fail https://ipapi.co/timezone)"
    utils_setOption 'KEYMAP' 'us'

    utils_ShowLogo "" "Please select the setup settings for your system"
    userPreferences_getDisk

    utils_ShowLogo "" "Please review the setup settings for your system"
    userPreferences_showFinalPreferences
}



##SETUP IS WRONG THIS IS RUN
#if ! source $HOME/$CUSTOM_OS_NAME/configs/setup.conf; then
#	# Loop through user input until the user gives a valid username
#	while true
#	do 
#		read -p "Please enter username:" username
#		# username regex per response here https://unix.stackexchange.com/questions/157426/what-is-the-regex-to-validate-linux-users
#		# lowercase the username to test regex
#		if [[ "${username,,}" =~ ^[a-z_]([a-z0-9_-]{0,31}|[a-z0-9_-]{0,30}\$)$ ]]
#		then 
#			break
#		fi 
#		echo "Incorrect username."
#	done 
## convert name to lowercase before saving to setup.conf
#echo "username=${username,,}" >> ${HOME}/$CUSTOM_OS_NAME/configs/setup.conf
#
#    #Set Password
#    read -p "Please enter password:" password
#echo "password=${password,,}" >> ${HOME}/$CUSTOM_OS_NAME/configs/setup.conf
#
#    # Loop through user input until the user gives a valid hostname, but allow the user to force save 
#	while true
#	do 
#		read -p "Please name your machine:" name_of_machine
#		# hostname regex (!!couldn't find spec for computer name!!)
#		if [[ "${name_of_machine,,}" =~ ^[a-z][a-z0-9_.-]{0,62}[a-z0-9]$ ]]
#		then 
#			break 
#		fi 
#		# if validation fails allow the user to force saving of the hostname
#		read -p "Hostname doesn't seem correct. Do you still want to save it? (y/n)" force 
#		if [[ "${force,,}" = "y" ]]
#		then 
#			break 
#		fi 
#	done 
#
#    echo "NAME_OF_MACHINE=${name_of_machine,,}" >> ${HOME}/$CUSTOM_OS_NAME/configs/setup.conf
#fi