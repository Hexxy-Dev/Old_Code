# -*- coding: utf-8 -*-
import sys
import io

if __name__ == "__main__":
    sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
    
    f = open("voices.txt", "r", encoding='utf-8')
    lines = f.readlines()

    i = 0
    indexes = ""

    while i < len(lines):
        japName = lines[i].strip()
        engName = lines[i+1].strip()
        i += 2
        while lines[i].strip() != "":
            index = lines[i].strip()
            japStyle = lines[i+1].strip()
            engStyle = lines[i+2].strip()
            i += 3
            print(f"{{\"name\": \"{engName} - {engStyle}\",\"index\": {index}}},")
        i += 1