#!/bin/bash
#exec 2> '../TEMP/ERROR.log'

cd "$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
source './utils.sh'

utils_ShowLogo ""

utils_verifyScriptPreconditions

if [ ! -f $CONFIG_FILE ]; then
    touch -f $CONFIG_FILE
    source './userPreferences.sh'
    userPreferences_getUserPreferences |& tee './TEMP/userPrefs.log'
fi

utils_ShowLogo ""

source "$CONFIG_FILE"

source './install.sh'
install_prepSetup |& tee './TEMP/install.log'

    cp -R ${BASE_DIR} /mnt/root/$CUSTOM_OS_NAME
    ( arch-chroot /mnt chmod +x /root/HexxyOS/*.sh )
    ( arch-chroot /mnt /root/HexxyOS/setup.sh )|& tee './TEMP/setup.log'

    mkdir -p /mnt/home/$USERNAME/$CUSTOM_OS_NAME
    cp -R ${BASE_DIR} /mnt/home/$USERNAME

umount -A --recursive /mnt

utils_ShowLogo "" "Done - Please Eject Install Media and Reboot" "" "AFTER REBOOT RUN:" "sudo ./$CUSTOM_OS_NAME/postboot.sh"