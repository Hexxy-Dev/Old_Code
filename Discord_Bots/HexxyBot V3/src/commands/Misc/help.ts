import Config from '../../config/commandsConfig';
import { Ctx } from '../../core/commandHandler/Ctx';
import * as CMD from '../../core/commandHandler/commandHandler';
import * as embeds from '../../core/graphics/embeds';
import { GetCommandInfo } from './info';

export default {
    name: 'help',
    aliases: ['h'],
    description: `List available commands
    Options: LIST_ALL - List all commands even those that you do not have access to, u - List usage `,
    reqArgs: false,
    usage: 'help [options]',
    exampleUsage: 'help u LIST_ALL',
    cooldown: 300,
 
    async run(ctx : Ctx) {
        let args = ctx.args.join();
        let HelpMessage = '';
        const commands = CMD.getAllCommands();
        commands.forEach((command) => {
            if(args.indexOf('LIST_ALL') == -1) {
                if(command.category == 'BotAdministration')
                    if(!ctx.hasRole(Config.BotMasterRole))
                        return;
                if(command.category == 'ServerManagement')
                    if(!ctx.hasRole(Config.AdminRole))
                        return;
                if(command.name == 'mention')
                    return;
            }
            if(args.indexOf('u') != -1)
                HelpMessage += GetCommandInfo(command,true);
            else
                HelpMessage += GetCommandInfo(command,false);
        });
        
        ctx.channel.send(embeds.customEmbed(HelpMessage,'Help'));
    }
};
