module.exports = {
    name: 'pauseSong',
    description: "this command pauses the song",
    execute(message,command,args,lowercaseArgs){
        internalFlags[202]=202;
        client.commands.get('playSound').execute(message,internalFlags);
    }
}