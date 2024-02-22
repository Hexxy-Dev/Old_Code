module.exports = {
    name: 'soundVolume',
    description: "this command sets the bot's volume",
    execute(message,command,args,lowercaseArgs){
        if(args[0]==null){
            message.channel.send('current volume is: ' + volume*100 + '%');
            return;
        } 
        if(args[0]>=0 && args[0]<=100){
            volume = args[0]/100;
            if(isPlaying){
                args[0]=null;
                internalFlags[101]=101;
                client.commands.get('playSound').execute(message,internalFlags);
            }
            message.channel.send('new volume is: ' + volume*100 + '%');
        } 
        else{
            message.channel.send('new volume value is not between 0 and 100');
        }
    }
}