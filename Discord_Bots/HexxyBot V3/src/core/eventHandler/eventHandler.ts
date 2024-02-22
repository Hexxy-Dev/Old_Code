import * as path from 'path';
import * as RequireAll from 'require-all';
import * as Logger from '../utils/logger';
import BotConfig from '../../config/botConfig';

let discordClient;

export function init(client, args = { launchTimestamp: Date.now() }) {
    discordClient = client;
    this.initEssentialEvents(client, args);
    this.initEvents(client);
};

export function initEssentialEvents(client = discordClient, args = { launchTimestamp: Date.now() }) {
    // Ready event, which gets fired only once when the bot reaches the ready state
    client.once('ready', async () => {
        const updateBotStatus = async () => {
            await client.user.setActivity(BotConfig.Status, { type: BotConfig.StatusType });
        };

        await updateBotStatus();
        // Updates the bot status every hour
        setInterval(() => updateBotStatus(), 3600000);

        Logger.info(`Successfully launched in ${(Date.now() - args.launchTimestamp) / 1000} seconds!`);
    });

    /* Raw listener for messageReactionAdd event
        Uncomment the following code if you need your bot
        to listen to messageReactionAdd events on uncached messages
    */
    //client.on('raw', async (event) => {
    //    // Listen only to reactionAdd events
    //    if (event.t !== 'MESSAGE_REACTION_ADD') {
    //        return;
    //    }
    //
    //    const { d: data } = event;
    //    if (typeof client.channels.cache.get(data.channel_id) === 'undefined') {
    //        return;
    //    }
    //
    //    const channel = await client.channels.fetch(data.channel_id);
    //
    //    // if the message is already in the cache, don't re-emit the event
    //    if (channel.messages.cache.has(data.message_id)) {
    //        return;
    //    }
    //
    //    const user = await client.users.fetch(data.user_id);
    //    const message = await channel.messages.fetch(data.message_id);
    //    // Custom emoji are keyed by IDs, while unicode emoji are keyed by names
    //    const reaction = message.reactions.resolve(data.emoji.id || data.emoji.name);
    //
    //    client.emit('messageReactionAdd', reaction, user);
    //});

    // Some other somewhat important events that the bot should listen to
    client.on('error', (err) => Logger.error('The client threw an error', err));

    client.on('shardError', (err) => Logger.error('A shard threw an error', err));

    client.on('warn', (warn) => Logger.warn('The client received a warning', warn));
};

export function initEvents(client = discordClient) {
    const events = Object.entries(
        RequireAll({
            dirname: path.join(__dirname, 'events'),
            filter: /^(?!-)(.+)\.js$/
        }),
    );
    //                                       name                   function
    events.forEach((event: any) => client.on(event[0], eventdata => event[1](client, eventdata)));
};