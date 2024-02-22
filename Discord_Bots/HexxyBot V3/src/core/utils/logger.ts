import { Name } from '../../config/botConfig';
import LoggingConfig from '../../config/loggingConfig';

export function info(data) {
    console.log(`
    ${ConsoleColors.fgGreen}[${Name}-INFO]${ConsoleColors.reset}
    ${data}`);
}
export function warn(data, warn) {
    console.log(`
    ${ConsoleColors.fgYellow}[${Name}-WARN]${ConsoleColors.reset}
    ${data}\n${warn}`);
}
export function error(data, err) {
    console.log(`
    ${ConsoleColors.fgRed}[${Name}-ERROR]${ConsoleColors.reset}
    ${data}\n${err}`);
}
export function command(ctx) {
    if (LoggingConfig.Commands)
        console.log(`
        ${ConsoleColors.fgMagenta}[${Name}-COMMAND]${ConsoleColors.reset}
        ${ctx.member.displayName} (${ctx.member.id}) used ${ctx.commandName} in ${ctx.guild.name} (${ctx.guild.id})`);
}

export const ConsoleColors: { [text: string]: string } = {
    reset: '\x1b[0m',
    bright: '\x1b[1m',
    dim: '\x1b[2m',
    underscore: '\x1b[4m',
    blink: '\x1b[5m',
    reverse: '\x1b[7m',
    hidden: '\x1b[8m',
    fgBlack: '\x1b[30m',
    fgRed: '\x1b[31m',
    fgGreen: '\x1b[32m',
    fgYellow: '\x1b[33m',
    fgBlue: '\x1b[34m',
    fgMagenta: '\x1b[35m',
    fgCyan: '\x1b[36m',
    fgWhite: '\x1b[37m',
    bgBlack: '\x1b[40m',
    bgRed: '\x1b[41m',
    bgGreen: '\x1b[42m',
    bgYellow: '\x1b[43m',
    bgBlue: '\x1b[44m',
    bgMagenta: '\x1b[45m',
    bgCyan: '\x1b[46m',
    bgWhite: '\x1b[47m',
};