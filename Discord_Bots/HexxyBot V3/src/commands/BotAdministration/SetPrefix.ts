import Config from '../../config/commandsConfig';
import { Ctx } from '../../core/commandHandler/Ctx';

export default {
    name: 'SetPrefix',
    aliases: [],
    description: 'Change the prefix for all commands',
    reqArgs: true,
    usage: 'SetPrefix <NewPrefix>',
    exampleUsage: 'SetPrefix !',
 
    async run(ctx : Ctx) {
        if(!ctx.hasRole(Config.BotMasterRole)) {
            ctx.sendText(`To use this command you need the "${Config.BotMasterRole}" Role`);
            return;
        }
        Config.Prefix = ctx.args[0];
    }
};
