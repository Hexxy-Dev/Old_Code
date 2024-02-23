#!/bin/bash

function main() {
    local port="$1"; shift
    
    local protocol="tcp"
    if [[ "$1" == -* ]]; then
        protocol="${1:1}"; shift
    fi
    local command="$@"

    local uuid="$(cat /proc/sys/kernel/random/uuid)"
    local proxifierGroup="proxifier_${uuid:0:8}"
    
    sudo groupadd $proxifierGroup
    sudo iptables -t nat -I OUTPUT -m owner --gid-owner $proxifierGroup -p $protocol -j REDIRECT --to-ports $port
    sudo usermod -a -G $proxifierGroup $(logname)
    
    #debugging
    sudo nft list ruleset | grep $(getent group $proxifierGroup | awk -F: '{print $3}')
    getent group | grep $proxifierGroup

    #sudo -E -u $(logname) -g $proxifierGroup "$command"
    
    $(sg $proxifierGroup "$command")

    sudo iptables -t nat -D OUTPUT -m owner --gid-owner $proxifierGroup -p $protocol -j REDIRECT --to-ports $port
    sudo groupdel $proxifierGroup
    
    
    #debugging
    #sudo nft list ruleset | grep $(getent group $proxifierGroup | awk -F: '{print $3}')
    #getent group | grep $proxifierGroup
}
main "$@"