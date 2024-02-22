import * as fs from 'fs';
import * as path from 'path';
import * as Discord from 'discord.js';
import * as Logger from '../utils/logger';

type Command = {
    name: string
    aliases: string[]
    description: string
    reqArgs: boolean
    usage: string
    exampleUsage: string
    category: string
    cooldown: number
    
    run: (ctx) => void
};

// Discord collection are simply an extended map (https://discord.js.org/#/docs/collection/master/class/Collection)
const commands = new Discord.Collection<string,Command>();

// Function to require all the commands from the commands folder recursively
// and adds them to the commands collection
function registerCommands(dir : string) {
   fs.readdir(dir, (e, files) => {
        if (e) {
            throw e;
        }

        files.forEach((file) => {
            const filepath = path.resolve(dir, file);

            fs.stat(filepath, (_, stats) => {
                if (stats.isDirectory()) {
                    registerCommands(filepath);
                } else if (stats.isFile() && file.endsWith('.js')) {
                    const command : Command = require(filepath).default;
                    command.category = dir.substring(CommandsDirPath.length+1,dir.length);

                    // Check for duplicate command names
                    if (commands.has(command.name.toLowerCase())) {
                        Logger.error(`Command name duplicate: ${command.name}`,``);
                        process.exit();
                    }
                    // Check for duplicate command aliases
                    if (commands.some((cmd : Command) => cmd.aliases.some((a) => command.aliases.includes(a)))) {
                        Logger.error(`Command alias duplicate: ${command.aliases}`,``);
                        process.exit();
                    }

                    commands.set(command.name.toLowerCase(), command);
                }
            });
        });
    });
}
const CommandsDirPath = path.join(__dirname, '../../commands');
registerCommands(CommandsDirPath);

export async function getCommandData(message, prefix) {
    const msgContent = message.content;
    let command;
    let args;

    // Checks if the message contains only the bot mention
    if (msgContent.trim().toLowerCase() === `<@!${message.client.user.id}>`
        || msgContent.trim().toLowerCase() === `<@${message.client.user.id}>`) {
        command = commands.get('mention');
    }

    if (command) {
        args = msgContent.slice(2 + command.name.length).split(/ +/);
        args.shift();
    }

    if (!command) {
        // Remove prefix / mention from the message content
        // and splits the message by spaces into the args array
        if (msgContent.startsWith(`<@!${message.client.user.id}>` || `<@${message.client.user.id}>`)) {
        args = msgContent.slice(23).split(/ +/);
        } else if (msgContent.toLowerCase().startsWith(prefix)) {
        args = msgContent.slice(prefix.length).split(/ +/);
        }

        if (args) {
        // Uses the first arg as command name and removes it from the args array
        const commandName = args.shift().toLowerCase();
        
        if(commandName == 'mention')
            return { command, args };

        command = commands.get(commandName)
            || commands.find((cmd : Command) => cmd.aliases && cmd.aliases.includes(commandName));
        }
    }

    return { command, args };
};

export async function runCommand(ctx) {
    const command = commands.get(ctx.commandName.toLowerCase())
        || commands.find((cmd : Command) => cmd.aliases && cmd.aliases.includes(ctx.commandName.toLowerCase()));
    try {
        await command.run(ctx);
        Logger.command(ctx);
        return null;
    } catch (err) {
        Logger.error(`Error while executing the command ${ctx.commandName}`, err);
        return err;
    }
};





export function getCommand(commandName  : string) {
    return commands.get(commandName.toLowerCase())
        || commands.find((cmd : Command) => cmd.aliases && cmd.aliases.includes(commandName.toLowerCase()));
};

export function getCommandsByCategory(category  : string) {
    return commands.filter((cmd : Command) => cmd.category.toLowerCase() === category.toLowerCase());
};

export function getAllCommands() {
    return commands;
};


// Function used to recursively find a file
function traverse(dir, filename) {
    for (const dirent of fs.readdirSync(dir, { withFileTypes: true })) {
       if (dirent.isDirectory()) {
          const result = traverse(path.join(dir, dirent.name), filename);
          if (result) {
             return result;
          }
       } else if (dirent.name === `${filename}.js`) {
          return dir;
       }
    }
    return null;
}

export function reloadCommand(commandName : string) {
    // Find the command in the commands collection
    const command = this.getCommand(commandName);

    if (!command) {
        return `There is no command with name or alias \`${commandName}\`.`;
    }

    // Finds the path of the command
    const dir = traverse(CommandsDirPath, command.name);
    if (!dir) {
        return 'File not found';
    }

    const commandPath = path.join(dir,command.name);

    // Un-caches the command
    delete require.cache[require.resolve(commandPath)];

    // Re-caches the command
    try {
        const newCommand : Command = require(commandPath).default;
        newCommand.category = dir.substring(CommandsDirPath.length+1,dir.length);
        commands.set(newCommand.name.toLowerCase(), newCommand);
        return `Command \`${command.name}\` successfully reloaded!`;
    } catch (err) {
        return `There was an error while reloading a command \`${command.name}\`:\n\`${err}\``;
    }
};