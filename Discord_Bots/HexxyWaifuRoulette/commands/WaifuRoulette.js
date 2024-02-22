

const localPath = '../Characters/Waifus/';

const characterList = require(`../Characters/Waifus.json`);

module.exports = {
    name: 'WaifuRoulette',
    description: "this command rolls a waifu",
    execute(message,command,args,lowercaseArgs){
        var WaifuEmbed = new Discord.MessageEmbed()


        //code to determine the rarity of the character

        //code to pick a character in that rarity

        //code to load the character data

        statusColor = unclaimedStatus.Color;
        status = unclaimedStatus.Name;

        rarity = 'UltraRare';

        k = Math.round(Math.random());


        PathSeries = characterList[status][rarity][k].Series;
        PathName = characterList[status][rarity][k].Name;

        Path = localPath + PathSeries + '/' + PathName;

        character = require(Path)

        console.log(Path);



        characterName = character.Name;

        descriptionData = character.Series + '\n' + character.Currency + ' ' + CurrencySymbol + '\n';

        imageUrl = character.Url[character.PreferredUrl];


        WaifuEmbed.setColor(statusColor);
        WaifuEmbed.setTitle(characterName);
        WaifuEmbed.setDescription(descriptionData);
        WaifuEmbed.setImage(imageUrl)

        message.channel.send(WaifuEmbed)
        .then(function (message) {

            message.react(claimEmoji);

            const filter = (reaction, user) => reaction.emoji.name === claimEmoji && !user.bot;
            message.awaitReactions(filter, { max: 1, time: claimTime, errors: ['time'] })
            .then(collected => {

                const reaction = collected.first();
                //console.log(reaction.users.cache.last().username);
                //console.log(reaction.message.embeds[0]);

                messageCharacterName = reaction.message.embeds[0].title;

                messageCharacterSeries = reaction.message.embeds[0].description.split('\n')[0];

                messagePath = localPath + messageCharacterSeries + '/' + messageCharacterName;

                messageCharacter = require(messagePath);


                messageDescriptionData = messageCharacter.Series + '\n' + messageCharacter.Currency + ' ' + CurrencySymbol + '\n';

                messageImageUrl = messageCharacter.Url[messageCharacter.PreferredUrl];

                var messageWaifuEmbed = new Discord.MessageEmbed()

                messageuser = reaction.users.cache.last().username;

                messageWaifuEmbed.setColor(claimedStatus.Color);
                messageWaifuEmbed.setTitle(messageCharacterName);
                messageWaifuEmbed.setDescription(messageDescriptionData);
                messageWaifuEmbed.setImage(messageImageUrl)
                messageWaifuEmbed.setFooter('Belongs to: ' + messageuser);

                reaction.message.edit(messageWaifuEmbed);

                reaction.message.channel.send(claimEmoji + ' ' + messageuser + ' and ' + messageCharacterName + ` are now married! ${claimEmoji}`);

                //function to actually add the character to the user's inventory











                
            })
            .catch(collected => {
            });
            
        })
        .catch(function() {
            console.log("Error at adding reactions")
        });

    }
}