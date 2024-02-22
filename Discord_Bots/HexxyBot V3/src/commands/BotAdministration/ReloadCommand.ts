import Config from '../../config/commandsConfig';
import { Ctx } from '../../core/commandHandler/Ctx';
import * as CMD from '../../core/commandHandler/commandHandler';

export default {
    name: 'ReloadCommand',
    aliases: [],
    description: 'Reload specific command (meant for rapid testing)',
    reqArgs: true,
    usage: 'ReloadCommand <CommandName>',
    exampleUsage: 'ReloadCommand help',
 
    async run(ctx : Ctx) {
        if(!ctx.hasRole(Config.BotMasterRole)) {
            ctx.sendText(`To use this command you need the "${Config.BotMasterRole}" Role`);
            return;
        }
        ctx.sendText(CMD.reloadCommand(ctx.args[0]));
    }
};