import Config from '../../config/commandsConfig';
import { Ctx } from '../../core/commandHandler/Ctx';
import * as CMD from '../../core/commandHandler/commandHandler';

export default {
    name: 'ReloadCommands',
    aliases: [],
    description: 'Reload ALL commands',
    reqArgs: false,
    usage: '',
    exampleUsage: 'ReloadCommands',
 
    async run(ctx : Ctx) {
        if(!ctx.hasRole(Config.BotMasterRole)) {
            ctx.sendText(`To use this command you need the "${Config.BotMasterRole}" Role`);
            return;
        }
        CMD.getAllCommands().forEach((command) => ctx.sendText(CMD.reloadCommand(command.name)));
    }
};
