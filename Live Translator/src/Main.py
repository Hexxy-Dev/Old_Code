# -*- coding: utf-8 -*-
import time

from Utils import Utils
from LiveTranslator import LiveTranslator
from KeyManager import KeyManager
from Audio import Audio
from Config import Config

import json
import os

from Audio import Audio
from Config import Config

def test_configs():
    if Config.virtual_microphone_device_index != -1:
        return
    config_file = open("../Config.json", "r")
    if os.path.exists("../tmp/Config.json"):
        config_file = open("../tmp/Config.json", "r")

    user_configs = json.load(config_file)

    Audio.list_audio_devices()

    Config.virtual_microphone_device_index = Audio.find_device_index(Config.virtual_microphone_device_name)
    Config.output_device_index = Audio.find_device_index(Config.output_device_name)
    Utils.force_print(f"i:{Config.virtual_microphone_device_index},o:{Config.output_device_index }\nTesting audio...\n")

    Audio.play_audio("../assets/test.wav",[Config.output_device_index])

    user_configs["virtual_microphone_device_index"] = Config.virtual_microphone_device_index

    with open("../tmp/Config.json", "w") as config_file:
        config_file.write(json.dumps(user_configs, indent=4))

def main() :
    Utils.force_console_utf8()
    Utils.force_print("Initializing...\nStarting engine...\n")

    Config.LoadConfigs()
    test_configs()

    live_translator = LiveTranslator()

    keyboard_manager = KeyManager()

    keyboard_manager.add_callback("0",live_translator.start,live_translator.stop,with_ctrl=True)

    keyboard_manager.add_callback("1", live_translator.play_and_monitor,with_ctrl=True)
    keyboard_manager.add_callback("2", live_translator.create_ai_voice,with_ctrl=True)
    keyboard_manager.add_callback("3", live_translator.cycle_voices_forward,with_ctrl=True)
    keyboard_manager.add_callback("6", live_translator.cycle_voices_backward,with_ctrl=True)
    
    time.sleep(2) #delay to make sure the engine has started up
    Utils.force_print("Script started!\n")

    keyboard_manager.start(live_translator.recorder.record_callback)



if __name__ == '__main__':
    main()
