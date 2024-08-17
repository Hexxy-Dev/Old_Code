#!/bin/bash


maybeBad_Clear_Unused_Locales() {
    sudo rm '/usr/share/locale/!(en*|*alias)'
}
maybeBad_Disable_Downloading_New_Locales() {
    sudo echo '%_install_langs en' > '/etc/rpm/macros'
    sudo sed -i 's/%_install_langs.*all/%_install_langs en/g' '/usr/lib/rpm/macros'
}


probablyBad_Disable_Downloading_New_Manpages() {
    sudo echo 'tsflags=nodocs' >> '/etc/dnf/dnf.conf'
}

probablyBad_Disable_Documentation_And_Locales() {
    maybeBad_Clear_Unused_Locales
    maybeBad_Disable_Downloading_New_Locales
    probablyBad_Disable_Downloading_New_Manpages
}
