module.exports = {
    name: 'resumeSong',
    description: "this command resumes the song",
    execute(message,command,args,lowercaseArgs){
        internalFlags[303]=303;
        client.commands.get('playSound').execute(message,internalFlags);
    }
}