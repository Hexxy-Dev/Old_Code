#!/bin/bash
sudo chown "$USERNAME:$USERNAME" -R .
cd "$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
source './utils.sh'
source "$CONFIG_FILE"
source './fileUtils.sh'

utils_ShowLogo ""

postboot_setLocales() {
    utils_ShowLogo "" "Setup Language to US and set locale"
    #loadkeys ?????
    #timedatectl set-ntp true
    timedatectl set-timezone ${TIMEZONE}
    sudo hwclock --systohc

    sudo sed -i 's/^#en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen
    sudo locale-gen

    localectl set-locale LANG="en_US.UTF-8" LC_TIME="en_US.UTF-8"
    sudo ln -sf /usr/share/zoneinfo/${TIMEZONE} /etc/localtime
    
    localectl set-keymap ${KEYMAP}

    utils_pacmanInstall chrony
    systemctl enable chronyd.service
}

postboot_installAUR() {
    utils_ShowLogo "" "Installing AUR Helper"

    utils_pacmanInstall base-devel rustup
    rustup toolchain install stable
    git clone https://aur.archlinux.org/paru.git
    cd paru
    makepkg -si
    cd ..
}

postboot_installGraphics() {
    utils_ShowLogo "" "Installing Graphics Drivers"

    utils_pacmanInstall mesa xorg{,-server,-apps,-drivers,-xkill,-xinit} glfw-x11 noto-fonts ttf-dejavu ttf-liberation
    
    gpu_type=$(lspci)
    if grep -E "NVIDIA|GeForce" <<< ${gpu_type}; then
        utils_pacmanInstall nvidia nvidia-utils lib32-nvidia-utils
        nvidia-xconfig
    elif lspci | grep 'VGA' | grep -E "Radeon|AMD"; then
        utils_pacmanInstall xf86-video-amdgpu
    elif grep -E "Integrated Graphics Controller" <<< ${gpu_type}; then
        utils_pacmanInstall libva-intel-driver libvdpau-va-gl lib32-vulkan-intel vulkan-intel libva-intel-driver libva-utils lib32-mesa
    elif grep -E "Intel Corporation UHD" <<< ${gpu_type}; then
        utils_pacmanInstall libva-intel-driver libvdpau-va-gl lib32-vulkan-intel vulkan-intel libva-intel-driver libva-utils lib32-mesa
    fi
}

postboot_installGraphicalEnvironment() {
    utils_ShowLogo "" "Installing and Theming Login Display Manager"
    
    utils_pacmanInstall ly
    paru -S  mkinitcpio-numlock # NEEDS HOOK
    systemctl enable ly.service
    systemctl set-default graphical.target

    utils_ShowLogo "" "Installing Window Manager and Compositor"
    utils_pacmanInstall i3-wm i3lock polybar rofi dmenu picom maim xclip xdotool
}

postboot_packages_essentials() {
    utils_ShowLogo "" "Installing essential packages"
    utils_pacmanInstall pipewire jack2 wireplumber phonon-qt5-vlc jdk-openjdk xdg-desktop-portal-gtk
    utils_pacmanInstall alacritty neovim ranger ttf-hack-nerd tldr btop neofetch cloc bc unrar zip p7zip
    utils_pacmanInstall discord obsidian firefox chromium

    utils_pacmanInstall rsync tmux jq gpick fzf nvtop openssh cronie

    utils_pacmanInstall lxappearance qt5ct arandr
    paru -S oomox-qt5-styleplugin-git
    paru -S themix-full-git   #THIS IS HUGE!!!!!
}

postboot_packages_optionals_Utilities() {
    utils_ShowLogo "" "Installing utilities"
    utils_pacmanInstall qbittorrent zerotier-one
    utils_pacmanInstall dolphin konsole
    utils_pacmanInstall baobab gnome-disk-utility gnome-logs
    paru -S nvidia-system-monitor-qt
    paru -S microsoft-edge-stable-bin

    utils_pacmanInstall cups
    systemctl enable cups.service
    systemctl enable avahi-daemon.service
}

postboot_install_optionals_Virtualization() {
    utils_pacmanInstall dnsmasq vde2 bridge-utils openbsd-netcat dmidecode iptables-nft qemu-full libguestfs virt-manager
    sudo systemctl enable libvirtd.service
    sudo systemctl start libvirtd.service

    # idk if actually necessary
    sudo sed -i 's/^#unix_sock_group/unix_sock_group/' /etc/libvirt/libvirtd.conf
    sudo sed -i 's/^#unix_sock_rw_perms/unix_sock_rw_perms/' /etc/libvirt/libvirtd.conf

    sudo systemctl restart libvirtd.service
    # WIP:
    # probably will have problems with the default network... maybe see virsh
}

