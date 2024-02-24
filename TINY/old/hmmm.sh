#!/bin/bash

offset=$(xxd -p -c 1024 a.out | tr -d '\n'| grep -m 1 -bo 9090 | cut -d':' -f1)
echo -ne "obase=16\n$(($offset / 2))\n" | bc