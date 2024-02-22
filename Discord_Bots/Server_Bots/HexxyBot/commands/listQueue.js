const YouTube = require("discord-youtube-api");

const youtube = new YouTube(youtubeApiKey);

var inlineMessage = false;

module.exports = {
    name: 'listQueue',
    description: "this command lists the youtube videos in the queue",
    execute(message,command,args,lowercaseArgs){
        if(leftInQueue > 0){
            printQueueList(message);
        }else{
            message.channel.send('no videos left in the queue');
        }
    }
}

async function printQueueList(message){
    const queueEmbed = new Discord.MessageEmbed()

    queueEmbed
    .setColor('#0099ff')
    .setTitle('Queue song list')
    .setAuthor('HexxyBot', '') // REDACTED
    for(i=0;i<leftInQueue;i++){
        info = await youtube.getVideo(queue[i]);
        title = info.title;
        length = info.length;
        queueEmbed.addField((i+1) + ') ' + title + ' | ' + length, queue[i], inlineMessage);
    }
    queueEmbed
    .setTimestamp()
    .setFooter('HexxyBot', ''); // REDACTED

    message.channel.send(queueEmbed);
}