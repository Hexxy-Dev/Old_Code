import sounddevice as sd
import soundfile as sf
from pynput import keyboard
import numpy as np

duration = 0  # initialize recording duration to 0
samplerate = 44100  # Hz
channels = 1
chunk_size = 1024  # number of samples per chunk

# define function to handle keyboard events
def on_press(key):
    if key == keyboard.Key.esc:
        return False  # stop listener
    else:
        return True  # continue listener

# start listener
listener = keyboard.Listener(on_press=on_press)
listener.start()

buffer_size = int(samplerate * 60)  # 1 minute buffer
buffer = np.zeros((buffer_size, channels))

while listener.running:
    if duration == 0:
        stream = sd.InputStream(samplerate=samplerate, channels=channels)
        stream.start()

    chunk, overflow = stream.read(chunk_size)
    buffer = np.roll(buffer, -chunk_size, axis=0)
    buffer[-len(chunk):, :] = chunk
    duration += chunk_size / samplerate  # increment recording duration
    if overflow:
        print('Audio buffer overflow.')
    sd.sleep(1)  # wait for 1 second

# stop recording and listener
stream.stop()
stream.close()
listener.stop()

# save recorded audio to file
if duration > 0:
    # trim audio data from circular buffer to actual recording duration
    frames = buffer[-int(duration * samplerate):, :]
    filename = 'recording.wav'
    sf.write(filename, frames, samplerate, subtype='PCM_16')
    print(f'Recording saved to {filename}.')
else:
    print('No audio data recorded.')
