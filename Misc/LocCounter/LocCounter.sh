#!/bin/bash
ExcludeList=""
IncludeList=""
Path=""
while getopts 'iepf:' flag; do
  case "${flag}" in
    i)  while IFS= read -r extension; do
            if [ -n "$IncludeList" ]; then
                IncludeList=$(echo "$IncludeList-o ")
            fi
            IncludeList=$(echo "$IncludeList-iname '$extension' ")
        done <<<$(cat ~/Coding/LocCounter/include_files)
        ;;

    e)  while IFS= read -r extension; do
            ExcludeList=$(echo "$ExcludeList! -iname '$extension' ")
        done <<<$(cat ~/Coding/LocCounter/skip_files)
        ;;

    p)  echo $IncludeList
        echo $ExcludeList
        ;;

    f)  Path="${OPTARG}"
        ;;

    *)  echo "Usage:"
        ;;
  esac
done

HMM=$(echo "find \"$(pwd)/$Path\" -type f $IncludeList $ExcludeList")
eval $HMM | grep -vwE "(vendor|GLEW|GLM|GLFW|external|Dependencies|x64)" | sed 's/.*/"&"/' | xargs wc -l | sort -nr
