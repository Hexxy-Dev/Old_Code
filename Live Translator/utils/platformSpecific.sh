#!/bin/bash

EXECUTABLE_EXTENSION=""
if [[ "$OSTYPE" = "msys" ]]; then
    PLATFORM="windows"
    PYTHON_VENV_FOLDER="Scripts"
    EXECUTABLE_EXTENSION=".exe"
fi

if [[ "$OSTYPE" == "linux-gnu" ]]; then
    PLATFORM="linux"
    PYTHON_VENV_FOLDER="bin"
fi

VENV_PYTHON="venv/${PYTHON_VENV_FOLDER}/python"
VOICEVOX_TYPE="${PLATFORM}-nvidia"