#!/bin/bash

source "./utils/platformSpecific.sh"

cd src

VENDOR_DIR="../vendor/"
VENV_PYTHON="${VENDOR_DIR}${VENV_PYTHON}"

${VENDOR_DIR}${VOICEVOX_TYPE}/run${EXECUTABLE_EXTENSION} --use_gpu &>../tmp/engineLog.txt & #--load_all_models
${VENV_PYTHON} Main.py | tee ../tmp/log.txt

wait