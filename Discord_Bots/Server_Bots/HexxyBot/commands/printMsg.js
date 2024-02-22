module.exports = {
    name: 'printMsg',
    description: "this command sends it's arguments as a message",
    execute(message,command,args,lowercaseArgs){
        message.channel.send(args);
    }
}