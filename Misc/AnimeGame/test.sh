#!/bin/bash

ls -R / &
pid1=$!
trap "kill $pid1" EXIT
sleep 3