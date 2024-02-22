module.exports = {
    name: 'UpTime',
    description: "this command displays the bot's uptime",
    execute(message,command,args,lowercaseArgs){
        var seconds = args[707];
        args[707] = undefined;
        var minutes = Math.floor((seconds/60)%60);
        var hours = Math.floor((seconds/3600)%24);
        var days = Math.floor(seconds/86400);
        message.channel.send('up time is: ' + days + ' days ' + hours + ' hours ' + minutes + ' minutes and '+ seconds%60 + ' seconds');
    }
}