#!/bin/bash

rm ~/.ssh/known_hosts; scp -r ./ root@192.168.122.139:./HexxyOS
