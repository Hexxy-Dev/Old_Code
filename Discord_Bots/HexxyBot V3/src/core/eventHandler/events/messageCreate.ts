import * as commandHandler from '../../commandHandler/commandHandler';
import { Ctx } from '../../commandHandler/Ctx';
import * as cooldownManager from '../../utils/cooldownsManager';
import * as embeds from '../../graphics/embeds';
import * as logger from '../../utils/logger';
import Config from '../../../config/commandsConfig';

module.exports = async (client, message) => {
   try {
      // Don't listen to bot messages
      if (message.author.bot) {
         return;
      }

      // Don't listen to DMs
      if (!message.guild) {
         return;
      }

      const {channel, member} = message;


      // COMMAND CHECK

      const commandCheck = await commandHandler.getCommandData(message, Config.Prefix);
      if (!commandCheck.command) {
         return;
      }

      const {command, args} = commandCheck;

      if (command.reqArgs && !args.length) {
         await channel.send(embeds.error('The command is missing some arguments'));
         return;
      }

      // COOLDOWN CHECK
      const userOnCooldown = await cooldownManager.isCmdOnCooldown(member.id, command);
      if (userOnCooldown) {
         await channel.send(embeds.error('Cool down mate'));
         return;
      }

      // EXECUTE THE COMMAND
      const ctx = new Ctx(message, command.name, args);

      const error = await commandHandler.runCommand(ctx);

      if (error) {
         await channel.send(embeds.error(`Error while executing the command ${command.name}`));
         logger.error(`Error caused by the ${ctx.commandName} command`, error);
      }
   } catch (e) {
      logger.error('Error from message event', e);
   }
};
