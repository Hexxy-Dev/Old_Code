import * as Discord from 'discord.js';
import Config from '../../config/commandsConfig';

const cooldowns = new Discord.Collection();

export async function isCmdOnCooldown(userID, command) {
    if (!Config.CooldownsEnabled)
        return false;

    if (!cooldowns.has(command.name))
        cooldowns.set(command.name, new Discord.Collection());

    const now = Date.now();
    const timestamps: any = cooldowns.get(command.name);
    const cooldownAmount = (command.cooldown || Config.DefaultCooldownAmount);

    if (timestamps.has(userID)) {
        const expirationTime = timestamps.get(userID) + cooldownAmount;

        if (now < expirationTime)
            return true;
    }

    timestamps.set(userID, now);
    return false;
}