#!/bin/bash

utils_setPacmanParallel() {
    sed -i 's/^#ParallelDownloads = 5/ParallelDownloads = 20/' /etc/pacman.conf
}


# add to setup.conf variable($1) = value($2)
utils_setOption() {
    if grep -Eq "^${1}.*" $CONFIG_FILE; then # check if option exists
        sed -i -e "/^${1}.*/d" $CONFIG_FILE # delete option if exists
    fi
    echo "${1}='${2}'" >>$CONFIG_FILE # add option
}

utils_rebootWithTimer() {
    echo "Drive is not mounted can not continue"
    echo "Rebooting in 3 Seconds ..." && sleep 1
    echo "Rebooting in 2 Seconds ..." && sleep 1
    echo "Rebooting in 1 Second ..." && sleep 1
    reboot now
}




utils_CurrentTimeMS() {
    date +%s%3N
}

#show only the last $1 lines of the stdin
utils_StdinNtail() {
    local NUM_LINES=${1:-30}
    local  SCREEN_BUFFER_SIZE=$NUM_LINES
    NUM_LINES=$((NUM_LINES + 1))

    local TAIL_BUFFER="$(printf "%${SCREEN_BUFFER_SIZE}s")"
    TAIL_BUFFER="${TAIL_BUFFER// /$'\n'}"
    echo -n "$TAIL_BUFFER"

    local LAST_UPDATE=$(utils_CurrentTimeMS)
    while IFS= read -r NEW_LINE; do
        TAIL_BUFFER="$TAIL_BUFFER$NEW_LINE"$'\n'

        if [ $(($(utils_CurrentTimeMS) - LAST_UPDATE)) -gt 100 ]; then
            TAIL_BUFFER=$(echo "$TAIL_BUFFER" | tail -n "$NUM_LINES")$'\n'

            printf "\033[${SCREEN_BUFFER_SIZE}A\033[2K%s" "$TAIL_BUFFER"

            LAST_UPDATE=$(utils_CurrentTimeMS)
        fi

    done < /dev/stdin
}