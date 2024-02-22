module.exports = {
    name: 'ping',
    description: "this is a ping command!",
    execute(message,command,args,lowercaseArgs){
        message.channel.send('pong!');
        ping ++;
    }
}