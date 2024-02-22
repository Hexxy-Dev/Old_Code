const http = require("http");
const fs = require('fs');
var path = require('path');

var qs = require('querystring');


const host = 'localhost';
const port = ; // REDACTED

const localtunnel = require('localtunnel');

const OSmode = 'L'; //W for windows L for linux

//function RestartTunnel(){

    (async () => {
    const tunnel = await localtunnel({ port: port, subdomain: `` }); // REDACTED

        http.createServer(function (request, response) {
            request.url = './MudaeDB' + request.url;
            console.log('request ', request.url);

            var filePath = request.url;
            if (filePath == './MudaeDB/') {
                filePath = './MudaeDB/index.html';
            }

            var extname = String(path.extname(filePath)).toLowerCase();
            var mimeTypes = {
                '.html': 'text/html',
                '.js': 'text/javascript',
                '.css': 'text/css',
                '.json': 'application/json',
                '.png': 'image/png',
                '.jpg': 'image/jpg',
                '.gif': 'image/gif',
                '.svg': 'image/svg+xml',
                '.wav': 'audio/wav',
                '.mp4': 'video/mp4',
                '.woff': 'application/font-woff',
                '.ttf': 'application/font-ttf',
                '.eot': 'application/vnd.ms-fontobject',
                '.otf': 'application/font-otf',
                '.wasm': 'application/wasm'
            };

            var contentType = mimeTypes[extname] || 'application/octet-stream';

            fs.readFile(filePath, function(error, content) {
                if (error) {
                    if(error.code == 'ENOENT') {
                        fs.readFile('./404.html', function(error, content) {
                            response.writeHead(404, { 'Content-Type': 'text/html' });
                            response.end(content, 'utf-8');
                        });
                    }
                    else {
                        response.writeHead(500);
                        response.end('Sorry, check with the site admin for error: '+error.code+' ..\n');
                    }
                }
                else {
                    response.writeHead(200, { 'Content-Type': contentType });
                    response.end(content, 'utf-8');
                }
            });

            if (request.method == 'POST') {
                var body = '';
                request.on('data', function (data) {
                    body += data;
                    // 1e6 === 1 * Math.pow(10, 6) === 1 * 1000000 ~~~ 1MB
                    if (body.length > 1e6) {
                        // FLOOD ATTACK OR FAULTY CLIENT, NUKE REQUEST
                        request.connection.destroy();
                    }

                });
                request.on('end', function () {
                    var post = qs.parse(body);
                    // use POST
                    console.log(post);
                    console.log(post.password);
                    console.log(post.action);
                    if(post.password == ''){ // REDACTED
                        switch(post.action){
                            case 'StopServer' : StopServer(); break;
                            case 'RunDBBot' : RunDBBot(); break;
                            case 'StopDBBot' : StopDBBot(); break;
                            case 'RunUtilityBot' : RunUtilityBot(); break;
                            case 'StopUtilityBot' : StopUtilityBot(); break;
                            case 'HTMLGen' : RunHTMLGenerator(); break;
                        }
                    }
                });
            }
        }).listen(port, host, () => {
            console.log(`Server is running on http://${host}:${port}`);
        });

        console.log('Url: ' + tunnel.url);

        /*
        tunnel.on('error', () => {
            console.log('tunnel error!');
            RestartTunnel();
        });
        */

        tunnel.on('close', () => {
            console.log('closed tunnel!');
        });

        async function StopServer(){
            console.log('Goodbye');
            tunnel.close();
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
            setTimeout(async () => { }, 3000);
            process.exit();
        }
        
    })();

//}

var child_process = require('child_process');
DBbot = undefined;

function RunDBBot(){
    console.log('DBbot started!');
    DBbot = child_process.exec('npm run DBbot',{detached: true});
    DBbot.stdout.on('data',( data ) =>{
        // This will render 'live':
        process.stdout.write( 'DBbotLog: ' + data );
    });
    DBbot.stderr.on('data',( data ) =>{
        // This will render 'live' too:
        process.stdout.write( 'DBbotErr: ' + data );
    });
}
async function StopDBBot(){
    if(DBbot != undefined){
        if(OSmode == 'W'){
            child_process.spawn("taskkill", ["/pid", DBbot.pid, '/f', '/t']);
        }else if(OSmode == 'L'){
            child_process.spawn("kill", [DBbot.pid]);
        }

        console.log('DBbot killed!');
        DBbot = undefined;
    }
}

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

Utilitybot = undefined;

function RunUtilityBot(){
    console.log('Utilitybot started!');
    Utilitybot = child_process.exec('npm run Utilitybot',{detached: true});
    Utilitybot.stdout.on('data',( data ) =>{
        // This will render 'live':
        process.stdout.write( 'UtilitybotLog: ' + data );
    });
    Utilitybot.stderr.on('data',( data ) =>{
        // This will render 'live' too:
        process.stdout.write( 'UtilitybotErr: ' + data );
    });
}
function StopUtilityBot(){
    if(Utilitybot != undefined){
        if(OSmode == 'W'){
            child_process.spawn("taskkill", ["/pid", Utilitybot.pid, '/f', '/t']);
        }else if(OSmode == 'L'){
            child_process.spawn("kill", [Utilitybot.pid]);
        }

        console.log('Utilitybot killed!');
        Utilitybot = undefined;
    }
}

//Start function
StartSequence();
async function StartSequence(){
    RunDBBot();
    RunUtilityBot();
}


setInterval(async function PeriodicHTMLGenerator(){
    RunHTMLGenerator();
}, 1800000);