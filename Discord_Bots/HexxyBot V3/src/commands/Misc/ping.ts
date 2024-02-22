import Config from '../../config/commandsConfig';
import { Ctx } from '../../core/commandHandler/Ctx';

export default {
    name: 'ping',
    aliases: [],
    description: 'PONG!!',
    reqArgs: false,
    usage: '',
    exampleUsage: 'ping',
 
    async run(ctx : Ctx) {
       ctx.sendText("PONG");
    }
};
 