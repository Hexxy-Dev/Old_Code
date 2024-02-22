const CMD = require('../core/command-handler/command-handler');

module.exports = {
    name: 'help',
    aliases: ['h'],
    description: 'List all commands',
    reqArgs: false,
    usage: '',
    exampleUsage: 'help',
    category: 'Misc',
    cooldown: 300,
 
    async run(ctx) {
        const commands = CMD.getAllCommands();
        commands.forEach((e) => {
            ctx.sendText(
                e.name + ' '
                + e.aliases.forEach((e2) => e2 + ' ')
                + e.description + ' '
                + e.usage + ' '
                + e.exampleUsage + ' '
                + e.category
            );
        })
    }
};
 