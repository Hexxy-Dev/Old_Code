import openai
import deepl

import json
import os

class config:
    def __init__(self):
        self.frame_chunk_size = 1024 #TODO: add auto setup for audio devices and allow override
        self.sample_rate = 51200
        self.block_size = 4096
        self.channels = 2
        self.buffer_size = 60 # seconds

        self.virtual_microphone_device_index = -1
        self.output_device_index = -1
        self.virtual_microphone_device_name = "NULL"
        self.output_device_name = "NULL"

        self.monitor_audio = False
        self.output_audio_to_microphone = False

        self.available_voices = [
            {"name": "Shikoku Metan - normal",              "index": 2},
            {"name": "Shikoku Metan - sweet",               "index": 0},
            {"name": "Shikoku Metan - tsun tsun",           "index": 6},
            {"name": "Shikoku Metan - sexy",                "index": 4},
            {"name": "Shikoku Metan - breathy whisper",     "index": 36},
            {"name": "Shikoku Metan - soft whisper",        "index": 37},
            {"name": "Zundamon - normal",                   "index": 3},
            {"name": "Zundamon - sweet",                    "index": 1},
            {"name": "Zundamon - tsun tsun",                "index": 7},
            {"name": "Zundamon - sexy",                     "index": 5},
            {"name": "Zundamon - breathy whisper",          "index": 22},
            {"name": "Zundamon - soft whisper",             "index": 38},
            {"name": "Tsumugi Kasukabe - normal",           "index": 8},
            {"name": "Rainy Configro Shirakami - bien",     "index": 35},
            {"name": "Ryuusei Aoyama - normal",             "index": 13},
            {"name": "Himari - normal",                     "index": 14},
            {"name": "Kyushu Sky - normal",                 "index": 16},
            {"name": "Kyushu Sky - sweet",                  "index": 15},
            {"name": "Kyushu Sky - tsun tsun",              "index": 18},
            {"name": "Kyushu Sky - sexy",                   "index": 17},
            {"name": "Kyushu Sky - breathy whisper",        "index": 19},
            {"name": "Mochiko - normal",                    "index": 20},
            {"name": "Kenzaki - normal",                    "index": 21},
            {"name": "WhiteCUL - normal",                   "index": 23},
            {"name": "WhiteCUL - fun",                      "index": 24},
            {"name": "WhiteCUL - sad",                      "index": 25},
            {"name": "WhiteCUL - bien",                     "index": 26},
            {"name": "Goki - human ver.",                   "index": 27},
            {"name": "Goki - plush ver.",                   "index": 28},
            {"name": "No.7 - normal",                       "index": 29},
            {"name": "No.7 - announcement",                 "index": 30},
            {"name": "No.7 - story telling",                "index": 31},
            {"name": "Little old man - normal",             "index": 42},
            {"name": "Sakuraka Miko - normal",              "index": 43},
            {"name": "Sakuraka Miko - second form",         "index": 44},
            {"name": "Sakuraka Miko - loli",                "index": 45},
            {"name": "Sayo - normal",                       "index": 46},
            {"name": "Nurse Robo Type T - normal",          "index": 47},
            {"name": "Nurse Robo Type T - easily",          "index": 48},
            {"name": "Nurse Robo Type T - fear",            "index": 49},
            {"name": "Nurse Robo Type T - secret story",    "index": 50}
        ]

        self.openai_api_key = ""
        self.deepl_auth_key = ""

        self.input_language = ""
        self.output_language = ""

        self.starting_voice_index = 0
        self.default_output_text = ""

    def LoadConfigs(self):
        config_file = open("../Config.json", "r")
        if os.path.exists("../tmp/Config.json"):
            config_file = open("../tmp/Config.json", "r")
            
        user_configs = json.load(config_file)

        self.openai_api_key = user_configs["openai_api_key"]
        self.deepl_auth_key = user_configs["deepl_auth_key"]

        self.input_language = user_configs["input_language"]
        self.output_language = user_configs["output_language"]
        self.default_output_text = user_configs["default_output_text"]

        self.monitor_audio = user_configs["monitor_audio"]
        self.output_audio_to_microphone = user_configs["output_audio_to_microphone"]

        self.frame_chunk_size = user_configs["frame_chunk_size"]
        self.sample_rate = user_configs["sample_rate"]
        self.channels = user_configs["channels"]

        self.block_size = user_configs["block_size"]
        self.buffer_size = user_configs["buffer_size"]

        self.virtual_microphone_device_name = user_configs["virtual_microphone_device_name"]
        self.output_device_name = user_configs["output_device_name"]


        openai.api_key = Config.openai_api_key

Config = config()
