import numpy as np
import sounddevice as sd
import soundfile as sf

import time
import asyncio

from Config import Config
from Utils import Utils

class AudioRecorder:
    def __init__(self, filename):
        self.filename = filename
        self.is_recording = False
        self.is_stopped = False
        self.reset()

    def reset(self):
        self.duration = 0
        self.buffer = np.zeros((int(Config.sample_rate * Config.buffer_size), Config.channels))

    def start_recording(self):
        self.reset()
        Utils.force_print("Started recording...\n")
        self.stream = sd.InputStream(samplerate=Config.sample_rate, channels=Config.channels)
        self.stream.start()
        self.is_recording = True

    def record_callback(self):
        self.is_stopped = True
        if self.is_recording:
            self.is_stopped = False
            chunk, overflow = self.stream.read(Config.frame_chunk_size)
            self.buffer = np.roll(self.buffer, -Config.frame_chunk_size, axis=0)
            self.buffer[-len(chunk):, :] = chunk
            self.duration += Config.frame_chunk_size / Config.sample_rate
            if overflow:
                Utils.force_print('Audio buffer overflow.\n')

    def stop_recording(self):
        if self.duration > 0:
            self.is_recording = False
            while not self.is_stopped:
                time.sleep(0)
            self.is_stopped = False
            self.stream.stop()
            self.stream.close()
            

            Utils.force_print(f'Recording saved to {self.filename}.\n')
            self.save_recording()
        else:
            Utils.force_print('No audio data recorded.\n')

    def save_recording(self):
        frames = self.buffer[-int(self.duration * Config.sample_rate):, :]
        sf.write(self.filename, frames, Config.sample_rate, subtype='PCM_16')


class audio:
    def play_audio(self, path, device_ids):
        data, fs = sf.read(path, dtype='float32', always_2d=True)

        if data.shape != Config.channels:
            data = np.column_stack((data, data)) #make from mono to stereo

        streams = [sd.OutputStream(device=device_id, channels=Config.channels, blocksize=Config.block_size) for device_id in device_ids]

        for stream in streams:
            stream.start()

        samples_written = 0
        blocksize = Config.block_size
        while samples_written < len(data):
            samples_left = len(data) - samples_written
            blocksize = min(blocksize, samples_left)
            for stream in streams:
                stream.write(data[samples_written:samples_written+blocksize])
            samples_written += blocksize

        for stream in streams:
            stream.stop()
            stream.close()

    def play_audio_and_monitor(self,path):
        devices = []
        if Config.output_audio_to_microphone:
            devices.append(Config.virtual_microphone_device_index)

        if Config.monitor_audio:
            devices.append(Config.output_device_index)

        self.play_audio(path,devices)

    def list_audio_devices(self):
        print(sd.query_devices())

    def find_device_index(self,name):
        devices = sd.query_devices()
        for device in devices:
            if name in device["name"]:
                return device["index"]
            
Audio = audio()