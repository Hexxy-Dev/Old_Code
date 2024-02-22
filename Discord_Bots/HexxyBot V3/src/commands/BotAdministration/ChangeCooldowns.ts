import Config from '../../config/commandsConfig';
import { Ctx } from '../../core/commandHandler/Ctx';
import * as CMD from '../../core/commandHandler/commandHandler';

export default {
    name: 'ChangeCooldowns',
    aliases: [],
    description: `Change the default cooldowns for non specific commands (currently: ${Config.DefaultCooldownAmount})`,
    reqArgs: true,
    usage: 'ChangeCooldowns <NewCooldown (in ms)>',
    exampleUsage: 'ChangeCooldowns 3000 (meaning 3 seconds)',
 
    async run(ctx : Ctx) {
        if(!ctx.hasRole(Config.BotMasterRole)) {
            ctx.sendText(`To use this command you need the "${Config.BotMasterRole}" Role`);
            return;
        }
        Config.DefaultCooldownAmount = parseInt(ctx.args[0]);
        CMD.reloadCommand(this.name);
    }
};
