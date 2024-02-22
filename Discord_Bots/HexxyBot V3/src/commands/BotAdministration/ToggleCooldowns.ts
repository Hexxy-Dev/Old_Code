import Config from '../../config/commandsConfig';
import { Ctx } from '../../core/commandHandler/Ctx';

export default {
    name: 'ToggleCooldowns',
    aliases: [],
    description: 'Toggle cooldowns for all commands',
    reqArgs: false,
    usage: '',
    exampleUsage: 'ToggleCooldowns',
 
    async run(ctx : Ctx) {
        if(!ctx.hasRole(Config.BotMasterRole)) {
            ctx.sendText(`To use this command you need the "${Config.BotMasterRole}" Role`);
            return;
        }
        Config.CooldownsEnabled = !Config.CooldownsEnabled;
    }
};
