module.exports = {
    name: 'UpTime',
    description: "this command displays the bot's uptime",
    execute(message,command,args,lowercaseArgs){

        //difference between both dates in ms
        var difference = (new Date() - start_time);

        var msSecond = 1000;
        var msMinute = 60 * msSecond;
        var msHour = 60 * msMinute;
        var msDay = 24 * msHour;

        var days = Math.floor(difference / msDay);
        difference -= days * msDay;

        var hours = Math.floor(difference / msHour);
        difference -= hours * msHour;

        var minutes = Math.floor(difference / msMinute);
        difference -= minutes * msMinute;

        var seconds = Math.floor(difference / msSecond);
        

        message.channel.send('up time is: ' + days + ' days ' + hours + ' hours ' + minutes + ' minutes and '+ seconds%60 + ' seconds');
    }
}