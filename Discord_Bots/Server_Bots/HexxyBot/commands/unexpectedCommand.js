module.exports = {
    name: 'unexpectedCommand',
    description: "(internal command) this command handels the undefined/unexpected commands",
    execute(message,command,args,lowercaseArgs){
        message.channel.send('this is not a command dummy!');
    }
}