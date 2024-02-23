#!/bin/bash
#28081 port for dispatch server
#28080 port for proxy
sudo ls /dev/null
#./Mitm_Start.sh &
#pid1=$!
#./3DMigoto_Start.sh &
#pid2=$!
#trap "kill $pid1; kill $pid2" EXIT
#sleep 10
#./Proxifier.sh 28080 ./Proton_AnimeGame_Game.sh

./Proxifier.sh 28080 ./3DMigoto_Start.sh
#./Proxifier.sh 28080 /usr/bin/lutris lutris:rungame/AnimeGame
#WIP
#add settings for the ports
#auto patching is needed
#mod support