module.exports = {
    name: 'changeChannel',
    description: "this command changes the channel in witch the bot is active",
    execute(message,command,args,lowercaseArgs){
        if(changingChannel === false){
            changingChannel = true;
            message.channel.send('waiting for $here command');
        }
    }
}