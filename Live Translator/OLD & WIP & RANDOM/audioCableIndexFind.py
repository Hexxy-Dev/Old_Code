import pyaudio
import wave

p = pyaudio.PyAudio()

device_count = p.get_device_count()

print(f"Number of audio devices: {device_count}")

for i in range(device_count):
    device_info = p.get_device_info_by_index(i)
    print(f"Device index {i}: {device_info['name']}")