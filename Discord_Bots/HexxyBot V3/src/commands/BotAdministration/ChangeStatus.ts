import Config from '../../config/commandsConfig';
import { Ctx } from '../../core/commandHandler/Ctx';
import BotConfig from '../../config/botConfig';
import { Name } from '../../config/botConfig';
import * as embeds from '../../core/graphics/embeds';
import { client } from '../../bot';
import * as CMD from '../../core/commandHandler/commandHandler';

const ActivityNames : string[] = [
    'Playing',
    'Streaming',
    'Listening',
    'Watching',
    'Custom',
    'Competing'
];

export default {
    name: 'ChangeStatus',
    aliases: [],
    description: `Change the current status of ${Name} - Current status: ${ActivityNames[BotConfig.StatusType]} ${BotConfig.Status}
    Valid activities: Playing, Streaming, Listening, Watching, Competing`,
    reqArgs: true,
    usage: 'ChangeStatus <NewStatusType> <NewStatusText>',
    exampleUsage: 'ChangeStatus Playing !!!READY!!!',
 
    async run(ctx : Ctx) {
        if(!ctx.hasRole(Config.BotMasterRole)) {
            ctx.sendText(`To use this command you need the "${Config.BotMasterRole}" Role`);
            return;
        }
        if(ActivityNames.indexOf(ctx.args[0]) == -1 || ActivityNames.indexOf(ctx.args[0]) == 4) {
            ctx.channel.send(embeds.error('Not a valid status type'));
            return;
        }
        BotConfig.StatusType = ActivityNames.indexOf(ctx.args[0]);
        BotConfig.Status = ctx.args[1];
        //@ts-ignore
        client.user.setActivity(BotConfig.Status, { type: BotConfig.StatusType });
        CMD.reloadCommand(this.name);
    }
};
