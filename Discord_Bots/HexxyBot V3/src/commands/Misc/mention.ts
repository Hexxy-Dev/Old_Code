import Config from '../../config/commandsConfig';
import { Ctx } from '../../core/commandHandler/Ctx';
import * as CMD from '../../core/commandHandler/commandHandler';
import * as embeds from '../../core/graphics/embeds';

export default {
    name: 'mention',
    aliases: [],
    description: 'Nothing to see here...',
    reqArgs: false,
    usage: '',
    exampleUsage: 'HMMMM',
 
    async run(ctx : Ctx) {
        ctx.sendText('Don\'t do that!');
    }
};
