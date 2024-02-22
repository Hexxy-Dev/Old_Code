//bot invite link  // REDACTED
// bot made by Bosuhexxyt

loginToken = ''; // REDACTED

console.log('noom!');

Discord = require('discord.js');
client = new Discord.Client();
client.login(loginToken);
client.on('debug', console.log);

const fs = require('fs');

client.commands = new Discord.Collection();

var commandsFound = 0;

const commandFiles = fs.readdirSync('../HexxyWaifuRoulette/commands/').filter(file => file.endsWith('.js'));
for(const file of commandFiles){
    const command = require(`./commands/${file}`);
    client.commands.set(command.name, command);
    commandsFound++;
}

client.on('ready', botReady);

isConected = true;

function botReady(){
    console.log('found ' + commandsFound + " commands");
    console.log('Bot is ready');
    isConected = true;
}

client.on('Disconnect', Disconnected);

function Disconnected(){
    isConected = false;
    reconnecting = setInterval(function(){ AutoReconnect(); }, 10000);
}

function AutoReconnect(){
    if(isConected){
        clearInterval(reconnecting);
        return;
    }
    console.log('Attempting to reconnect');
    client.login(loginToken);
}

presence = 1;

setInterval(function(){
    if(presence){
        presence = 0;
        client.user.setPresence({ activity: {name: "To $help",type: "LISTENING"}, status: 'idle' })
            .then(console.log)
            .catch(console.error);
    }else{
        presence = 1;
        client.user.setPresence({ activity: {name: "anime",type: "WATCHING"}, status: 'online' })
            .then(console.log)
            .catch(console.error);
    }
},300000);



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
                if(command == commandsDictionary.UpTime){
                    args[707] = Math.floor(process.uptime());
                }
                client.commands.get(key).execute(message,command,args,lowercaseArgs);
                ok = true;
            }
        });
    }
    if(!ok){
        client.commands.get('unexpectedCommand').execute(message,command,args,lowercaseArgs);
    }
}


//config

Prefix = '$';
singleChannel = false;

commandsDictionary = {
    helpCommand : ['help','h'],
    changePrefix : ['prefix'],
    changeChannel : ['changechannel'],
    changeChannelHere : ['here'],
    singleChannelToggle : ['singlechannel'],
    UpTime : ['uptime'],

    WaifuRoulette : ['waifu','w'],
    showAvailableImages : ['im']
}

//end of config


//global variables
changingChannel = false;
Channel = ''; // REDACTED
CurrencySymbol = 'munny';


unclaimedStatus = {
    "Name":"Unclaimed",
    "Color":"#ffff00"
}

claimedStatus = {
    "Name":"Claimed",
    "Color":"#d834eb"
}

wishedColor = "#34e5eb";

claimTime = 10000;

imTime = 10000;

claimEmoji = "💙";
leftEmoji = "👈";
rightEmoji = "👉";



/*
partials:

new Discord.Client({ partials: Object.values(Discord.Constants.PartialTypes) });

client.on('messageReactionAdd', async (reaction, user) => {
  // If the message is partial, the only accessible property is its id
  if (reaction.message.partial) await reaction.message.fetch();
  // The message is now fully available
  if(user.bot) return;

  client.commands.get('claimCharacter').execute(reaction,user);
});*/