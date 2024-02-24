import pyaudio
import wave

import threading
import asyncio

from Config import Config
from Utils import Utils

class AudioRecorder:
    def __init__(self, filename):
        self.filename = filename
        
        self.frames = []
        self.recording_event = threading.Event()
        self.sample_format = pyaudio.paInt16

        self.chunk = Config.frame_chunk_size
        self.channels = Config.channels
        self.sample_rate = Config.sample_rate

    def reset():
        self.frames = []
        self.recording_event.clear()

    def start_recording(self):
        p = pyaudio.PyAudio()

        stream = p.open(format=self.sample_format,
                        channels=self.channels,
                        rate=self.sample_rate,
                        frames_per_buffer=self.chunk,
                        input=True)

        while not self.recording_event.is_set():
            data = stream.read(self.chunk)
            self.frames.append(data)

        stream.stop_stream()
        stream.close()
        
        p.terminate()

        self.save_recording()

    def save_recording(self):
        p = pyaudio.PyAudio()

        wf = wave.open(self.filename, 'wb')
        wf.setnchannels(self.channels)
        wf.setsampwidth(p.get_sample_size(self.sample_format))
        wf.setframerate(self.sample_rate)
        wf.writeframes(b''.join(self.frames))
        wf.close()

        p.terminate()

    def stop_recording(self):
        self.recording_event.set()



class audio:
    def play_audio_async(self,output_device_index, path):
        asyncio.run(self.play_audio(output_device_index, path))

    async def play_audio(self,output_device_index, path):
        wf = wave.open(path, 'rb')

        p = pyaudio.PyAudio()

        return

        if output_device_index == -1:
            stream = p.open(format=p.get_format_from_width(wf.getsampwidth()),
                            channels=wf.getnchannels(),
                            rate=wf.getframerate(),
                            output=True)#TODO: FIX
        else:
            stream = p.open(format=p.get_format_from_width(wf.getsampwidth()),
                            channels=wf.getnchannels(),
                            rate=wf.getframerate(),
                            output=True,
                            output_device_index=output_device_index)

        data = wf.readframes(Config.frame_chunk_size)

        while data != b'':
            stream.write(data)
            data = wf.readframes(Config.frame_chunk_size)

        stream.stop_stream()
        stream.close()

        p.terminate()

    def play_audio_and_monitor(self,path):
        if Config.output_audio_to_microphone:
            self.play_audio_async(Config.virtual_microphone_device_index, path)
        if Config.monitor_audio:
            self.play_audio_async(22, path)

    def list_audio_devices(self):
        p = pyaudio.PyAudio()

        device_count = p.get_device_count()

        Utils.force_print(f"Number of audio devices: {device_count}\n")

        for i in range(device_count):
            device_info = p.get_device_info_by_index(i)
            Utils.force_print(f"Device index {i}: {device_info['name']}\n")

Audio = audio()