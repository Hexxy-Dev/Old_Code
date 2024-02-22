module.exports = {
    name: 'changeChannelHere',
    description: "this command point witch channel the change channel command targets",
    execute(message,command,args,lowercaseArgs){
        if(changingChannel === true && command === commandsDictionary.changeChannelHere){
            Channel = message.channel.id;
            changingChannel = false;
            message.channel.send('this is my new channel');
        }
    }
}