

const localPath = '../Characters/Waifus/';

const characterList = require(`../Characters/Waifus.json`);

var mk;

const numbers = [0,1,2,3,4,5,6,7,8,9];

module.exports = {
    name: 'showAvailableImages',
    description: "this command displays a character's available images",
    execute(message,command,args,lowercaseArgs){
        
        var k;

        var nameToSearch = lowercaseArgs[0];
        var words = nameToSearch.split(" ");

        for (let i = 0; i < words.length; i++) {
            var j;
            for (j = 0; j < words.length; j++) {
                if(!numbers.includes(words[i][j])) break;
            }
            words[i] = words[i][j].toUpperCase() + words[i].substr(1);
        }

        nameToSearch = words.join(' ');


        //let character = characterList.find(characterList.Name === args[0]);

        //character = getCharacterByName(args[0]);

        console.log(findNestedObj(characterList,'Name',nameToSearch));

        characterToSearch = findNestedObj(characterList,'Name',nameToSearch);

        var WaifuEmbed = new Discord.MessageEmbed()

        PathSeries = characterToSearch.Series;
        PathName = characterToSearch.Name;

        Path = localPath + PathSeries + '/' + PathName;

        character = require(Path)

        characterName = character.Name;

        descriptionData = character.Series + '\n' + character.Currency + ' ' + CurrencySymbol + '\n';

        k = character.PreferredUrl;

        imageUrl = character.Url[k];


        WaifuEmbed.setColor('#8f8f8f');//needs to be auto changed
        WaifuEmbed.setTitle(characterName);
        WaifuEmbed.setDescription(descriptionData);
        WaifuEmbed.setImage(imageUrl)
        WaifuEmbed.setFooter(k + ' / ' + Object.keys(character.Url).length);

        message.channel.send(WaifuEmbed)
        .then(function (message) {

            message.react(leftEmoji);
            message.react(rightEmoji);

            mk=k;

            awaitMessageReactions(message);
            
        })
        .catch(function() {
            console.log("Error at adding reactions")
        });

    }
}

async function awaitMessageReactions(message){
    const filter = (reaction, user) => /*(reaction.emoji.name === leftEmoji || reaction.emoji.name === rightEmoji) &&*/ !user.bot;
    message.awaitReactions(filter, { max: 1, time: imTime, errors: ['time'] })
    .then(collected => {

        const reaction = collected.first();
        //console.log(reaction.users.cache.last().username);
        //console.log(reaction.message.embeds[0]);

        messageCharacterName = reaction.message.embeds[0].title;

        messageCharacterSeries = reaction.message.embeds[0].description.split('\n')[0];

        messagePath = localPath + messageCharacterSeries + '/' + messageCharacterName;

        messageCharacter = require(messagePath);

        messageDescriptionData = messageCharacter.Series + '\n' + messageCharacter.Currency + ' ' + CurrencySymbol + '\n';

        if(reaction.emoji.name === leftEmoji) mk--;
        else mk++;

        if(mk > Object.keys(messageCharacter.Url).length - 1) mk=0;

        messageImageUrl = messageCharacter.Url[mk];

        var messageWaifuEmbed = new Discord.MessageEmbed()

        messageuser = reaction.users.cache.last().username;

        messageWaifuEmbed.setColor('#8f8f8f');
        messageWaifuEmbed.setTitle(messageCharacterName);
        messageWaifuEmbed.setDescription(messageDescriptionData);
        messageWaifuEmbed.setImage(messageImageUrl)
        messageWaifuEmbed.setFooter((mk+1) + ' / ' + Object.keys(messageCharacter.Url).length);

        reaction.message.edit(messageWaifuEmbed);

        awaitMessageReactions(message);

    })
    .catch(collected => {
        console.log('Shit happened');
    });
}


function findNestedObj(entireObj, keyToFind, valToFind) {
    let foundObj;
    JSON.stringify(entireObj, (_, nestedValue) => {
      if (nestedValue && nestedValue[keyToFind] === valToFind) {
        foundObj = nestedValue;
      }
      return nestedValue;
    });
    return foundObj;
  };