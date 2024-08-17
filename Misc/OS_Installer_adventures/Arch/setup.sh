#!/bin/bash
cd "$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
source './utils.sh'
source "$CONFIG_FILE"

setup_createUser() {
    utils_ShowLogo "" "Adding User"

    groupadd libvirt
    useradd -m -G wheel,libvirt -s /bin/bash $USERNAME 

    echo "$USERNAME:$PASSWORD" | chpasswd
    echo "root:$ROOT_PASSWORD" | chpasswd

    echo $NAME_OF_MACHINE > /etc/hostname

    # Add sudo rights
    sed -i 's/^# %wheel ALL=(ALL) ALL/%wheel ALL=(ALL) ALL/' /etc/sudoers
    sed -i 's/^# %wheel ALL=(ALL:ALL) ALL/%wheel ALL=(ALL:ALL) ALL/' /etc/sudoers
}

setup_enableNetwork() {
    utils_ShowLogo "" "Network Setup"
    utils_pacmanInstall networkmanager dhclient #########################################
    systemctl enable --now NetworkManager
    echo -ne "127.0.0.1\tlocalhost\n::1\t\tlocalhost\n127.0.1.1\t$NAME_OF_MACHINE.localdomain\t$NAME_OF_MACHINE\n" > /etc/hosts
}

setup_prepOptimisations() {
    nc=$(grep -c ^processor /proc/cpuinfo)
    utils_ShowLogo "" "You have $nc cores." "Changing the makeflags for $nc cores. Aswell as" "changing the compression settings."
    
    #######################################################################################
        #network-manager-applet wpa-supplicant dialog os-prober mtools dosfstools linux-headers
    utils_pacmanInstall pacman-contrib reflector curl rsync arch-install-scripts git

    sed -i "s/#MAKEFLAGS=\"-j2\"/MAKEFLAGS=\"-j$nc\"/g" /etc/makepkg.conf
    sed -i "s/COMPRESSXZ=(xz -c -z -)/COMPRESSXZ=(xz -c -T $nc -z -)/g" /etc/makepkg.conf

    utils_setPacmanParallel
    sed -i "/\[multilib\]/,/Include/"'s/^#//' /etc/pacman.conf
    utils_pacmanInstall -yyu
}

setup_installMicrocode() {
    utils_ShowLogo "" "Installing Microcode"
    proc_type=$(lscpu)
    if grep -E "GenuineIntel" <<< ${proc_type}; then
        utils_ShowLogo "" "Installing Microcode" "Installing Intel microcode"
        utils_pacmanInstall intel-ucode
        proc_ucode=intel-ucode.img
    elif grep -E "AuthenticAMD" <<< ${proc_type}; then
        utils_ShowLogo "" "Installing Microcode" "Installing AMD microcode"
        utils_pacmanInstall amd-ucode
        proc_ucode=amd-ucode.img
    fi
}

setup_bootLoader() {
    utils_ShowLogo "" "Prepping the BootLoader"
    local partition="${DISK}"
    if [[ "${DISK}" =~ "nvme" ]]; then
        partition="${partition}p"
    fi
    partition="${partition}2" # ROOT PARTITION
    bootctl install

    echo -ne "default arch-*" > $BOOT_PATH/loader/loader.conf
    echo -ne "title\t$CUSTOM_OS_NAME\nlinux\t/vmlinuz-linux\ninitrd\t/initramfs-linux.img\ninitrd\t/$proc_ucode\noptions\troot=$partition rw" > $BOOT_PATH/loader/entries/arch.conf
    if [ $BOOT_PATH = "/efi" ]; then
        echo "ERROR: FEATURE MISSING: EFI PARTITION"
        exit
    fi
}

setup_customDataDirs() {
    utils_ShowLogo "" "Setting up symlinks"
    local links=('Downloads' 'Documents' 'Music' 'Videos' 'Pictures' 'Public' 'Games' 'Coding' 'Configs' 'Servers')

    mkdir -p "/home/$USERNAME"
    for ((i = 0; i  < ${#links[@]}; ++i)); do
        mkdir "/DATA/${links[i]}"
        ln -s "/DATA/${links[i]}" "/home/$USERNAME/${links[i]}"
    done
    chown "$USERNAME:$USERNAME" -R /DATA/
    chown "$USERNAME:$USERNAME" -R "/home/$USERNAME/"
}

setup_main() {
    setup_createUser
    setup_enableNetwork
    setup_prepOptimisations
    setup_installMicrocode
    setup_bootLoader
    setup_customDataDirs
}
setup_main