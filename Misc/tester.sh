#!/bin/bash
INTERNAL_TEST_NUMBER=1
function pass() { echo -e "\x1b[1;32mPASS\x1b[0m"; }
function fail() { echo -e "\x1b[1;31mFAIL\x1b[0m"; }
function internal_test() {
    text="$1"
    shift 1
    position=0

    for string in "$@"; do
        case ${string:0:2} in
            %!)
                if [[ "$text" == *"${string:2}"* ]]; then
                    echo 0
                    return
                fi
                ;;
            *)
                position=$(expr index "$text" "$string")
                if [ "$position" -eq 0 ]; then
                    echo 0
                    return
                fi
                ;;
        esac

        text="${text:$position}"
        position=0
    done

    echo 1
}
function test() {
    echo "$1"
    echo -ne "Test $INTERNAL_TEST_NUMBER: "
    case $(internal_test "$@") in
        1) pass ;;
        0) fail ;;
    esac
    ((INTERNAL_TEST_NUMBER++))
}