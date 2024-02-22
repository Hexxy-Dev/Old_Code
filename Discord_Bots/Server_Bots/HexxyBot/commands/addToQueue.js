const YouTube = require("discord-youtube-api");

const youtube = new YouTube(youtubeApiKey);

module.exports = {
    name: 'addToQueue',
    description: "this command adds a youtube video to the queue",
    execute(message,command,args,lowercaseArgs){

        if(args[0]=='testinG'){
            args[0] = (''); // REDACTED
        }
        
        if(!validURL(args[0])){
            searchYoutube(message,command,args);
            message.channel.send('not a url performing standard search...');
            return;
        }else{
            if(!matchYoutubeUrl(args[0])){
                message.channel.send('invalid youtube url');
                return;
            }
        }

        leftInQueue++;
        queue.push(args[0]);
        printTitle(message,args)

        if(!isPlaying){
            client.commands.get('playSound').execute(message,internalFlags,queue);
        }
    }
}

function validURL(str) {
    var pattern = new RegExp('^(https?:\\/\\/)?'+ // protocol
      '((([a-z\\d]([a-z\\d-]*[a-z\\d])*)\\.)+[a-z]{2,}|'+ // domain name
      '((\\d{1,3}\\.){3}\\d{1,3}))'+ // OR ip (v4) address
      '(\\:\\d+)?(\\/[-a-z\\d%_.~+]*)*'+ // port and path
      '(\\?[;&a-z\\d%_.~+=-]*)?'+ // query string
      '(\\#[-a-z\\d_]*)?$','i'); // fragment locator
    return !!pattern.test(str);
}

async function searchYoutube(message,command,args){
    var video = await youtube.searchVideos(args.toString().replace(/,/g,' '));
    args[0] = video.url;
    client.commands.get('addToQueue').execute(message,command,args);
}

function matchYoutubeUrl(url) {
    var p = /^(?:https?:\/\/)?(?:m\.|www\.)?(?:youtu\.be\/|youtube\.com\/(?:embed\/|v\/|watch\?v=|watch\?.+&v=))((\w|-){11})(?:\S+)?$/;
    if(url.match(p)){
        return true;
    }
    return false;
}

async function printTitle(message,args){
    info = await youtube.getVideo(args[0]);
    title = info.title;
    length = info.length;
    message.channel.send(title + ' | ' + length + ' | was added to the queue: place: ' + leftInQueue);
}
