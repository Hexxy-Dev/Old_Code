//bot invite link  // REDACTED
// bot made by Bosuhexxyt

loginToken = ''; // REDACTED

console.log('noom!');

Discord = require('discord.js');
client = new Discord.Client({ totalShards: 'auto' });
client.login(loginToken);
client.on('debug', console.log);

const fs = require('fs');


client.on('ready', botReady);

function botReady(){
    console.log('Bot is ready');
}

presence = 0;

setInterval(function(){
    if(presence){
        presence = 0;
        client.user.setPresence({ activity: { name: 'weeb music', type: 'LISTENING' }, status: 'Online' })
            //.then(console.log)
            .catch(console.error);
    }else{
        presence = 1;
        client.user.setPresence({ activity: { name: 'anime', type: 'WATCHING' }, status: 'idle' })
            //.then(console.log)
            .catch(console.error);
    }
},240000);


client.on('messageReactionAdd', (reaction, user) => {
    Reaction(reaction);
});

client.on('messageReactionRemove', (reaction, user) => {
    Reaction(reaction);
});

async function Reaction(reaction){
	if (reaction.partial) {
		try {
			await reaction.fetch();
		} catch (error) {
			console.error('Something went wrong when fetching the message: ', error);
			return;
		}
    }

    if(reaction.message.embeds[0]){
        if(reaction.message.embeds[0].footer){
            if(reaction.message.embeds[0].footer.text.split(' ')[1] != 2){
                if(reaction.message.embeds[0].footer.text.split(' ')[6] > 30){
                    embedFooterData = reaction.message.embeds[0].footer.text.split(' ');
                    order = embedFooterData[4];
                    author = embedFooterData[2];
                    author = author.split(' ');
                    author = author[0];
                    totalNumberOfCharacters = embedFooterData[6];
            
                    switch(author){
                        case'Bosuhexxyt': accountOrder = 0; break;
                        case'': accountOrder = 1; break; // REDACTED
                        case'': accountOrder = 2; break; // REDACTED
                        case'': accountOrder = 3; break; // REDACTED
                        case'': accountOrder = 4; break; // REDACTED
                        default : console.log('New user!!!!'); return;
                    }

                    logMessage(reaction.message,accountOrder,author,order,totalNumberOfCharacters);
                }
            }
        }
    }
}

jsonWriteInfoArray=[
[],[],[],[],[]
];

function logMessage(message,accountOrder,author,order,totalNumberOfCharacters){
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
        notes = '';
    }

    jsonWriteInfo =`{"Order":${order},"Name":"${characterName}","Series":"${series}","Kakera":${kakera},"ClaimRank":${claimRank},"LikeRank":${likeRank},"Notes":"${notes}","ImageLink":"${imageLink}"}`;

    jsonWriteInfoArray[accountOrder][order-1] = jsonWriteInfo;

    for(k=0;jsonWriteInfoArray[accountOrder].length-k > totalNumberOfCharacters; k++){
        //console.log(jsonWriteInfoArray[accountOrder].length-k);
        jsonWriteInfoArray[accountOrder].pop();
    }

    //console.log(jsonWriteInfoArray);
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

users =[ // REDACTED
];

Start();

function Start(){
    for(i=0;i<=4;i++){
        author = users[i];

        if(fs.existsSync(`./MudaeDB/lists/${author}/${author}.json`)){
            console.log(`Found ${author}`);
            existingJson = require(`./lists/${author}/${author}.json`);
        }else {console.log('JSON fetching error at initialisation'); continue;}
    
        existingJson = JSON.stringify(existingJson);
        existingJson = existingJson.slice(0,-1);
        existingJson = existingJson.escapeSpecialChars();
        existingJson = existingJson.substring(1);
        
        existingJson = existingJson.replace(/},/g,'}},');
        existingJson = existingJson.split('},');
        
        jsonWriteInfoArray[i] = existingJson;
    }
}

setInterval(async function PeriodicJSONwrite(){

    for(i=0;i<=4;i++){
        author = users[i];

        if(!fs.existsSync(`./MudaeDB/lists/${author}/${author}.json`)){
            console.log('JSON error at write'); 
            continue;
        }

        cleanArray = jsonWriteInfoArray[i].filter(function () { return true; });

        data = cleanArray.join(',\n');

        await writeJson(author,data);
    }
    console.log(`Updated json!!`);

    setTimeout(async function (){
        RunHTMLGenerator();
    },10000);

}, 600000);

async function writeJson(author,jsonWriteInfo){
    if(fs.existsSync(`./MudaeDB/lists/${author}/${author}.json`)){
        fs.unlinkSync(`./MudaeDB/lists/${author}/${author}.json`);
    }

    fs.appendFile(`./MudaeDB/lists/${author}/${author}.json`,'[' + jsonWriteInfo + '\n]', function (err) {
        if (err) throw err;
    });
}


var child_process = require('child_process');

function RunHTMLGenerator(){
    console.log('html generated!');
    HTMLGenerator = child_process.exec('npm run HTMLGenerator',{detached: true});
    HTMLGenerator.stdout.on('data',( data ) =>{
        // This will render 'live':
        process.stdout.write( 'HTMLGeneratorLog: ' + data );
    });
    HTMLGenerator.stderr.on('data',( data ) =>{
        // This will render 'live' too:
        process.stdout.write( 'HTMLGeneratorErr: ' + data );
    });
}