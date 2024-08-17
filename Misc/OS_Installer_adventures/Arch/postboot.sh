#!/bin/bash
chown "$USERNAME:$USERNAME" -R .
cd "$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
source './utils.sh'
source "$CONFIG_FILE"

utils_ShowLogo ""

postboot_setLocales() {
    utils_ShowLogo "" "Setup Language to US and set locale"

    timedatectl --no-ask-password set-ntp true
    timedatectl --no-ask-password set-timezone ${TIMEZONE}
    hwclock --systohc

    sed -i 's/^#en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen
    locale-gen

    localectl --no-ask-password set-locale LANG="en_US.UTF-8" LC_TIME="en_US.UTF-8"
    ln -sf /usr/share/zoneinfo/${TIMEZONE} /etc/localtime
    
    localectl --no-ask-password set-keymap ${KEYMAP}
}


postboot_installAUR() {
    utils_ShowLogo "" "Installing AUR Softwares"

    cd ~
    mkdir "/home/$USERNAME/.cache"
    touch "/home/$USERNAME/.cache/zshhistory"
    git clone "https://github.com/ChrisTitusTech/zsh"
    git clone --depth=1 https://github.com/romkatv/powerlevel10k.git ~/powerlevel10k
    ln -s "~/zsh/.zshrc" ~/.zshrc
}



postboot_installBasePkgs() {
    utils_ShowLogo "" "Installing Base System"
    sudo utils_pacmanInstall mesa
    sudo utils_pacmanInstall xorg{,-server,-apps,-drivers,-xkill,-xinit}
}

postboot_installGraphics() {
    utils_ShowLogo "" "Installing Graphics Drivers"
    gpu_type=$(lspci)
    if grep -E "NVIDIA|GeForce" <<< ${gpu_type}; then
        utils_pacmanInstall nvidia
        nvidia-xconfig
    elif lspci | grep 'VGA' | grep -E "Radeon|AMD"; then
        utils_pacmanInstall xf86-video-amdgpu
    elif grep -E "Integrated Graphics Controller" <<< ${gpu_type}; then
        utils_pacmanInstall libva-intel-driver libvdpau-va-gl lib32-vulkan-intel vulkan-intel libva-intel-driver libva-utils lib32-mesa
    elif grep -E "Intel Corporation UHD" <<< ${gpu_type}; then
        pacman -S --needed --noconfirm libva-intel-driver libvdpau-va-gl lib32-vulkan-intel vulkan-intel libva-intel-driver libva-utils lib32-mesa
    fi
}

postboot_installDisplayManager() {
    utils_ShowLogo "" "Enabling (and Theming) Login Display Manager"
    sudo utils_pacmanInstall lightdm-gtk-greeter

    systemctl enable lightdm.service
    systemctl set-default graphical.target
    # Set default lightdm-webkit2-greeter theme to Litarvan
    sed -i 's/^webkit_theme\s*=\s*\(.*\)/webkit_theme = litarvan #\1/g' /etc/lightdm/lightdm-webkit2-greeter.conf
    # Set default lightdm greeter to lightdm-webkit2-greeter
    sed -i 's/#greeter-session=example.*/greeter-session=lightdm-webkit2-greeter/g' /etc/lightdm/lightdm.conf
}

postboot_installWindowManager() {

}

postboot_installCompositor() {

}

postboot_installPackages() {

}

postboot_enableServices() {
    utils_ShowLogo "" "Enabling Essential Services"
    systemctl enable cups.service
    echo "  Cups enabled"
    ntpd -qg
    systemctl enable ntpd.service
    echo "  NTP enabled"
    systemctl disable dhcpcd.service
    echo "  DHCP disabled"
    systemctl stop dhcpcd.service
    echo "  DHCP stopped"
    systemctl enable NetworkManager.service
    echo "  NetworkManager enabled"
    systemctl enable bluetooth
    echo "  Bluetooth enabled"
    systemctl enable avahi-daemon.service
    echo "  Avahi enabled"
}

postboot_installBootSplash() {
    utils_ShowLogo "" "Enabling (and Theming) Plymouth Boot Splash"

    PLYMOUTH_THEMES_DIR="$HOME/$CUSTOM_OS_NAME/configs/usr/share/plymouth/themes"
    PLYMOUTH_THEME="arch-glow" # can grab from config later if we allow selection
    mkdir -p /usr/share/plymouth/themes
    echo 'Installing Plymouth theme...'
    cp -rf ${PLYMOUTH_THEMES_DIR}/${PLYMOUTH_THEME} /usr/share/plymouth/themes
    if  [[ $FS == "luks"]]; then
    sed -i 's/HOOKS=(base udev*/& plymouth/' /etc/mkinitcpio.conf # add plymouth after base udev
    sed -i 's/HOOKS=(base udev \(.*block\) /&plymouth-/' /etc/mkinitcpio.conf # create plymouth-encrypt after block hook
    else
    sed -i 's/HOOKS=(base udev*/& plymouth/' /etc/mkinitcpio.conf # add plymouth after base udev
    fi
    plymouth-set-default-theme -R arch-glow # sets the theme and runs mkinitcpio
    echo 'Plymouth theme installed'
}

postboot_main() {
    # Add sudo no password rights
    sed -i 's/^# %wheel ALL=(ALL) NOPASSWD: ALL/%wheel ALL=(ALL) NOPASSWD: ALL/' /etc/sudoers
    sed -i 's/^# %wheel ALL=(ALL:ALL) NOPASSWD: ALL/%wheel ALL=(ALL:ALL) NOPASSWD: ALL/' /etc/sudoers

    postboot_setLocales
    #postboot_installAUR
    #postboot_installBasePkgs
    #postboot_installGraphics
    #postboot_installDisplayManager
    #postboot_installWindowManager
    #postboot_installCompositor
    #postboot_installPackages
    #postboot_enableServices
    #postboot_installBootSplash

    utils_ShowLogo "" "Cleaning"
    # Remove no password sudo rights
    sed -i 's/^%wheel ALL=(ALL) NOPASSWD: ALL/# %wheel ALL=(ALL) NOPASSWD: ALL/' /etc/sudoers
    sed -i 's/^%wheel ALL=(ALL:ALL) NOPASSWD: ALL/# %wheel ALL=(ALL:ALL) NOPASSWD: ALL/' /etc/sudoers

    cat './TEMP/*.log' > '../complete.log'
    rm -r /root/$CUSTOM_OS_NAME
    rm -r /home/$USERNAME/$CUSTOM_OS_NAME
}
postboot_main > './TEMP/postboot.log'

exit