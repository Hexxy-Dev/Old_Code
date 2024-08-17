# WIP
base: fedora server - custom os profile
dm: lightdm - lightdm-gtk-greeter
wm: i3 + polybar, rofi
term: alacritty + bash

RN it should work but is really ugly :/


after fresh install some manual steps need to be made:
create oomox theme and icons


run and configure lxappearance
run and configure qt5ct


WIP: configure and then put in user.txt
run and configure gnome-tweaks
run and configure gnome-control-center
dnf remove gnome-tweaks



This whole thing (apart from the custom installs that were added later on) has been written in about 5 days starting from scratch (at the time I did not even know what a display manager was)
I use only sh files because I wanted to just plug in a usb stick with all these files and just copy them then chmod +x controller.sh, run it and leave it do it's thing



DESPITE MY BEST EFFORTS, THEMING IS STILL FUCKED


PROBLEM:
the /etc/dconf/profile/user first line is service-db:keyfile/user
meaning that the .config/dconf/user.txt will be used for that database but
I'm not sure if it is actually good for a first install. I'll need to make sure it
contains only sensible defaults that don't break stuff

maybe have user.txt and the other one be ignored for now??







fd
tldr
ripgrep
bat
exa
toeki



SWITCH TO ARCH????
i3 awsomewm?

thunar dolphin
gnome-disks kde-partition-manager gparted
nvim micro vscode sublime
firefox chromium edge

ext4
tmpfs


windows XP ---> windows 7 -|-> windows 10 ---> windows 11 ---> fedora -|-> arch
                           \-> ubuntu server                           \-> proxmox
                                                                          \-> clear linux