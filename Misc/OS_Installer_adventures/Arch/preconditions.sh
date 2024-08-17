#!/bin/bash

preconditions_verifyIsRoot() {
    if [[ "$(id -u)" != "0" ]]; then
        echo "ERROR! This script must be run as the root user!"
        exit 0
    fi
}

preconditions_verifyIsDocker() {
    if awk -F/ '$2 == "docker"' /proc/self/cgroup | read -r; then
        echo -ne "ERROR! Docker container is not supported (at the moment)\n"
        exit 0
    elif [[ -f /.dockerenv ]]; then
        echo -ne "ERROR! Docker container is not supported (at the moment)\n"
        exit 0
    fi
}

preconditions_verifyIsArch() {
    if [[ ! -e /etc/arch-release ]]; then
        echo -ne "ERROR! This script must be run in Arch Linux!\n"
        exit 0
    fi
}

preconditions_verifyPacmanLock() {
    if [[ -f /var/lib/pacman/db.lck ]]; then
        echo "ERROR! Pacman is blocked."
        echo -ne "If not running remove /var/lib/pacman/db.lck.\n"
        exit 0
    fi
}

preconditions_verifyIsUEFI() {
    if [[ ! -d "/sys/firmware/efi" ]]; then
        echo "ERROR! This script must be run on a UEFI system"
        exit 0
    fi
}

preconditions_verifyScriptPreconditions() {
    preconditions_verifyIsRoot
    preconditions_verifyIsArch
    preconditions_verifyPacmanLock
    preconditions_verifyIsDocker
    preconditions_verifyIsUEFI
}