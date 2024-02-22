const replies = [
    'Noom',
    'NOOM',
    'Oomnoomnom',
]

module.exports = {
    name: 'noom',
    description: "this command randomly nooms u",
    execute(message,command,args,lowercaseArgs){
        const r = Math.floor(Math.random() * replies.length);
        message.channel.send(replies[r]);
    }
}