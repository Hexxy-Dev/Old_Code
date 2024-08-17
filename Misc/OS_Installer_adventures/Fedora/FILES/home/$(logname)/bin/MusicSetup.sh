#!/bin/bash

session='Music'
window="$session:0"

#wmctrl -r ':ACTIVE:' -b toggle,fullscreen
echo -ne "\e[8;60;240t"

mpd || true

tmux attach-session -d -t "$session"
if [ $? -eq 0 ]
then exit
fi

tmux new-session -d -s "$session"

tmux send-keys    -t "$window"		'tmux detach' C-m
tmux attach-session -d -t "$session"


tmux send-keys    -t "$window"		'ncmpcpp -s playlist' C-m

tmux split-window -t "$window"			-h
tmux send-keys    -t "$window"		'ncmpcpp -s visualizer' C-m

tmux split-window -t "$window"			-v
tmux send-keys    -t "$window"		'ncmpcpp -s browser' C-m

tmux select-pane  -t "$window.{left}"
tmux split-window -t "$window"			-v
tmux send-keys    -t "$window"		'ncmpcpp -s clock' C-m


tmux select-window -t "$window"
tmux select-pane   -t "$window.{bottom-right}"

tmux attach-session -d -t "$session"
