import Config from '../../config/commandsConfig';
import LoggingConfig from '../../config/loggingConfig';
import { Ctx } from '../../core/commandHandler/Ctx';

export default {
    name: 'ToggleLogging',
    aliases: [],
    description: 'Toggle console logging for all commands',
    reqArgs: false,
    usage: '',
    exampleUsage: 'ToggleLogging',
 
    async run(ctx : Ctx) {
        if(!ctx.hasRole(Config.BotMasterRole)) {
            ctx.sendText(`To use this command you need the "${Config.BotMasterRole}" Role`);
            return;
        }
        LoggingConfig.Commands = !LoggingConfig.Commands;
    }
};
