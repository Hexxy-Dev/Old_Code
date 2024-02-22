module.exports = {
    name: 'pongs',
    description: "this command says the number of times the ping command has been used",
    execute(message,command,args,lowercaseArgs){
        message.channel.send('total number of pings: ' + ping);
    }
}