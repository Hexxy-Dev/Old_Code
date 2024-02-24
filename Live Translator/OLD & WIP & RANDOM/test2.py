import sounddevice as sd
import soundfile as sf
import numpy as np

filename = '../voice.wav'

# Load the audio file
monodata, fs = sf.read(filename, dtype='float32', always_2d=True)

data = np.column_stack((monodata, monodata))

# Get a list of available output devices
devices = sd.query_devices()
for device in devices:
    print(device)

print(data.shape)
# Select the two devices you want to use
device_ids = [21]
blocksize = 4096

# Open an output stream for each device
streams = [sd.OutputStream(device=device_id, channels=2, blocksize=blocksize) for device_id in device_ids]

# Start both streams
for stream in streams:
    stream.start()

# Write the audio data to both streams

samples_written = 0
while samples_written < len(data):
    samples_left = len(data) - samples_written
    blocksize = min(blocksize, samples_left)
    for stream in streams:
        stream.write(data[samples_written:samples_written+blocksize])
    samples_written += blocksize

# Wait until both streams are finished
for stream in streams:
    stream.stop()
    stream.close()