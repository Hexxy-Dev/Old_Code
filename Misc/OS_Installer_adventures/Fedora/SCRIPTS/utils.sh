#!/bin/bash
##################################
#                                #
#  C O N F I G  M A N A G E R S  #
#                                #
##################################

utils_Copy_With_Missing_Path_And_Accodring_Privileges() {
    local_path="$1"
    escaped_path="$2"

    sudo -u "$(logname)" mkdir -p "$(dirname "$escaped_path")" #create missing path as current user
    rsync --mkpath --chown="$(logname)":"$(logname)" "$local_path" "$escaped_path" #mkpath is fallback
}

utils_Copy_ALL_Configs() {
    sudo -u "$(logname)" find ../FILES/ -type f -iname "*.sh" -exec chmod +x {} \;

    cd ../FILES

    find . -type f | while IFS= read -r local_path; do
        # STILL DOES NOT WORK WITH PATHS THAT HAVE SPACES IN THEM!!!
        templated_spaced_path="${local_path:1}"
        spaced_path="${templated_spaced_path//\$(logname)/$(logname)}"
        escaped_path=${spaced_path// /\ }
        if ! diff -q "$local_path" "$spaced_path"; then
            utils_Copy_With_Missing_Path_And_Accodring_Privileges "$local_path" "$escaped_path"
        fi
    done

    cd ../SCRIPTS
}

utils_Update_ALL_Configs() {
    result="$(utils_Copy_ALL_Configs 2>&1)"

    #extra steps after copy
    echo "$result" | while IFS= read -r file; do
        #this path extraction might need some more experimentation as it might fail with wierd outputs
        if [[ "$file" =~ ^"diff: " ]]; then
            file=${file//diff: /}
            file=${file//: No such file or directory/}
        fi
        if [[ "$file" =~ ^"Files " ]]; then
            file=${file//Files /}
            file=${file// differ/}
            file=${file#* and }
        fi
        echo $file


        if [[ "$file" == *"/etc/default/grub"* ]]; then
            echo "Grub changed!!"
            r=$(grub2-mkconfig -o /etc/grub2.cfg)
        fi

        if [[ "$file" == *"/pipewire/filter-chain.conf.d"* ]]; then
            echo "ALWAYS - Pipewire paths fix at $file"
            sed -i "s/\$(logname)/$(logname)/g" $file
        fi

        if [[ "$file" == *"XnView"* ]]; then
            echo "ALWAYS - XnView paths fix at $file"
            sed -i "s#/opt/XnView/#/home/$(logname)/Custom_Software_Installs/XnView/#g" $file
        fi

        if [[ "$file" == *".gtkrc"* ]]; then
            echo "ALWAYS - Lxappearance paths fix at $file"
            sed -i "s#/home/\$(logname)/#/home/$(logname)/#g" $file
        fi
    done
}

##################################
#                                #
#     C U S T O M  U T I L S     #
#                                #
##################################

utils_Git_File_Downloader() {
    REPO="$1"; shift

    JSON="$(curl "https://api.github.com/repos/${REPO}/releases/latest")"

    while (( $# > 0 )); do
        SELECTION="$1"
        DESTINATION="$2"
        shift 2

        URL="$(echo $JSON | jq -r ".assets[] | select(.name | $SELECTION) | .browser_download_url")"
        FILE_NAME=${URL##*/}

        cd '../TEMP'

        wget "$URL" 2>&1 #REDIRECT
        utils_Copy_With_Missing_Path_And_Accodring_Privileges "./$FILE_NAME" "$DESTINATION"
        rm "./$FILE_NAME"

        cd '../SCRIPTS'
    done
}


utils_JQ_Contains() {
    OUTPUT="contains(\"$1\")"; shift

    for STRING in "$@"; do
        OUTPUT="$OUTPUT and contains(\"$STRING\")"
    done

    echo "$OUTPUT"
}

utils_Prep_Custom_Installs_Node_Dependencies() {
    cd './CustomInstalls'
    mkdir 'Compiled'
    npm install
    cd '..'
}
utils_Clean_Custom_Installs_Node_Dependencies() {
    cd './CustomInstalls'
    rm './package-lock.json'
    rm -rf './node_modules'
    rm -rf './Compiled'
    cd '..'
}

utils_Clean_Custom_Installs_Binaries() {
    rm -rf '../FILES/home/$(logname)/Custom_Software_Installs/*'
    rm -rf '../FILES/home/$(logname)/.ladspa/*'
}

utils_TypeScript_Compile_And_Run() {
    FILE_NAME="$1"; shift
    cd './CustomInstalls'
    npx tsc --outDir "./Compiled" "$FILE_NAME.ts"
    cd '..'
    node "./CustomInstalls/Compiled/$FILE_NAME.js" "$@"
}
