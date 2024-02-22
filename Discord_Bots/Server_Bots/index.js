
var child_process = require('child_process');

const OSmode = 'L'; //W for windows L for linux


async function StopApp(){
    console.log('Goodbye');
    if(DBbot != undefined){
        if(OSmode == 'W'){
            child_process.spawn("taskkill", ["/pid", DBbot.pid, '/f', '/t']);
        }else if(OSmode == 'L'){
            child_process.spawn("kill", [DBbot.pid]);
        }

        console.log('DBbot killed!');
        DBbot = undefined;
    }
    if(Utilitybot != undefined){
        if(OSmode == 'W'){
            child_process.spawn("taskkill", ["/pid", Utilitybot.pid, '/f', '/t']);
        }else if(OSmode == 'L'){
            child_process.spawn("kill", [Utilitybot.pid]);
        }

        console.log('Utilitybot killed!');
        Utilitybot = undefined;
    }
    if(HTMLserver != undefined){//where the killin'???
        console.log('HTMLserver killed!');
        HTMLserver = undefined;
    }
    setTimeout(async () => { }, 3000);
    process.exit();
}


DBbot = undefined;

function RunDBBot(){
    console.log('DBbot starting!');
    DBbot = child_process.exec('npm run DBbot',{detached: true});
    DBbot.stdout.on('data',( data ) =>{
        // This will render 'live':
        process.stdout.write( 'DBbotLog: ' + data );
    });
    DBbot.stderr.on('data',( data ) =>{
        // This will render 'live' too:
        process.stdout.write( 'DBbotErr: ' + data );
    });
    DBbot.on('exit',() =>{
        console.log('DBbot is down!');
        DBbot = undefined;
    });
}

Utilitybot = undefined;

function RunUtilityBot(){
    console.log('Utilitybot starting!');
    Utilitybot = child_process.exec('npm run Utilitybot',{detached: true});
    Utilitybot.stdout.on('data',( data ) =>{
        // This will render 'live':
        process.stdout.write( 'UtilitybotLog: ' + data );
    });
    Utilitybot.stderr.on('data',( data ) =>{
        // This will render 'live' too:
        process.stdout.write( 'UtilitybotErr: ' + data );
    });
    Utilitybot.on('exit',() =>{
        console.log('Utilitybot is down!');
        Utilitybot = undefined;
    });
}

HTMLserver = undefined;

function RunHTMLserver(){
    console.log('starting HTMLserver!');
    HTMLserver = child_process.exec('npm run HTMLserver',{detached: true});
    HTMLserver.stdout.on('data',( data ) =>{
        // This will render 'live':
        process.stdout.write( 'HTMLserverLog: ' + data );
        if(data.includes('STOPTHEGODDAMNAPP')){
            StopApp();
        }
    });
    HTMLserver.stderr.on('data',( data ) =>{
        // This will render 'live' too:
        process.stdout.write( 'HTMLserverErr: ' + data );
    });
    HTMLserver.on('exit',() =>{
        console.log('Server is down!');
        HTMLserver = undefined;
        setTimeout(function(){
            console.log('Attempting to restart server');
            RunHTMLserver();
        },20000);
    });
}

//Start function
StartSequence();
async function StartSequence(){
    RunHTMLserver();
    RunDBBot();
    RunUtilityBot();
}



pingAddress = '8.8.8.8';

logPings = false;

setInterval(function(){
    if(OSmode == 'W'){
        pingProcess = child_process.spawn("ping", [pingAddress]);
    }else if(OSmode == 'L'){
        pingProcess = child_process.spawn("ping", ['-c','4',pingAddress]);
    }
    if(logPings){
        pingProcess.stdout.on('data',( data ) =>{
            // This will render 'live':
            process.stdout.write( 'PingLog: ' + data );
        });
        pingProcess.stderr.on('data',( data ) =>{
            // This will render 'live' too:
            process.stdout.write( 'PingErr: ' + data );
        });
    }
},30000);