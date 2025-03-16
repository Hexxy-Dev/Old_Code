# My Old Discord Bots

A collection of discord bots I made during the pandemic

## 🌟 Overview
- **Server_Bots/HexxyBot** was the first bot I created. It was mainly just a music bot being able to play songs from youtube.

- **Server_Bots/MudaeDB** was the second bot. It was created in parallel with HexxyBot but it's purpose was different. It read messages sent by [Mudae bot](https://mudae.fandom.com/wiki/Mudae) in order to create a local database of each player's inventory for the gatcha minigame. It periodically updated a website where players could search, filter and sort trough the inventories of others or arrange their own inventory and automatically generate the command for Mudae in order to actually set their public display.

- **HexxyWaifuRoulette** was a short lived bot that was created when Mudae bot had to partially shut down for a while when Discord started rate limiting bots due to the huge influx of traffic during the pandemic. The objective was to try to recreate the gatcha minigame to some extent and add some features that we tough would be a good addition. This bot was abandoned because soon after the rate limits, many bots switched to slash command which allowed Mudae to resume normal operations.

- **HexxyBot V2** was an experiment to use a premade bot framework.

- **HexxyBot V3** was the last bot I created and it was meant to help with server management. It would create channels, groups and roles to be able to quickly add new topics to our server turning it into a big wiki with many opt in categories. This was mostly obsoleted by Discord introducing threads.

## 🚀 Features

### Server Management
- Advanced server administration tools
- Customizable command system
- Automated moderation capabilities

### Technical Highlights
- Built with TypeScript for type safety and better development experience
- Implements Discord.js v14 for modern Discord API integration
- Modular architecture for easy extension
- Sharding support for scalability

## 🛠 Technology Stack
- **Language**: TypeScript
- **Runtime**: Node.js
- **Framework**: Discord.js v14

#### 📐 Architecture: The bots follow a modular event-driven architecture with clear separation of concerns.

---
*Note: These bots were developed as a learning project to demonstrate practical application of modern JavaScript/TypeScript development practices.* 