const whiteListedPrefixes = [
    '!', '$', '%', '^', '&', '*', '-', '_', '=', '+', '`', '~', ',', '<', '.', '>', '?', '|', ';'
]
module.exports = {
    name: 'changePrefix',
    description: "this command changes the bot's prefix",
    execute(message,command,args,lowercaseArgs){
        if(!whiteListedPrefixes.includes(lowercaseArgs[0])){
            message.channel.send('That is not a valid prefix');
            return;
        }
        Prefix = lowercaseArgs[0].toString();
        message.channel.send('My prefix is now: ' + Prefix);
    }
}