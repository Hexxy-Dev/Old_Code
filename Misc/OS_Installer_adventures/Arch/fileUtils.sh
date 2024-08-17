#!/bin/bash
fileUtils_Print_Existing_AND_Nonexisting_Path() {
    IFS="/" read -ra parts <<< "$1"

    local current_path=""
    local existing_path=""
    local nonexistent_path=""
    case ${parts[0]} in
        "..") current_path=".."; existing_path=".."; unset parts[0];;
        ".") current_path="."; existing_path=".."; unset parts[0];;
        "") unset parts[0]
    esac

    for part in "${parts[@]}"; do
        current_path="$current_path/$part"

        if [ -d "$current_path" ]; then
            existing_path="$current_path"
        else
            nonexistent_path="$nonexistent_path/$part"
        fi
    done

    echo "$existing_path"
    echo "$nonexistent_path"
}

fileUtils_Get_Existing_Path () {
    IFS="/" read -ra parts <<< "$1"

    local current_path=""
    local existing_path=""
    case ${parts[0]} in
        "..") current_path=".."; existing_path=".."; unset parts[0];;
        ".") current_path="."; existing_path="."; unset parts[0];;
        "") unset parts[0]
    esac

    for part in "${parts[@]}"; do
        current_path="$current_path/$part"
        
        if [ -d "$current_path" ]; then
            existing_path="$current_path"
        else
            break
        fi
    done

    echo "$existing_path"
}

#Also creates a backup in tmp
fileUtils_Copy_With_Missing_Path_And_Appropriate_Owner() {
    local local_path="$($1)"
    local path="$($2)"

    local existing_path="$(fileUtils_Get_Existing_Path "$path")"
    local user="$(logname)"
    if [[ -f "$path" ]]; then
        local temp_folder="/tmp/FILE_BACKUP_$(date +%s%3N)"
        mkdir "$temp_folder"
        sudo cp "$path" "$temp_folder/"
        echo "$path" > "$temp_folder/ORIGIN.txt"
        user="$(stat -c "%U:%G" "$path")"
    else
        user="$(stat -c "%U:%G" "$existing_path")"
        sudo -u "$(stat -c "%U" "$existing_path")" mkdir -p "$(dirname "$path")"
    fi
    sudo rsync --chown=$user "$local_path" "$path"
}

fileUtils_Git_File_Downloader() {
    REPO="$1"; shift

    JSON="$(curl "https://api.github.com/repos/${REPO}/releases/latest")"

    while (( $# > 0 )); do
        SELECTION="$1"
        DESTINATION="$2"
        shift 2

        URL="$(echo $JSON | jq -r ".assets[] | select(.name | $SELECTION) | .browser_download_url")"
        FILE_NAME=${URL##*/}

        cd './TEMP'

        wget "$URL" 2>&1 #REDIRECT
        fileUtils_Copy_With_Missing_Path_And_Appropriate_Owner "./$FILE_NAME" "$DESTINATION"
        rm "./$FILE_NAME"

        cd './SCRIPTS'
    done
}

fileUtils_JQ_Contains() {
    OUTPUT="contains(\"$1\")"; shift

    for STRING in "$@"; do
        OUTPUT="$OUTPUT and contains(\"$STRING\")"
    done

    echo "$OUTPUT"
}