import openai
import deepl
from voicevox import Client

import threading
import asyncio

from Config import Config
from Audio import Audio
from Audio import AudioRecorder

from Utils import Utils

class LiveTranslator:
    def __init__(self):
        self.japanese_text = Config.default_output_text
        self.selected_voice = Config.available_voices[Config.starting_voice_index]["index"]
        self.selected_voice_index = Config.starting_voice_index

        self.recording_path = "../tmp/recording.wav"
        self.voice_path = "../tmp/voice.wav"

        self.recorder = AudioRecorder(self.recording_path)

        self.print_character_name()

        self.translator = deepl.Translator(Config.deepl_auth_key)

    def start(self):
        self.recorder.start_recording()
        
    def stop(self):
        self.recorder.stop_recording()
        
        audio_file= open(self.recording_path, "rb")
        transcript = openai.Audio.transcribe("whisper-1",
                                            audio_file,
                                            language = Config.input_language,
                                            response_format = "text")

        Utils.force_print("[USER]:",transcript,"\n")

        result = self.translator.translate_text(transcript, target_lang=Config.output_language)

        self.japanese_text = result.text

        Utils.force_print("[JAPANESE]:",self.japanese_text,"\n")

        self.create_ai_voice()
        Utils.force_print("Audio Created!\n")

        self.play_and_monitor()

    def play_and_monitor(self):
        Audio.play_audio_and_monitor(self.voice_path)

    async def create_ai_voice_async(self):
        async with Client() as client:
            audio_query = await client.create_audio_query(
                text=self.japanese_text, speaker=self.selected_voice
            )
            audio_query.output_sampling_rate = Config.sample_rate
            with open(self.voice_path, "wb") as f:
                f.write(await audio_query.synthesis(speaker=self.selected_voice))
        Utils.force_print("Created!\n")

    def create_ai_voice(self):
        asyncio.run(self.create_ai_voice_async())

    def cycle_voices_forward(self):
        self.selected_voice_index = (self.selected_voice_index + 1) % len(Config.available_voices)
        
        self.selected_voice = Config.available_voices[self.selected_voice_index]["index"]

        self.print_character_name()

    def cycle_voices_backward(self):
        self.selected_voice_index = (self.selected_voice_index - 1)
        if self.selected_voice_index < 0:
            self.selected_voice_index = len(Config.available_voices) - 1

        self.selected_voice = Config.available_voices[self.selected_voice_index]["index"]

        self.print_character_name()
        
    def print_character_name(self):
        Utils.force_print("selected voice: ",Config.available_voices[self.selected_voice_index]["name"],"\n")
