#include <iostream>
#include <limits>
#include <cmath>

void clear() { puts("\033[H\033[J"); }

using namespace std;

//Settings

bool piece=1; //1 to start with O   0 to start with X
bool convert=1; //convert 1 to 11, 2 to 21, ....  9 to 33
bool PvP=1; //if set to 1 bot is disabled
string difficulty = "Random"; //"Random" "Impossible" bot always starts first
bool botStartFirst = 1;

///////////

int input,i,j,currentMove=0,lastMove;
string v[3][3];


void initializeBoard(){
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            v[i][j]="#";
}

bool gameOver(){
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            if(v[i][j]=="#") return false;
    cout<<"draw"<<endl;
    return true;
}

bool checkWin(){
    string win="n";

    j=0;
    for(i=0;i<3;i++){
        if(v[i][j]==v[i][j+1] && v[i][j]==v[i][j+2] && v[i][j]!="#")
            if(v[i][j]=="x") win="x";else win="o";
    }

    i=0;
    for(j=0;j<3;j++){
        if(v[i][j]==v[i+1][j] && v[i][j]==v[i+2][j] && v[i][j]!="#")
            if(v[i][j]=="x") win="x";else win="o";
    }

    if(v[0][0]==v[1][1] && v[0][0]==v[2][2] && v[0][0]!="#")
        if(v[0][0]=="x") win="x";else win="o";
    if(v[2][0]==v[1][1] && v[2][0]==v[0][2] && v[2][0]!="#")
        if(v[2][0]=="x") win="x";else win="o";

    if(win=="x"){
        cout<<"x wins"<<endl;
        return true;
    }
    if(win=="o"){
        cout<<"o wins"<<endl;
        return true;
    }

    return false;
}

void printBoard(){
    clear();
    for(i=0;i<3;i++){
        for(j=0;j<3;j++)
            cout<<v[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void printError(string err){
    printBoard();
    cout<<err<<endl;
}

bool placePiece(int x, int y){
    if(v[x][y]=="#")
        if(piece)
            v[x][y]="x";
        else
            v[x][y]="o";
    else{
        printError("Piece already in place");
        return false;
    }
    return true;
}

void printTurn(bool next){
    if(next)
        if(piece)
            piece=0;
        else
            piece=1;
    if(piece)
        cout<<"x's turn-";
    else
        cout<<"o's turn-";
}

int convertInput(int UnconvertedInput){
    int finalInput;
    switch(UnconvertedInput){
        case(1) : finalInput=11; break;
        case(2) : finalInput=21; break;
        case(3) : finalInput=31; break;
        case(4) : finalInput=12; break;
        case(5) : finalInput=22; break;
        case(6) : finalInput=32; break;
        case(7) : finalInput=13; break;
        case(8) : finalInput=23; break;
        case(9) : finalInput=33; break;
        default : finalInput=UnconvertedInput; break;
    }
    return finalInput;
}

void botPlay(int oldInput){

    if(difficulty == "Random"){
        input = rand()%8+1;
        input = convertInput(input);
    }

    if(difficulty == "Impossible"){
        currentMove++;
        if(currentMove == 1)
            input = 33;
        if(currentMove == 2){
            switch(oldInput){
                case(13): input=31; break;
                case(23): input=31; break;
                default: input=13; break;
            }
        }
        cout<<currentMove;
        if(currentMove == 3){
            switch(oldInput){
                case(23): if(lastMove==13) input=22;
                          if(lastMove==31) input=31; break;
                case(32): if(lastMove==13) input=31;
                          if(lastMove==31) input=22; break;
                default: if(lastMove == 13) input=23;
                         if(lastMove == 31) input=32; break;
            }
        }
        if(currentMove == 4){
            switch(oldInput){
                case(11): if(lastMove==22) input=13;
                          if(lastMove==31) input=31; break;
                case(13): if(lastMove==22) input=11;
                          if(lastMove==31) input=22; break;
                default: input=32; break;
            }
        }
    }
    lastMove=input;

    if(placePiece(input%10-1,input/10-1)) return;
    else if(difficulty == "Random") botPlay(0);
}

int main(){

    if(difficulty == "Impossible")
        botStartFirst = 1;

    initializeBoard();

    while(true){

        printBoard();

        if(gameOver() || checkWin()) break;

        printTurn(1);

        if(botStartFirst == true && PvP == false){
            botPlay(input);

            printBoard();

            if(gameOver() || checkWin()) break;

            printTurn(1);
        }


        while(true){

            cin>>input;

            if(convert) input = convertInput(input);

            if(input == int(input) && input%10 <= 3 && input/10 <= 3 && input > 10){
                if(placePiece(input%10-1,input/10-1))
                    break;
                else{
                    printTurn(0);
                    continue;
                }
            }else{
                printError("Incorrect value (should be: ColumnRow  EX: 11 or   1 to 9 if convertion is active)");
                printTurn(0);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }

        if(!PvP){
            botStartFirst = 1;
        }
    }

    std::cin.get();
    std::cin.get();
}