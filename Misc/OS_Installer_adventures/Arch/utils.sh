#!/bin/bash

set -a
BASE_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
TEMP_DIR="$BASE_DIR/TEMP"
CONFIG_FILE="$BASE_DIR/TEMP/setup.conf"
set +a

##################################
#                                #
#         G R A P H I C S        #
#                                #
##################################

# pad a string($1) left and right to make it centered in $2 characters of space
utils_CenterString() {
  local string="$1"
  local max_length="$2"

  local padding_length=$(( (max_length - ${#string}) / 2 ))
  local padding=$(printf '%*s' "$padding_length" "")

  local padding_extra="" #if the parity differs
  if (( ${#string} % 2 != max_length % 2 )); then
    padding_extra=" "
  fi

  echo -ne "$padding$string$padding$padding_extra"
}

utils_ShowLogo() {
    clear
    local spacer="--------------------------------------------------------------------------"
    local firstHeading=${1:-"Automated Arch Linux Installer"}
    firstHeading="$(utils_CenterString "$firstHeading" ${#spacer})"
    local headings="$spacer\n$firstHeading\n"
    for ((i = 2; i <= $# + 1; ++i)); do
        local nextHeading="$(utils_CenterString "${!i:-$spacer}" ${#spacer})"
        headings="$headings$nextHeading\n"
    done
    echo -ne "
--------------------------------------------------------------------------
    ██╗  ██╗███████╗██╗  ██╗██╗  ██╗██╗   ██╗     ██████╗ ███████╗    
    ██║  ██║██╔════╝╚██╗██╔╝╚██╗██╔╝╚██╗ ██╔╝    ██╔═══██╗██╔════╝    
    ███████║█████╗   ╚███╔╝  ╚███╔╝  ╚████╔╝     ██║   ██║███████╗    
    ██╔══██║██╔══╝   ██╔██╗  ██╔██╗   ╚██╔╝      ██║   ██║╚════██║    
    ██║  ██║███████╗██╔╝ ██╗██╔╝ ██╗   ██║       ╚██████╔╝███████║    
    ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝        ╚═════╝ ╚══════╝    
$headings"
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

##################################
#                                #
#            M I S C             #
#                                #
##################################

utils_CurrentTimeMS() {
    date +%s%3N
}

utils_pacmanInstall() {
    pacman -S --noconfirm --needed "$@"
}

utils_rebootWithTimer() {
    echo "Drive is not mounted can not continue"
    echo "Rebooting in 3 Seconds ..." && sleep 1
    echo "Rebooting in 2 Seconds ..." && sleep 1
    echo "Rebooting in 1 Second ..." && sleep 1
    reboot now
}

utils_setPacmanParallel() {
    sed -i 's/^#ParallelDownloads = 5/ParallelDownloads = 20/' /etc/pacman.conf
}

##################################
#                                #
#  O P T I O N  M A N A G E R S  #
#                                #
##################################

# add to setup.conf variable($1) = value($2)
utils_setOption() {
    if grep -Eq "^${1}.*" $CONFIG_FILE; then # check if option exists
        sed -i -e "/^${1}.*/d" $CONFIG_FILE # delete option if exists
    fi
    echo "${1}='${2}'" >>$CONFIG_FILE # add option
}

# Renders a text based list of options that can be selected by the
# user using up, down and enter keys and returns the chosen option.
#
#   Arguments   : list of options, maximum of 256
#                 "opt1" "opt2" ...
#   Return value: selected index (0 for opt1, 1 for opt2 ...)
utils_selectColumnOption() {
    cursor_blink_on()  { printf "\033[?25h"; }
    cursor_blink_off() { printf "\033[?25l"; }
    cursor_to()        { printf "\033[$1;${2:-1}H"; }
    print_option()     { printf "$2   $1 "; }
    print_selected()   { printf "$2  \033[7m $1 \033[27m"; }

    get_cursor_pos()   { IFS=';' read -sdR -p $'\E[6n' ROW COL; echo "${ROW#*[};${COL#*[}"; }
    key_input() {
        local key
        read -rsn1 key 2>/dev/null >&2
        case "$key" in
            "") echo "enter" ;;
            $'\x20') echo "space" ;;
            "k") echo "up" ;;
            "j") echo "down" ;;
            "h") echo "left" ;;
            "l") echo "right" ;;
            "a") echo "all" ;;
            "n") echo "none" ;;
            $'\x1b')
                read -rsn2 key
                case "$key" in
                    "[A" | "k") echo "up" ;;
                    "[B" | "j") echo "down" ;;
                    "[C" | "l") echo "right" ;;
                    "[D" | "h") echo "left" ;;
                esac
                ;;
        esac
    }
    print_options_multicol() {
        local curr_col=$1
        local curr_row=$2
        local curr_idx=$((curr_col + curr_row * colmax))

        for ((idx = 0; idx < ${#options[@]}; idx++)); do
            local row=$((idx / colmax))
            local col=$((idx % colmax))

            cursor_to $((startrow + row + 1)) $((offset * col + 1))
            if [ $idx -eq $curr_idx ]; then
                print_selected "${options[idx]}"
            else
                print_option "${options[idx]}"
            fi
        done
    }

    # initially print empty new lines (scroll down if at bottom of screen)
    for opt; do printf "\n"; done

    # Initialization
    local return_value=$1
    local cols=$(tput cols)
    local colmax=$2
    local offset=$((cols / colmax))
    local size=${#options[@]}
    size=$((size - 1)) # cuz we are 0 indexed

    # Determine start row based on current cursor position
    local lastrow
    IFS=';' read -r -dR lastrow _ < <(get_cursor_pos)
    startrow=$((lastrow - size))
    local active_row=0
    local active_col=0
    local active_index=0

    # Cursor and input control
    trap "cursor_blink_on; stty echo; printf '\n'; exit" 2
    cursor_blink_off

    while true; do
        print_options_multicol "$active_col" "$active_row"

        local last_row=$active_row
        local last_col=$active_col
        # User key control
        case "$(key_input)" in
            enter) break ;;
            up) ((active_row--))
                if [ $active_row -lt 0 ]; then
                    active_row=0
                fi;;
            down) ((active_row++))
                if [ $active_row -ge $((size / colmax)) ]; then
                    active_row=$((size / colmax))
                fi;;
            left) ((active_col--))
                if [ $active_col -lt 0 ]; then
                    active_col=0
                fi;;
            right) ((active_col++))
                if [ $active_col -ge $colmax ]; then
                    active_col=$((colmax - 1))
                fi;;
        esac
        active_index=$((active_col + active_row * colmax))
        if [ $active_index -gt $size ]; then
            active_col=$last_col
            active_row=$last_row
            active_index=$((active_col + active_row * colmax))
        fi
    done

    # Reset cursor position and display
    cursor_to "$((lastrow+1))"
    printf "\n"
    cursor_blink_on

    return $active_index
}

