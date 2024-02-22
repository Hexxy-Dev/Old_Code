const launchTimestamp = Date.now();

import * as Discord from 'discord.js';
import { GatewayIntentBits } from 'discord.js';
import * as Logger from './core/utils/logger';
import * as EventManager from './core/eventHandler/eventHandler';
import { Token, Intents } from './config/botConfig';

export const client = new Discord.Client({
    intents: Intents
});

EventManager.init(client, { launchTimestamp });

client.login(Token)
        .then(() => Logger.info('Logged into Discord successfully'))
        .catch((err) => {
            Logger.error('Error logging into Discord', err);
            process.exit();
        });
