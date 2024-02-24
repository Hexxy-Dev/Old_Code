import numpy as np
import sounddevice as sd
import soundfile as sf

import time
import asyncio

#chunk_size = 1024

class AudioRecorder:
    def __init__(self, filename):
        self.filename = filename
        self.is_recording = False
        self.is_stopped = False
        self.reset()

    def reset(self):
        self.duration = 0
        self.buffer = np.zeros((int(44100 * 60), 2))

    def start_recording(self):
        self.reset()
        print("Started recording")
        self.stream = sd.InputStream(samplerate=44100, channels=2)
        self.stream.start()
        self.is_recording = True

    def record_callback(self):
        self.is_stopped = True
        if self.is_recording:
            self.is_stopped = False
            chunk, overflow = self.stream.read(1024)
            self.buffer = np.roll(self.buffer, -1024, axis=0)
            self.buffer[-len(chunk):, :] = chunk
            self.duration += 1024 / 44100
            if overflow:
                print('Audio buffer overflow.')

    def stop_recording(self):
        if self.duration > 0:
            self.is_recording = False
            while not self.is_stopped:
                time.sleep(0)
            self.is_stopped = False
            self.stream.stop()
            self.stream.close()
            

            print(f'Recording saved to {self.filename}.')
            self.save_recording()
        else:
            print('No audio data recorded.')

    def save_recording(self):
        frames = self.buffer[-int(self.duration * 44100):, :]
        sf.write(self.filename, frames, 44100, subtype='PCM_16')
            
            
        
class audio:
    def play_audio(self, path, device_ids):
        data, fs = sf.read(path, dtype='float32', always_2d=True)

        if data.shape == 1:
            data = np.column_stack((data, data)) #make from mono to stereo

        streams = [sd.OutputStream(device=device_id, channels=2, blocksize=4096) for device_id in device_ids]

        for stream in streams:
            stream.start()

        samples_written = 0
        while samples_written < len(data):
            samples_left = len(data) - samples_written
            blocksize = min(4096, samples_left)
            for stream in streams:
                stream.write(data[samples_written:samples_written+blocksize])
            samples_written += blocksize

        for stream in streams:
            stream.stop()
            stream.close()

    def play_audio_and_monitor(self,path):
        self.play_audio(path,[21,22])

    def list_audio_devices(self):
        print(sd.query_devices())








Audio = audio()
Audio.list_audio_devices()
#Audio.play_audio_and_monitor("./recorded.wav")




rec = AudioRecorder("./recording.wav")

def noom():
    print("NOOOM")

man = KeyManager()
man.add_callback('v',rec.start_recording,rec.stop_recording)
man.add_callback('1',noom,with_ctrl=True)
print(man.key_info)
man.start(rec.record_callback)
print("HMMMMMMM")
