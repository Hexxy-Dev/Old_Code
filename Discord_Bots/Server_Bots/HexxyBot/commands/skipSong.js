module.exports = {
    name: 'skipSong',
    description: "this command adds a song to the queue",
    execute(message,command,args,lowercaseArgs){
        if(leftInQueue>0){
            message.channel.send('skipped!');
            client.commands.get('playSound').execute(message,internalFlags,queue);
        }
        else{
            message.channel.send('skipped!');
            message.channel.send('no more videos left in the queue');
            client.commands.get('playSound').execute(message,internalFlags,queue);
        }
    }
}