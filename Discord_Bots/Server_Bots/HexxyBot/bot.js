console.log('noom!');

const Discord = require('discord.js');
const client = new Discord.Client();
client.login(''); // REDACTED

client.on('ready', botReady);

function botReady(){
    console.log('Bot is ready');
}

client.on('message', gotMessage);

var Channel = ''; // REDACTED

var Prefix = '$';

var commandsDictionary = {
    changePrefix : Prefix + 'prefix',
    printMsg : Prefix + 'print',
    changeChannel : Prefix + 'changechannel',
    changeChannelHere : Prefix + 'here',
    totalPings : [
        Prefix + 'totalpings',
        Prefix + 'tp'
    ]
}

const replies = [
    'Noom',
    'NOOM',
    'Oomnoomnom'
]

var ping = 0;

var changingChannel = false;

function gotMessage(msg){
    if(!msg.content.startsWith(Prefix) || msg.author.bot) return;
    if(msg.channel.id === Channel || changingChannel === true){
        parsedMsg = parseMessage(msg.content);
        executeCommand(msg,parsedMsg[0], parsedMsg[1]);
    }
}

function parseMessage(Msg){
    Msg = Msg.toLowerCase();
    command = Msg.split(" ",1).toString();
    Msg = Msg.replace(command + ' ',"");
    Msg = Msg.replace(command,"");
    args = Msg.split(Prefix);
    return [command, args];
}

function executeCommand(msg,command,args){
    console.log(command);
    console.log(args);

    if(command === commandsDictionary.changePrefix){
        Prefix = args[0].toString();
        msg.channel.send('My prefix is now: ' + Prefix);
    }

    if(command === Prefix + 'noom'){
        const r = Math.floor(Math.random() * replies.length);
        msg.channel.send(replies[r]);
    }

    if(command === Prefix + 'ping'){
        msg.channel.send('pong!');
        ping++;
    }

    if(command === commandsDictionary.printMsg){
        msg.channel.send(args);
    }

    if(command === commandsDictionary.changeChannel && changingChannel === false){
        changingChannel = true;
        msg.channel.send('waiting for $here command');
    }
    else{
        if(command === commandsDictionary.changeChannelHere){
            Channel = msg.channel.id;
            changingChannel = false;
            msg.channel.send('this is my new channel');
        }
    }

    if(command === commandsDictionary.totalPings[0] || command == commandsDictionary.totalPings[1]){
        msg.channel.send('total number of pings: ' + ping);
    }
}
