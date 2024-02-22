import Config from '../../config/commandsConfig';
import { Ctx } from '../../core/commandHandler/Ctx';
import * as CMD from '../../core/commandHandler/commandHandler';
import * as embeds from '../../core/graphics/embeds';

export function GetCommandInfo(command, showUsage) : string {
    let Info = `**${command.name}`;
    if(command.aliases)
        command.aliases.forEach((alias) => Info += `  ${alias}`);
    Info += `** - ${command.category}\n${command.description}`;
    if(showUsage) {
        Info += '\n\n*';
        if(command.usage != '')
            Info += `Usage: ${Config.Prefix}${command.usage}\n`;
        Info += `Example: ${Config.Prefix}${command.exampleUsage}*\n`;
    }
    Info += '\n\n';
    return Info;
}

export default {
    name: 'info',
    aliases: [],
    description: 'List all information about a certain command',
    reqArgs: true,
    usage: 'info <commandName>',
    exampleUsage: 'info help',
    cooldown: 300,
 
    async run(ctx : Ctx) {
        const command = CMD.getCommand(ctx.args[0]);
        if(command)
            ctx.channel.send(embeds.customEmbed(GetCommandInfo(command, true),'Info'));
    }
};