##################################
#                                #
#   P R E C O N D I T I O N S    #
#                                #
##################################


utils_verifyIsRoot() {
    if [[ "$(id -u)" != "0" ]]; then
        echo "ERROR! This script must be run as the root user!"
        exit 0
    fi
}

utils_verifyIsDocker() {
    if awk -F/ '$2 == "docker"' /proc/self/cgroup | read -r; then
        echo -ne "ERROR! Docker container is not supported (at the moment)\n"
        exit 0
    elif [[ -f /.dockerenv ]]; then
        echo -ne "ERROR! Docker container is not supported (at the moment)\n"
        exit 0
    fi
}

utils_verifyIsArch() {
    if [[ ! -e /etc/arch-release ]]; then
        echo -ne "ERROR! This script must be run in Arch Linux!\n"
        exit 0
    fi
}

utils_verifyPacmanLock() {
    if [[ -f /var/lib/pacman/db.lck ]]; then
        echo "ERROR! Pacman is blocked."
        echo -ne "If not running remove /var/lib/pacman/db.lck.\n"
        exit 0
    fi
}

utils_verifyIsUEFI() {
    if [[ ! -d "/sys/firmware/efi" ]]; then
        echo "ERROR! This script must be run on a UEFI system"
        exit 0
    fi
}

utils_verifyScriptPreconditions() {
    utils_verifyIsRoot
    utils_verifyIsArch
    utils_verifyPacmanLock
    utils_verifyIsDocker
    utils_verifyIsUEFI
}