postboot_packages_optionals_Media() {
    utils_ShowLogo "" "Installing media tools"
    utils_pacmanInstall ncmpcpp helvum easyeffects audacity mpd scrcpy ffmpeg
    sudo systemctl disable mpd
    systemctl --user enable mpd
    paru -S xnviewmp
}

postboot_packages_optionals_Coding() {
    utils_ShowLogo "" "Installing coding tools"
    utils_pacmanInstall sysprof python-pipx ghidra gimp nodejs arduino
    paru -S visual-studio-code-bin
    paru -S imhex   # maybe just install from flatpak?
    paru -S autokey-gtk
    paru -S arduino-ide-bin
    usermod -a -G uucp ${USERNAME}
    paru -S android-studio
}

postboot_packages_optionals_Games() {
    utils_ShowLogo "" "Installing gaming support"
    utils_pacmanInstall firejail mangohud gamemode wine lutris
    utils_pacmanInstall obs-studio steam

    paru -S prismlauncher
    paru -S osu-lazer
}

postboot_installPackages() {
    utils_ShowLogo "" "Installing specific choice packages"

    postboot_packages_essentials
    postboot_packages_optionals_Utilities
    postboot_install_optionals_Virtualization
    postboot_packages_optionals_Media
    postboot_packages_optionals_Coding
    postboot_packages_optionals_Games


    #paru -S snapd
    #sudo systemctl enable snapd.seeded.service
    #sudo systemctl start snapd.seeded.service
    #utils_pacmanInstall flatpak
    #sudo flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
}


customInstalls_DeepFilterNet() {
    fileUtils_Git_File_Downloader "Rikorose/DeepFilterNet" \
        "$(fileUtils_JQ_Contains "linux" "x86_64" ".so")" "/home/$(logname)/.ladspa/libdeep_filter_ladspa.so"
}



postboot_Prep() {
    utils_ShowLogo "" "Starting postboot configuration"
    # Add sudo no password rights
    sudo sed -i 's/^# %wheel ALL=(ALL) NOPASSWD: ALL/%wheel ALL=(ALL) NOPASSWD: ALL/' /etc/sudoers
    sudo sed -i 's/^# %wheel ALL=(ALL:ALL) NOPASSWD: ALL/%wheel ALL=(ALL:ALL) NOPASSWD: ALL/' /etc/sudoers
    
    local POLKIT_CTL_RULE='
    polkit.addRule(function(action, subject) {
        if((action.id == "org.freedesktop.systemd1.manage-unit-files" ||
            action.id == "org.freedesktop.locale1.set-locale" ||
            action.id == "org.freedesktop.locale1.set-keyboard" ||
            action.id == "org.freedesktop.timedate1.set-timezone"
            ) && subject.isInGroup("wheel"))
        {
            return polkit.Result.YES;
        }
    });
    '
    local POLKIT_FILE='/etc/polkit-1/rules.d/CREATED_DURING_INSTALL__PLEASE_REMOVE__WARNING_SECURITY_RISK.rules'
    echo "$POLKIT_CTL_RULE" | sudo tee "$POLKIT_FILE" > /dev/null
    sudo systemctl restart polkit
}

postboot_Cleanup() {
    utils_ShowLogo "" "Cleaning" "" "A reboot is advised"

    sudo rm -rf /root/$CUSTOM_OS_NAME

    sudo rm "$POLKIT_FILE"
    sudo systemctl restart polkit

    # Remove no password sudo rights
    sudo sed -i 's/^%wheel ALL=(ALL) NOPASSWD: ALL/# %wheel ALL=(ALL) NOPASSWD: ALL/' /etc/sudoers
    sudo sed -i 's/^%wheel ALL=(ALL:ALL) NOPASSWD: ALL/# %wheel ALL=(ALL:ALL) NOPASSWD: ALL/' /etc/sudoers

    cat $TEMP_DIR/*.log > ~/complete.log
}

postboot_main() {
    postboot_Prep

    sudo systemctl enable fstrim.timer

    postboot_setLocales
    postboot_installAUR
    postboot_installGraphics
    postboot_installGraphicalEnvironment
    postboot_installPackages

    customInstalls_DeepFilterNet


    utils_ShowLogo "" "UPDATING ALL CUSTOM CONFIGS"

    ./updateConfigs.sh


    # IF ENABLING VIA /etc/dconf/profile/user
    # sudo dconf dump / > ~/.config/dconf/user.txt
    
    # Defaults 	insults
    # /etc/sudoers

    postboot_Cleanup
}
postboot_main |& tee './TEMP/postboot.log'

#rm -rf /home/$USERNAME/$CUSTOM_OS_NAME