cd ..

mkdir vendor
mkdir tmp
cd vendor

python -m venv ./venv

source "./platformSpecific.sh"
VENV_PYTHON="./${VENV_PYTHON}"

${VENV_PYTHON} -m pip install --upgrade pip
${VENV_PYTHON} -m pip install -r ../utils/requirements.txt

TAG_NAME=$(curl -L "https://github.com/VOICEVOX/voicevox_engine/releases/latest" | grep -m1 Release | grep -oE "[0-9]+(\.[0-9]+)*")

FILE_NAME="voicevox_engine-${VOICEVOX_TYPE}-${TAG_NAME}.7z.001"

FILE_URL="https://github.com/VOICEVOX/voicevox_engine/releases/download/${TAG_NAME}/${FILE_NAME}"

echo $FILE_URL

TMP_DIR="../tmp/"
FILE_TEMP_PATH="${TMP_DIR}${FILE_NAME}"

wget -O "${FILE_TEMP_PATH}" "${FILE_URL}"

7z x "${FILE_TEMP_PATH}"

rm "${FILE_TEMP_PATH}"