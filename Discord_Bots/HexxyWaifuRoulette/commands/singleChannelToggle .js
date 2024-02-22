module.exports = {
    name: 'singleChannelToggle',
    description: "this command toggles single channel mode",
    execute(message,command,args,lowercaseArgs){
        if(singleChannel)
        {
            singleChannel = false;
            message.channel.send('bot is now operating on all channels');
        }
        else
        {
            Channel = message.channel.id;
            singleChannel = true;
            message.channel.send('bot is now operating only on this channel');
        }
    }
}