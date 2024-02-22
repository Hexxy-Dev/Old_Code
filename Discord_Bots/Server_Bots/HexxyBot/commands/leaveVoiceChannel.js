module.exports = {
    name: 'leaveVoiceChannel',
    description: "this command makes the bot leave your voice channel and clear the queue",
    execute(message,command,args,lowercaseArgs){
        var voiceChannel = message.member.voice.channel;
        voiceChannel.leave();
        queue = [
        ];
        leftInQueue = 0;
        message.channel.send('left voice channel and cleared the queue');
    }
}