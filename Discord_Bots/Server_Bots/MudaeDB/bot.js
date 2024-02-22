
loginToken = ''; // REDACTED

console.log('noom!');

Discord = require('discord.js');
client = new Discord.Client();
client.login(loginToken);

const fs = require('fs');

client.commands = new Discord.Collection();

client.on('ready', botReady);

function botReady(){
    console.log('Bot is ready');
}

client.on('messageReactionAdd', (reaction, user) => {
    Reaction(reaction);
});

client.on('messageReactionRemove', (reaction, user) => {
    Reaction(reaction);
});

ok = 0;

async function Reaction(reaction){
	if (reaction.partial) {
		try {
			await reaction.fetch();
		} catch (error) {
			console.error('Something went wrong when fetching the message: ', error);
			return;
		}
    }
    if(Ready){
        if(!locked){
            ReactionMessage = reaction.message.id;
            locked = true;
        }
        if(ok == 2 && reaction.message.id == ReactionMessage){
            characterCount = reaction.message.embeds[0].footer.text.split(' ');
            characterCount = characterCount[6];

            logMessage(reaction.message,characterCount);
        }
        else{
            ok++;
        }
    }
}

client.on('message', gotMessage);

Ready = false;
locked = false;
order = 1;

function gotMessage(message){
    if(!message.author.bot){
        firstargs = message.content.split(' ');
        command = firstargs[0] + ' ' + firstargs[1];
        console.log(command);
        console.log(firstargs[2]);
        if(!Ready && command == 'DB start'){
            separator = '';
            order = 1;
            author = firstargs[2];
            dirPath = './lists/' + author;
            fs.mkdirSync(dirPath, { recursive: true })
            if(fs.existsSync(`lists/${author}/${author}.json`)){
                fs.unlinkSync(`lists/${author}/${author}.json`);
            }
            fs.appendFile(`lists/${author}/${author}.json`,'[', function (err) {
                if (err) throw err;
                console.log(`Started json for ${author}`);
            });
            Ready = true;
        }
        if(!Ready && command == 'DB resume'){
            author = firstargs[2];
            if(fs.existsSync(`lists/${author}/${author}.json`)){
            separator = ',';
            order = 1;
            dirPath = './lists/' + author;
            fs.mkdirSync(dirPath, { recursive: true })

            existingJson = require(dirPath + '/' + author + '.json');

            order = Object.keys(existingJson).length;

            existingJson = JSON.stringify(existingJson);
            existingJson = existingJson.slice(0,-1);
            existingJson = existingJson.escapeSpecialChars()
            
            fs.unlinkSync(`lists/${author}/${author}.json`);
            
            fs.appendFile(`lists/${author}/${author}.json`,existingJson, function (err) {
                if (err) throw err;
                console.log(`Started json for ${author}`);
            });

            Ready = true
            }
        }
        if(command == 'DB continue'){
            ok = 0;
            Ready = true;
            locked = false;
        }
        if(command == 'DB stop'){
            Ready = false;
            locked = false;
            fs.appendFile(`lists/${author}/${author}.json`,'\n]', function (err) {
                if (err) throw err;
                console.log(`Stopped json for ${author}`);
            });
            separator = '';
            ok = 0;
        }
    }
}

String.prototype.escapeSpecialChars = function() {
    return this.replace(/\\n/g, "\\n")
               .replace(/\\'/g, "\\'")
               .replace(/\\"/g, '\\"')
               .replace(/\\&/g, "\\&")
               .replace(/\\r/g, "\\r")
               .replace(/\\t/g, "\\t")
               .replace(/\\b/g, "\\b")
               .replace(/\\f/g, "\\f");
};

place = 0;

function logMessage(message,characterCount){
    place ++;
    details = message.embeds[0].description.split('\n');
    characterName = message.embeds[0].author.name;
    offset = 0;
    if(details[3].includes('Like Rank:')){
        offset = 1;
        seriesArray = details[0].split(' ');
    }
    else if(details[4].includes('Like Rank:')){
        offset = 2;
        seriesArray = details[0].split(' ');
        part2 = details[1].split(' ');
        part2.forEach(element => {
            seriesArray.push(element);
        });
    }
    else if(details[5].includes('Like Rank:')){
        offset = 3;
        seriesArray = details[0].split(' ');
        part2 = details[1].split(' ');
        part2.forEach(element => {
            seriesArray.push(element);
        });
        part3 = details[2].split(' ');
        part3.forEach(element => {
            seriesArray.push(element);
        });
    }
    seriesArray.pop();
    if(seriesArray[seriesArray.length - 1].includes('<:female:452463537508450304><:male:452470164529872899>')){
        seriesArray.pop();
    }
    series = seriesArray.join(' ');
    kakeraUnfiltered = details[offset].split('*');
    kakera = parseInt(kakeraUnfiltered[4]);
    claimRank = details[offset+1].split(' ');
    claimRank.shift();
    claimRank.shift();
    claimRank = claimRank[0].split('')
    claimRank.shift();
    claimRank = claimRank.join('');
    claimRank = parseInt(claimRank);
    likeRank = details[offset+2].split(' ');
    likeRank.shift();
    likeRank.shift();
    likeRank = likeRank[0].split('')
    likeRank.shift();
    likeRank = likeRank.join('');
    likeRank = parseInt(likeRank);
    notes = details[offset+3];
    imageLink = message.embeds[0].image.url;

    if(notes == undefined){
        notes = '404 Not found';
    }

    logEverything(order,characterName,series,kakera,claimRank,likeRank,notes,imageLink);

    jsonWriteInfo = separator + `{"Order":${order},"Name":"${characterName}","Series":"${series}","Kakera":${kakera},"ClaimRank":${claimRank},"LikeRank":${likeRank},"Notes":"${notes}","ImageLink":"${imageLink}"}`;

    writeJson(author,jsonWriteInfo);
    order++;
    if(order <= characterCount){
        fun();
    }
}

separator = '';

function writeJson(author,jsonWriteInfo){
    fs.appendFile(`lists/${author}/${author}.json`,jsonWriteInfo, function (err) {
        if (err) throw err;
        console.log(`Updated json for ${author}`);
    });
    if(!separator){
        separator = ',\n';
    }
}

var exec = require('child_process').execFile;

var fun =function(){
   exec('clk.exe',function(err, data) {
       console.log(err);
       console.log(data);
    });
}

function logEverything(order,characterName,series,kakera,claimRank,likeRank,notes,imageLink){
    console.log(order);
    console.log(characterName);
    console.log(series);
    console.log(kakera);
    console.log(claimRank);
    console.log(likeRank);
    console.log(notes);
    console.log(imageLink);
}