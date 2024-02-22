const logger = require('../core/utils/logger');

const Discord = require('discord.js');
const { ChannelType } = require('discord.js');

module.exports = {
    name: 'createTemplate',
    aliases: [],
    description: '',
    reqArgs: true,
    usage: '',
    exampleUsage: '',
    category: 'Misc',
    cooldown: 3000,
 
    async run(ctx) {
        hmm = await ctx.guild.channels.create({name:ctx.args[0], type: ChannelType.GuildCategory});
        ctx.guild.channels.create({name:ctx.args[0], type: ChannelType.GuildText, parent: hmm.id});
    }
 };
 