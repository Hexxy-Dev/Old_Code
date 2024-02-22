var inlineMessage = false;

module.exports = {
    name: 'helpCommand',
    description: "this command displays all available commands and their corresponding descriptions",
    execute(message,command,args,lowercaseArgs){
        const helpCommandsEmbed = new Discord.MessageEmbed()

        isGenerated = false;

        if(!isGenerated){
            helpCommandsEmbed
            .setColor('#0099ff')
            .setTitle('Command list')
            .setAuthor('HexxyBot', '') // REDACTED
            .setThumbnail('') // REDACTED
            for(var commandKey in commandsDictionary){
                helpCommandsEmbed.addField(Prefix + commandsDictionary[commandKey], client.commands.get(commandKey).description, inlineMessage);
            }
            helpCommandsEmbed
            .setTimestamp()
            .setFooter('HexxyBot', ''); // REDACTED
            isGenerated = true;
        }

        message.channel.send(helpCommandsEmbed);
    }
}