//...

const Discord = require('discord.js');
const { GatewayIntentBits } = require('discord.js');
//...
   intents: [
      GatewayIntentBits.Guilds,
      GatewayIntentBits.GuildMessages,
      GatewayIntentBits.MessageContent
   ]
//...