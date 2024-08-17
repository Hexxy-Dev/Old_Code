#!/bin/bash
cd "$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
source './utils.sh'
source "$CONFIG_FILE"
source './specificUtils.sh'

install_prepEnvironment() {
    utils_ShowLogo "" "Setting up mirrors for optimal download"

    timedatectl set-ntp true
    timedatectl set-timezone "$TIMEZONE"

    pacman-key --init
    utils_pacmanInstall -y archlinux-keyring

    utils_pacmanInstall pacman-contrib terminus-font
    setfont ter-k16n

    utils_setPacmanParallel
    utils_pacmanInstall reflector rsync

    #reflector -a 10 --sort rate -n 40 --save /etc/pacman.d/mirrorlist
    cp "$TEMP_DIR/mirrorlist" '/etc/pacman.d/mirrorlist'

    utils_ShowLogo "" "Installing Prerequisites"

    utils_pacmanInstall gptfdisk btrfs-progs glibc
}

install_prepDisk() {
    mkdir /mnt &>/dev/null # Hiding error message if any
    utils_ShowLogo "" "Formating Disk"

    umount -A --recursive /mnt # make sure everything is unmounted before we start

    if [ "${TRY_KEEP_DATA}" = "Yes" ]; then # THIS ASSUMES THAT YOU ARE REINSTALLING!!!!!!!!!!!
        parted ${DISK} -s rm $(utils_getPartitionNumberFromLabel "ROOT")
        parted ${DISK} -s rm $(utils_getPartitionNumberFromLabel "EFIBOOT")
    else
        wipefs --all ${DISK}
        sgdisk -Z ${DISK}
        sgdisk -o ${DISK}

        sgdisk -n 3:-10G:-0 --typecode=3:8300: --change-name=3:'DATA' ${DISK}
        #sgdisk -n 3:-700G:-0 --typecode=3:8300: --change-name=3:'DATA' ${DISK} # partition 3 (DATA Partition)
    fi

    sgdisk -n 1::+1G --typecode=1:ef00 --change-name=1:'EFIBOOT' ${DISK} # partition 1 (UEFI Boot Partition)
    sgdisk -n 2::-0 --typecode=2:8300 --change-name=2:'ROOT' ${DISK} # partition 2 (Root), default start, remaining

    partprobe ${DISK}
}

install_prepFileSystem() {
    utils_ShowLogo "" "Creating Filesystems"

    local partition="${DISK}"
    if [[ "${DISK}" =~ "nvme" ]]; then
        partition="${partition}p" #nvme0n1 -> nvme0n1p
    fi

    if [[ "${FS}" == "ext4" ]]; then
        mkfs.vfat -F32 -n "EFIBOOT" "${partition}1"  #sda -> sda1     nvme0n1p -> nvme0n1p1
        mkfs.ext4 -L ROOT "${partition}2"
        if [ ! "${TRY_KEEP_DATA}" = "Yes" ]; then
            mkfs.ext4 -L DATA "${partition}3"
        fi
    else
        exit 0
    fi

    mount -t ext4 -L ROOT /mnt

    mkdir -p /mnt$BOOT_PATH
    mount -t vfat -L EFIBOOT /mnt$BOOT_PATH

    mkdir -p /mnt/DATA
    mount -t ext4 -L DATA /mnt/DATA

    if ! grep -qs '/mnt' /proc/mounts; then
        utils_rebootWithTimer
    fi
}

install_prepArch() {
    utils_ShowLogo "" "Arch Install on Main Drive"

    pacstrap -K /mnt base base-devel linux linux-firmware sudo archlinux-keyring wget efibootmgr --noconfirm --needed
    
    #echo "keyserver hkp://keyserver.ubuntu.com" >> /mnt/etc/pacman.d/gnupg/gpg.conf   # there is no need for this as it is the default
    cp /etc/pacman.d/mirrorlist /mnt/etc/pacman.d/mirrorlist

    genfstab -U /mnt >> /mnt/etc/fstab
    echo "Generated /etc/fstab:"
    cat /mnt/etc/fstab
}

install_prepSetup() {
    install_prepEnvironment
    install_prepDisk
    install_prepFileSystem
    install_prepArch
}