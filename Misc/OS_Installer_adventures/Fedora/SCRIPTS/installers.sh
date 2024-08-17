#!/bin/bash
##################################
#                                #
#    F I R S T  I N S T A L L    #
#                                #
##################################

firstInstall_Init_dnf_rpm() {
    sudo dnf upgrade -y --refresh

    sudo dnf install -y https://download1.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
    sudo dnf install -y https://download1.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm

    sudo dnf upgrade -y --refresh
}

firstInstall_DM_lightdm() {
    sudo dnf install -y Xorg lightdm lightdm-gtk
    sudo systemctl enable lightdm.service
    sudo systemctl set-default graphical.target
    sudo dnf install -y lightdm-settings lightdm-gtk-greeter-settings numlockx
}

firstInstall_Drivers_Nvidia() {
    sudo dnf install -y akmod-nvidia xorg-x11-drv-nvidia-libs xorg-x11-drv-nvidia-libs.i686
    sudo dnf install -y xorg-x11-drv-nvidia-cuda xorg-x11-drv-nvidia-cuda-libs vulkan
    sudo dnf install -y nvidia-vaapi-driver libva-utils vdpauinfo
}

firstInstall_Utils_essentials() {
    sudo dnf install -y rsync util-linux-user flatpak
    sudo flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

    sudo flatpak install -y io.github.congard.qnvsm

    sudo dnf install -y neovim alacritty cascadia-code-fonts tmux

    sudo dnf install -y lxappearance qt5ct qt5-qtstyleplugins
    sudo flatpak install -y com.github.themix_project.Oomox #UNOFFICIAL
    #sudo dnf install -y gnome-tweaks #this should be removed after initial configuration
    sudo dnf install -y malcontent #this is required by flatpak

    sudo dnf group install -y "C Development Tools and Libraries" "Development Tools" "Development Libraries"

    sudo dnf install -y snapd
    sudo systemctl enable snapd.seeded.service
    sudo systemctl start snapd.seeded.service

    sudo dnf install -y git wget jq
}

firstInstall_WM_i3() {
    sudo dnf install -y i3 polybar rofi picom arandr

    sudo dnf remove -y rxvt-unicode i3status
}

firstInstall_ALL() {
    firstInstall_Init_dnf_rpm
    firstInstall_DM_lightdm
    firstInstall_Drivers_Nvidia
    firstInstall_Utils_essentials
    firstInstall_WM_i3
}

##################################
#                                #
#       O P T I O N A L S        #
#                                #
##################################

optionals_Administrative() {
    sudo dnf install -y dolphin konsole

    sudo dnf install -y baobab gnome-disk-utility gnome-software gnome-logs

    sudo dnf remove -y onboard

    sudo dnf install -y btop fzf tldr nvtop

    sudo dnf install -y virt-manager qemu
    sudo usermod -aG libvirt $(logname)
    sudo systemctl enable libvirtd

    #sudo dnf group install -y "Hardware Support" "Sound and Video"

    #pipx install nvitop #idk if I need this

    sudo snap install bitwarden
    sudo snap install zerotier
}

optionals_Audio() {
    sudo dnf install -y ncmpcpp helvum easyeffects audacity

    sudo dnf install -y --allowerasing mpd
    sudo systemctl disable mpd
    systemctl --user enable mpd

    #sudo dnf install -y gstreamer1-plugins-{bad-\*,good-\*,base} gstreamer1-plugin-openh264 gstreamer1-libav --exclude=gstreamer1-plugins-bad-free-devel
    #sudo dnf install -y lame vlc
    #sudo dnf group install --with-optional -y Multimedia
}

optionals_Coding() {
    sudo dnf install -y imhex sysprof pipx

    sudo flatpak install -y org.ghidra_sre.Ghidra #UNOFFICIAL

    #sudo flatpak install -y com.github.finefindus.eyedropper

    sudo dnf install -y gimp autokey-gtk

    sudo dnf copr enable -y zeno/scrcpy
    sudo dnf install -y scrcpy

    sudo flatpak install -y cc.arduino.arduinoide
    sudo flatpak install -y cc.arduino.IDE2 #UNOFFICIAL
    #NOTE: user has to be part of dialout group

    sudo dnf install -y nodejs

    #not sure these are actually needed
    sudo dnf install -y python python-devel python3-devel python2-devel ####
    sudo dnf install -y portaudio portaudio-devel

    flatpak install -y com.google.AndroidStudio
    #meld sublime?
}

optionals_Wine() {
    sudo dnf install -y gamemode wine lutris mangohud firejail
    sudo dnf install -y vulkan-loader vulkan-loader.i686
}

optionals_Games() {
    sudo dnf copr enable -y g3tchoo/prismlauncher
    sudo dnf install -y prismlauncher

    sudo dnf install -y discord steam
    sudo flatpak install -y sh.ppy.osu #UNOFFICIAL
}

optionals_Random() {
    sudo flatpak install -y com.obsproject.Studio ####################################
    sudo flatpak install -y net.davidotek.pupgui2

    sudo flatpak install -y com.ultimaker.cura #UNOFFICIAL

    sudo dnf install -y firefox thunderbird chromium

    sudo dnf group install -y "LibreOffice"

    sudo dnf install -y neofetch
    sudo dnf install -y ffmpeg ImageMagick mpv yt-dlp
}

optionals_Terminal_emulators() {
    sudo flatpak install -y org.wezfurlong.wezterm

    sudo dnf install -y source-foundry-hack-fonts #texlive-cascadia-fonts
    sudo dnf install -y zsh fish kitty 
    #sudo chsh -s $(which zsh)
}

optionals_ALL() {
    optionals_Administrative
    optionals_Audio
    optionals_Coding
    optionals_Wine
    optionals_Random
    optionals_Games
    #optionals_Terminal_emulators
}

##################################
#                                #
#  C U S T O M  I N S T A L L S  #
#                                #
##################################

source ./utils.sh

customInstalls_AMDuprof() {
    LATEST="$(curl --user-agent "Mozilla/5.0 (X11; Linux x86_64)" https://www.amd.com/en/developer/uprof.html#downloads\
              | grep x86_64.rpm\" | sed "s#</.*e=##g" | sed "s#\".*>##g")"
    utils_TypeScript_Compile_And_Run "AMDuprof" "https://www.amd.com/en/developer/uprof/uprof-eula.html?filename=$LATEST"
    sudo dnf install -y '../TEMP/AMDuprof.rpm'
    rm '../TEMP/AMDuprof.rpm'
}

customInstalls_DeepFilterNet() {
    utils_Git_File_Downloader "Rikorose/DeepFilterNet" \
        "$(utils_JQ_Contains "linux" "x86_64" ".so")" "/home/$(logname)/.ladspa/libdeep_filter_ladspa.so"
}

customInstalls_XnView() {
    wget -O '../TEMP/XnViewMP.tgz' 'https://download.xnview.com/XnViewMP-linux-x64.tgz' 2>&1 #REDIRECT
    tar -xzf '../TEMP/XnViewMP.tgz' -C "/home/$(logname)/Custom_Software_Installs"
    rm '../TEMP/XnViewMP.tgz'
}

customInstalls_ALL() {
    sudo -u "$(logname)" mkdir -p "/home/$(logname)/Custom_Software_Installs"
    
    utils_Prep_Custom_Installs_Node_Dependencies
    
    customInstalls_AMDuprof

    utils_Clean_Custom_Installs_Node_Dependencies

    customInstalls_DeepFilterNet
    customInstalls_XnView
}