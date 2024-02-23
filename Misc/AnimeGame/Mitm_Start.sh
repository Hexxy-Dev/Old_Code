#!/bin/bash
./mitmdump -s ./proxy.py -k --listen-port 28080 
pid1=$!
trap "kill $pid1" EXIT
sleep 2000000000