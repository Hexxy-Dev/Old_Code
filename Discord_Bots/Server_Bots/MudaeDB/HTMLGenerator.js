/*
ability to sort harem from the web interface
ability to generate sort command for mudae
add options for how many characters to show on screen at a time
ability to generate divorce command


search a series in multiple jsons
*/

const SortTypes = [
    'Order',
    'Name',
    'Kakera',
    'ClaimRank',
    'LikeRank',
    'Series'
];

const fs = require('fs');

Start()

async function Start(){
    var UserList = [ // REDACTED
    ];
    
    globalPath = './lists/Global/Global';
    separator = '';

    if(fs.existsSync(`${globalPath}.json`)){
        fs.unlinkSync(`${globalPath}.json`);
    }

    await writeJsonStart(globalPath,UserList,separator);
}



async function GenerateHTML(UserList){
    username = UserList[0];
    userPath = './lists/' + username + '/' + username;
    console.log(userPath);
    if(fs.existsSync(userPath+'.json')){
        for(j=0;j<=5;j++){
            var User = require(userPath+'.json');
            console.log('found: ' + username);  
            User.sort(GetSortOrder(SortTypes[j]));
            await createHtml(User,username,userPath,SortTypes[j]);
        }
    }
    console.log('Created!');
    if(Object.keys(UserList).length>0){
        UserList.shift();
        GenerateHTML(UserList);
    }
    else{
        return true;
    }
}

async function createHtml(jsonInfo,author,path,SortType){
    if(fs.existsSync(path+`${SortType}`+'.html')){
        fs.unlinkSync(path+`${SortType}`+'.html');
    }
    const fsPromises = fs.promises;
    for(i=0;i<Object.keys(jsonInfo).length;i++){
        if(author == 'Global'){
            info = '\n\t<h1>Belongs to: ' + jsonInfo[i].BelongsTo + '</h1><br>\n\t' + '<h1>' + jsonInfo[i].Name + '</h1><br>\n\t<h2>' + jsonInfo[i].Series + '</h2><br>\n\t' + '<h3>Kakera: ' + jsonInfo[i].Kakera + '</h3><br>\n\t<h3>Claim Rank: ' + jsonInfo[i].ClaimRank + '</h3><br>\n\t<h3>Like Rank: ' + jsonInfo[i].LikeRank + '</h3><br>\n\t<h3>' + jsonInfo[i].Notes + '</h3><br><br>\n\t' + `<img src="` + jsonInfo[i].ImageLink + `">`;
        }
        else{
            info = '\n\t<h1>#' + jsonInfo[i].Order + '</h1><br>\n\t' + '<h1>' + jsonInfo[i].Name + '</h1><br>\n\t<h2>' + jsonInfo[i].Series + '</h2><br>\n\t' + '<h3>Kakera: ' + jsonInfo[i].Kakera + '</h3><br>\n\t<h3>Claim Rank: ' + jsonInfo[i].ClaimRank + '</h3><br>\n\t<h3>Like Rank: ' + jsonInfo[i].LikeRank + '</h3><br>\n\t<h3>' + jsonInfo[i].Notes + '</h3><br><br>\n\t' + `<img src="` + jsonInfo[i].ImageLink + `">`;
        }
        await fsPromises.appendFile(`lists/${author}/${author}${SortType}.html`,`\n<div class="CharacterInfo" id="${jsonInfo[i].Name}">` + info + '\n</div>\n');
    }
    return true;
}

function GetSortOrder(prop) {

    if(prop == 'Kakera'){
        return function(a, b) {
            if (a[prop] > b[prop]) {
                return -1;
            } else if (a[prop] < b[prop]) {
                return 1;
            }
            return 0;
        }
    }
    else{
        return function(a, b) {
            if (a[prop] > b[prop]) {
                return 1;
            } else if (a[prop] < b[prop]) {
                return -1;
            }
            return 0;
        }
    }
}



async function writeJsonStart(globalPath,UserList,separator){
    fs.appendFile(`${globalPath}.json`,'[', async function (err) {
        if (err) throw err;
        console.log(`Started json for Global`);
        createGlobalJSON(UserList,separator,globalPath);
    });
}

async function createGlobalJSON(userList,separator,globalPath){
    username = userList[0];
    userPath = './lists/' + username + '/' + username + '.json';
    if(fs.existsSync(userPath)){
        jsonUserInfo = require(userPath);

        for(k=0;k<Object.keys(jsonUserInfo).length;k++){
            jsonWriteInfo = separator + `{"BelongsTo":"${username}","Name":"${jsonUserInfo[k].Name}","Series":"${jsonUserInfo[k].Series}","Kakera":${jsonUserInfo[k].Kakera},"ClaimRank":${jsonUserInfo[k].ClaimRank},"LikeRank":${jsonUserInfo[k].LikeRank},"Notes":"${jsonUserInfo[k].Notes}","ImageLink":"${jsonUserInfo[k].ImageLink}"}`;
            fs.appendFile(`${globalPath}.json`,jsonWriteInfo, function (err) {
                if (err) throw err;
                //console.log(`Updated json for Global`);
            });
            if(!separator){
                separator = ',\n';
            }
        }
    }
    console.log('Created!');
    if(Object.keys(userList).length>0){
        userList.shift();
        createGlobalJSON(userList,separator,globalPath);
    }
    else{
        writeJsonEnd(globalPath);
    }
}

async function writeJsonEnd(globalPath){

    setTimeout(() => {
        fs.appendFile(`${globalPath}.json`,'\n]', function (err) {
            if (err) throw err;
            console.log(`Stopped json for Global`);
        });
    }, 500);

    setTimeout(async () => {
        var UserList = [ // REDACTED
        ];
        await GenerateHTML(UserList);
    
        console.log('All tasks completed!!')
    }, 1000);
}

