import Config from '../../config/commandsConfig';
import { ChannelType, PermissionsBitField } from 'discord.js';
import { Ctx } from '../../core/commandHandler/Ctx';

export default {
    name: 'createTemplate',
    aliases: [],
    description: 'Create category and text channel with given name',
    reqArgs: true,
    usage: 'createTemplate <TemplateName>',
    exampleUsage: 'createTemplate C++',
 
    async run(ctx : Ctx) {
        if(!ctx.hasRole(Config.AdminRole)) {
            ctx.sendText(`To use this command you need the "${Config.AdminRole}" Role`);
            return;
        }

        const TemplateName : string = ctx.args[0];

        const TemplateNameRole = await ctx.guild.roles.create({
            name: TemplateName,
            color: 'Default',
        });

        const TemplateCategory = await ctx.guild.channels.create({
            name:TemplateName, type: ChannelType.GuildCategory,
            permissionOverwrites: [{
                id: TemplateNameRole,
                allow: PermissionsBitField.resolve([
                   "ViewChannel"
                ])
            }]
        });
        await ctx.guild.channels.create({name:TemplateName, type: ChannelType.GuildVoice, parent: TemplateCategory.id});
        await ctx.guild.channels.create({name:TemplateName, type: ChannelType.GuildText, parent: TemplateCategory.id});
        await ctx.guild.channels.create({name:'Resources', type: ChannelType.GuildText, parent: TemplateCategory.id});
        await ctx.guild.channels.create({name:'Questions', type: ChannelType.GuildText, parent: TemplateCategory.id});
    }
};