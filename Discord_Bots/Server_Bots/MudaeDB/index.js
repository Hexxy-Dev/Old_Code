const http = require("http");
const fs = require('fs');
var path = require('path');

var qs = require('querystring');


const host = 'localhost';
const port = ; // REDACTED


const localtunnel = require('localtunnel');

(async () => {
const tunnel = await localtunnel({ port: port, subdomain: `` }); // REDACTED

    // the assigned public url for your tunnel
    // i.e. https://abcdefgjhij.localtunnel.me

    http.createServer(function (request, response) {
        console.log('request ', request.url);

        var filePath = '.' + request.url;
        if (filePath == './') {
            filePath = './index.html';
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
                        case 'RunBot' : RunBot(); break;
                        case 'StopBot' : StopBot(); break;
                        case 'HTMLGen' : RunHTMLGenerator(); break;
                    }
                }
            });
        }
    }).listen(port, host, () => {
        console.log(`Server is running on http://${host}:${port}`);
    });

    console.log('Url: ' + tunnel.url);

    tunnel.on('close', () => {
        console.log('closed tunnel!');
    });

    async function StopServer(){
        console.log('Goodbye');
        tunnel.close();
        if(bot != undefined){
            child_process.spawn("taskkill", ["/pid", bot.pid, '/f', '/t']);
            console.log('bot killed!');
            bot = undefined;
        }
        setTimeout(async () => { }, 3000);
        process.exit();
    }
    
})();

var child_process = require('child_process');
bot = undefined;

function RunBot(){
    console.log('bot started!');
    bot = child_process.exec('npm run bot',{detached: true});
}
async function StopBot(){
    if(bot != undefined){
        child_process.spawn("taskkill", ["/pid", bot.pid, '/f', '/t']);
        console.log('bot killed!');
        bot = undefined;
    }
}

function RunHTMLGenerator(){
    console.log('html generated!');
    child_process.exec('npm run HTMLGenerator',{stdio:[0,1,2]});
}


//Start function
RunBot();

setInterval(async function PeriodicHTMLGenerator(){
    RunHTMLGenerator();
}, 1800000);