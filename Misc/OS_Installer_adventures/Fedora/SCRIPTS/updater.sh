#!/bin/bash
utils_Print_Existing_AND_Nonexisting_Path() {
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

utils_Get_Existing_Path () {
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

utils_Copy_ALL_Configs() {
    sudo -u "$(logname)" find ./FILES/ -type f -iname "*.sh" -exec chmod +x {} \;

    cd ./FILES

    find . -type f | while IFS= read -r local_path; do
        local templated_path="${local_path:1}"
        local path="${templated_path//\$(logname)/$(logname)}"
        if ! diff -q "$local_path" "$path"; then
            local existing_path="$(utils_Get_Existing_Path "$path")"
            local user="$(stat -c "%U:%G" "$path")"
            if [[ "$existing_path" != "$(dirname $path)" ]]; then
                user="$(stat -c "%U:%G" "$existing_path")"
                sudo -u "$(stat -c "%U" "$existing_path")" mkdir -p "$(dirname "$path")"
            fi
            sudo rsync --chown=$user "$local_path" "$path"
        fi
    done

    cd ..
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

utils_Update_ALL_Configs