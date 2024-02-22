//bot invite link  // REDACTED
// bot made by Bosuhexxyt

loginToken = ''; // REDACTED

youtubeApiKey = ''; // REDACTED

//config

Prefix = '$';

commandsDictionary = {
    helpCommand : ['help','h'],
    changePrefix : ['prefix'],
    changeChannel : ['changechannel'],
    changeChannelHere : ['here'],
    singleChannelToggle : ['singlechannel'],

    printMsg : ['print'],
    UpTime : ['uptime'],

    ping : ['ping'],
    noom : ['noom'],
    pongs : ['pongs'],

    leaveVoiceChannel : ['leave'],
    soundVolume : ['volume'],
    addToQueue : ['play','p'],
    skipSong : ['skip'],
    pauseSong : ['pause'],
    resumeSong : ['resume'],
    listQueue : ['queue']
}


Channel = ''; // REDACTED
singleChannel = true;

//end of config

console.log('noom!');

Discord = require('discord.js');
client = new Discord.Client();
client.login(loginToken);
client.on('debug', console.log);

const fs = require('fs');

client.commands = new Discord.Collection();

var commandsFound = 0;

const commandFiles = fs.readdirSync('./HexxyBot/commands/').filter(file => file.endsWith('.js'));
for(const file of commandFiles){
    const command = require(`./commands/${file}`);
    client.commands.set(command.name, command);
    commandsFound++;
}

client.on('ready', botReady);


function botReady(){
    console.log('found ' + commandsFound + " commands");
    console.log('Bot is ready');
}

presence = 1;

setInterval(function(){
    if(presence){
        presence = 0;
        client.user.setPresence({ activity: { name: '$help', type: 'LISTENING' }, status: 'Online' })
            //.then(console.log)
            .catch(console.error);
    }else{
        presence = 1;
        client.user.setPresence({ activity: { name: 'anime', type: 'WATCHING' }, status: 'idle' })
            //.then(console.log)
            .catch(console.error);
    }
},240000);


client.on('message', gotMessage);

function gotMessage(message){
    if(!message.content.startsWith(Prefix) || message.author.bot) return;
    if(message.channel.id === Channel || changingChannel === true || !singleChannel){
        parsedMsg = messageParser(message.content);
        executeCommand(message,parsedMsg[0], parsedMsg[1]);
    }
}

function messageParser(Msg){
    command = Msg.split(" ",1).toString();
    command = command.toLowerCase();
    Msg = Msg.replace(command,"");
    command = command.replace(Prefix,"");
    args = Msg.split(Prefix);
    Msg = Msg.toLowerCase();
    lowercaseArgs = Msg.split(Prefix);
    for(var i = 0; i < args.length; i++){
        args[i] = args[i].replace(/^\s+|\s+$/g,"");
        args[i] = args[i].replace(/  +/g," ");
        lowercaseArgs[i] = lowercaseArgs[i].replace(/^\s+|\s+$/g,"");
        lowercaseArgs[i] = lowercaseArgs[i].replace(/  +/g," ");
    }
    args = args.filter(function(e){return e});
    lowercaseArgs = lowercaseArgs.filter(function(e){return e});
    return [command, args];
}

function executeCommand(message,command,args){
    console.log('author: ' + message.author.username);
    console.log('command: ' + command);
    console.log('args: ' + args);
    console.log('lowercaseArgs: ' + lowercaseArgs);
    console.log(process.uptime());
    console.log(message.channel.id);

    ok = false;
    for([key, val] of Object.entries(commandsDictionary)){
        val.forEach(value => {
            if(value === command){
                client.commands.get(key).execute(message,command,args,lowercaseArgs);
                ok = true;
            }
        });
    }
    if(!ok){
        client.commands.get('unexpectedCommand').execute(message,command,args,lowercaseArgs);
    }

    console.log('volume:' + volume);
}



//global variables

internalFlags = [
];
changingChannel = false;
ping = 0;
volume = 0.05;
isPlaying = false;
leftInQueue = 0;
queue = [
];

start_time = new Date();