const ytdl = require('ytdl-core');

module.exports = {
    name: 'playSound',
    description: "(internal command) this command plays sound from a url",
    execute(message, internalFlags, queue, voice){

        if(voice == undefined){
          var { voice } = message.member;
        }

        if(!voice.channel){
            message.channel.send('**you must be joined in a voice channel!**');
            return;
        }

        if(isPlaying){
            if(internalFlags[101]==101){
                dispatcher.setVolume(volume);
                internalFlags[101] = null;
                return;
            }

            if(internalFlags[303]==303){
                dispatcher.resume();
                message.channel.send('resuming...');
                internalFlags[303] = null;
                return;
            }
            if(internalFlags[202]==202){
                dispatcher.pause(true);
                message.channel.send('paused');
                internalFlags[202] = null;
                return;
            }
        }

        voice.channel.join().then((connection) => {
            dispatcher = connection.play('');

            if(leftInQueue > 0){
                dispatcher.destroy();
                dispatcher = connection.play(ytdl(queue[0],{filter: 'audioonly', quality: 'highestaudio', /*highWaterMark: 1<<1024*/ }),{ /*highWaterMark : 1,*/ volume : volume, bitrate : 96000 });
            }
            else{
                isPlaying = false;
                var voiceChannel = message.member.voice.channel;
                voiceChannel.leave();
            }

            dispatcher.on('start', () => {
                isPlaying = true;
                leftInQueue--;
                message.channel.send('playing: ' + queue[0] + ' at ' + volume*100 + '% volume | left in queue: ' + leftInQueue);
                queue.splice(0,1);
            });
            
            dispatcher.on('finish', () => {
                client.commands.get('playSound').execute(message,internalFlags,queue,voice);
            });

            dispatcher.on('error', console.error);
        })
    }
}