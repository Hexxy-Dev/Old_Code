#!/bin/bash
source './fileUtils.sh'

updater_Copy_ALL_Configs() {
    sudo -u "$(logname)" find ./FAKEROOT/ -type f -iname "*.sh" -exec chmod +x {} \;

    cd ./FAKEROOT

    find . -type f | while IFS= read -r local_path; do
        local templated_path="${local_path:1}"
        local path="${templated_path//\$(logname)/$(logname)}"

        if ! diff -q "$local_path" "$path"; then
            fileUtils_Copy_with_missing_path_and_appropriate_owner "$local_path" "$path"
        fi
    done

    cd ..
}

updater_Update_ALL_Configs() {
    echo "STARTING CONFIG UPDATES!"

    result="$(updater_Copy_ALL_Configs 2>&1)"

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

        if [[ "$file" == *"/pipewire/filter-chain.conf.d"* ]]; then
            echo "ALWAYS - Pipewire paths fix at $file"
            sed -i "s/\$(logname)/$(logname)/g" $file
        fi

        if [[ "$file" == *"/etc/mkinitcpio.conf"* ]]; then
            echo "RAMDISK changed!!"
            sudo mkinitcpio -P
        fi

        

        if [[ "$file" == *"/boot/loader/entries/arch.conf"* ]]; then
            echo "ALWAYS - Systemd entry changed!!"
            local partition="$(blkid -L ROOT)"
            local partition_uuid="$(blkid $partition -s UUID -o value)"
            sed -i "s/\$(UUID)/$(partition_uuid)/g" $file
        fi

    done
    echo "DONE!"
}

updater_Update_ALL_Configs