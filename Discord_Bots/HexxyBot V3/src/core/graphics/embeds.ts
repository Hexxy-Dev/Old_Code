import { ColorResolvable, EmbedBuilder } from 'discord.js';
import Colors from './colors';
import Config from '../../config/commandsConfig';

export function customEmbed(description, title = ' ', color : ColorResolvable = Colors.Primary, footer = ' ') {
    return {
        embeds: [
            new EmbedBuilder()
            .setColor(color)
            .setTitle(title)
            .setDescription(description)
            .setFooter({ text: footer})
        ]
    };
}

export function info(description, color : ColorResolvable = Colors.Primary) {
    return {
        embeds: [
            new EmbedBuilder()
            .setColor(color)
            .setTitle('Info')
            .setDescription(description)
            .setFooter({ text: `Use ${Config.Prefix}help for support` })
        ]
    };
}
export function warn(description) {
    return {
        embeds: [
            new EmbedBuilder()
            .setColor(Colors.Warn)
            .setTitle('Warning')
            .setDescription(description)
            .setFooter({ text: `Use ${Config.Prefix}help for support` })
        ]
    };
}
export function error(description) {
    return {
        embeds: [
            new EmbedBuilder()
            .setColor(Colors.Error)
            .setTitle('Error')
            .setDescription(description)
            .setFooter({ text: `Use ${Config.Prefix}help for support` })
        ]
    };
}
