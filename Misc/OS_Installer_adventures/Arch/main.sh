#!/bin/bash
#exec 2> '../TEMP/ERROR.log'

cd "$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
source './utils.sh'

utils_ShowLogo ""

source './preconditions.sh'
preconditions_verifyScriptPreconditions

if [ ! -f $CONFIG_FILE ]; then
    touch -f $CONFIG_FILE
    source './userPreferences.sh'
    userPreferences_getUserPreferences |& tee './TEMP/userPrefs.log'
fi
if [ ! -f $CONFIG_FILE ]; then
    exit 0
fi

utils_ShowLogo ""

source "$CONFIG_FILE"

source './install.sh'
install_prepSetup |& tee './TEMP/install.log'

    mkdir -p /mnt/root/$CUSTOM_OS_NAME
    cp -R ${BASE_DIR} /mnt/root/
    arch-chroot /mnt chmod +x /root/$CUSTOM_OS_NAME/*.sh
    arch-chroot /mnt /root/$CUSTOM_OS_NAME/setup.sh |& tee './TEMP/setup.log'

    mkdir -p /mnt/home/$USERNAME/$CUSTOM_OS_NAME
    cp -R ${BASE_DIR} /mnt/home/$USERNAME
    arch-chroot /mnt chown -R "$USERNAME:$USERNAME" /home/$USERNAME/$CUSTOM_OS_NAME

umount -A --recursive /mnt

utils_ShowLogo "" "Done - Please Eject Install Media and Reboot" "" "AFTER REBOOT RUN:" "./$CUSTOM_OS_NAME/postboot.sh"