# -*- coding: utf-8 -*-
from voicevox import Client

import sys
import io

if __name__ == "__main__":
    sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
    
    with Client() as client:
        for speaker in await client.fetch_speakers():
            print(speaker.name)
            for style in speaker.styles:
                print(style.id)
                print(style.name)