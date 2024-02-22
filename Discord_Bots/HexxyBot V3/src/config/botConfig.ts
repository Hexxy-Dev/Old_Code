import { ActivityType, GatewayIntentBits } from 'discord.js';
let BotConfig = {
    Status: "!!!WIP!!!",
    StatusType: ActivityType.Playing
};
export default BotConfig;

export const Name = "HexxyBot";

export const Token = ""; // REDACTED
export const Intents = [
    GatewayIntentBits.Guilds,
    GatewayIntentBits.GuildMessages,
    GatewayIntentBits.MessageContent
];