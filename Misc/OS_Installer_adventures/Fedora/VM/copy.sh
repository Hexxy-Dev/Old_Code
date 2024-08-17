#!/bin/bash
sudo -u $(logname) cp /mnt/new_os/VM/init.sh /home/$(logname)/
sudo -u $(logname) cp /mnt/new_os/VM/update.sh /home/$(logname)/
sudo -u $(logname) cp /mnt/new_os/VM/freshinstall.sh /home/$(logname)/
sudo -u $(logname) chmod +x /home/$(logname)/init.sh
sudo -u $(logname) chmod +x /home/$(logname)/update.sh
sudo -u $(logname) chmod +x /home/$(logname)/freshinstall.sh

sudo echo 'max_parallel_downloads=20' >> '/etc/dnf/dnf.conf' # 29:24
sudo echo 'fastestmirror=True' >> '/etc/dnf/dnf.conf'  # 28:07
sudo touch environment
sudo echo 'XDG_DATA_DIRS=/var/lib/flatpak/exports/share' > environment
sudo mv environment /etc/environment

reboot