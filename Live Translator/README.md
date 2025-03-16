# Live Voice Translator

A real-time voice translation tool that enables trolling in voice chats using cutting-edge AI technology. This project combines speech recognition, language translation, and AI voice synthesis to create an easy to use tool to fool around with your friends.

## 🌟 Features

- **AI Voice Synthesis**: Convert translated text into natural-sounding speech using VOICEVOX
- **Multiple Voice Options**: Choose from various AI voice characters
- **Simple Controls**: Easy-to-use keyboard shortcuts for all functions
- **Low Latency**: Quick response times for natural conversation flow

## 🚀 Quick Demo

1. Hold `CTRL+0` to record your voice
2. Release to automatically:
   - Transcribe your speech
   - Translate it to Japanese
   - Generate AI voice output
3. Press `CTRL+1` to play the translated audio
4. Use `CTRL+3` and `CTRL+6` to cycle through different AI voices

["Noom noom..." sound sample](https://github.com/Hexxy-Dev/Old_Code/assets/159670889/eb735d33-0f58-49e1-b9fc-72e8b780b19f) (meant to demonstrate pitch and tempo)

## 🛠️ Technical Stack

- **Speech Recognition**: OpenAI Whisper API
- **Translation**: DeepL API
- **Voice Synthesis**: VOICEVOX Engine
- **Language Support**: English to Japanese (expandable)
- **Audio Processing**: Python audio libraries
- **Platform**: Linux/Git-Bash compatible

## 📋 Prerequisites

- Linux or Git-Bash on Windows
- OpenAI API Key (for Whisper)
- DeepL API Key
- Python 3.x
- VOICEVOX Engine (running locally)

## 💻 Installation

1. Clone the repository
2. Navigate to the `utils` folder
3. Run the installation script:
   ```bash
   # For Linux
   ./install.sh
   # For Windows (Git-Bash)
   ./install.bat
   ```
4. Configure your settings in `Config.json`:
   - Add your API keys
   - Set audio device names
   - Adjust voice preferences

## ⚙️ Configuration

The `Config.json` file allows you to customize:
- API keys
- Input/Output audio devices
- Default voice settings
- Language preferences
- Audio quality parameters

## 🎮 Controls Reference

| Shortcut | Action | Description |
|----------|--------|-------------|
| `CTRL+0` | Hold | Record and translate speech |
| `CTRL+1` | Press | Play translated audio |
| `CTRL+2` | Press | Generate AI voice |
| `CTRL+3` | Press | Next voice |
| `CTRL+6` | Press | Previous voice |

## 🙏 Acknowledgments

- Inspired by [this YouTube video](https://www.youtube.com/watch?v=UY7sRB60wZ4)
- Made in collaboration with [Dan](https://github.com/danDrilea)