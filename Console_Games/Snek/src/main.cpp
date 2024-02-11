#include <iostream>
#include <future>
#include <string>

void clear_screen() { puts("\033[H\033[J"); }

#include <unistd.h>
void sleep_ms(size_t milliseconds)
{
	struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

#include <ncurses.h>


#include <sstream>
#define SSTR( x ) static_cast< std::stringstream >( \
        ( std::stringstream() << std::dec << x ) ).str()


const bool debug_mode=false;

const int board_size = 31;  //should be odd number

int board[board_size+2][board_size+2];

char snek_head_char='^';
int snek_head_x,snek_head_y;
int current_snek_lenght=1;

int direction_x=-1,direction_y=0;
bool game_over=false;
bool has_eaten_fruit=false;
int game_speed=150;  //higher is slower

bool die_if_touch_wall=true;


void print_board(){
    int x,y;
    std::string display_board;

    clear_screen();

    display_board+="\n\r\t\t\t\t\t\t\t\t\t\t\t Score: ";
    display_board+=SSTR(current_snek_lenght);
    display_board+="\n\r";

    for(x=0;x<board_size;x++){
        display_board+="\t\t\t\t\t\t\t\t\t\t\t";
        for(y=0;y<board_size;y++){
            if(debug_mode)
                display_board+=SSTR(board[x][y]);
            else if(board[x][y]==-11)
                display_board+="#";
            else if(board[x][y]==-9)
                display_board+=" ";
            else if(board[x][y]==0)
                display_board+=snek_head_char;
            else if(board[x][y]>0)
                display_board+="o";
            else if(board[x][y]==-1)
                display_board+="X";
            else if(board[x][y]==-5)
                display_board+="Q";
            display_board+=" ";
        }
        display_board+="\n\r";
    }
    int i;
    std::cout<<display_board;
}

void initialize_board(){
    int x,y;

    for(y=0;y<board_size;y++)
        board[0][y]=-11;

    for(x=0;x<board_size;x++)
        board[x][0]=-11;

    for(x=0;x<board_size;x++)
        board[x][board_size-1]=-11;

    for(y=0;y<board_size;y++)
        board[board_size-1][y]=-11;

   for(x=1;x<board_size-1;x++)
        for(y=1;y<board_size-1;y++)
            board[x][y]=-9;
}

void create_snek(){
    int x=board_size/2,y=board_size/2,i;

    board[x][y]=0;
    snek_head_x=x;
    snek_head_y=y;
    for(i=1;i<=current_snek_lenght;i++)
        board[x+i][y]=i;

}

bool valid_move(int x,int y){
    if(board[snek_head_x+x][snek_head_y+y]==1)
        return 0;
    return 1;
}

void get_new_direction(){
    char key=0;
    do
    {
        key = getch();
        
        switch(key)
        {
            case 'W':
            case 'w':
                if(valid_move(-1,0)){
                    direction_x=-1;
                    direction_y=0;
                    snek_head_char='^';
                }
                break;
            case 'A':
            case 'a':
                if(valid_move(0,-1)){
                    direction_x=0;
                    direction_y=-1;
                    snek_head_char='<';
                }
                break;
            case 's':
            case 'S':
                if(valid_move(1,0)){
                    direction_x=1;
                    direction_y=0;
                    snek_head_char='v';
                }
                break;
            case 'D':
            case 'd':
                if(valid_move(0,1)){
                    direction_x=0;
                    direction_y=1;
                    snek_head_char='>';
                }
                break;
        }
    }while (key != 'P' && key!='p');
}

void try_to_move_snek_body(int x,int y,int new_piece_value){
    int coord_x=0,coord_y=0;
    int check_x[4]={x-1,x,x+1,x};
    int check_y[4]={y,y-1,y,y+1};
    int i;
    int j,k;
    for(i=0;i<4;i++)
        if(board[check_x[i]][check_y[i]]>0)
            if(board[check_x[i]][check_y[i]]==new_piece_value){
                coord_x=check_x[i];
                coord_y=check_y[i];
                break;
            }
    if(coord_x==0 && coord_y==0){
        board[x][y]=-9;
        return;
    }
    else{
        board[x][y]=board[coord_x][coord_y];
        if(!has_eaten_fruit){
            board[coord_x][coord_y]=-9;
        } else {
            has_eaten_fruit=false;
            for(j=1;j<board_size-1;j++)
                for(k=1;k<board_size-1;k++)
                    if(board[j][k]>1)
                        board[j][k]=board[j][k]+1;
            board[coord_x][coord_y]=2;
            current_snek_lenght++;
            return;
        }

        if(board[x][y]<=current_snek_lenght){
            board[coord_x][coord_y]=-1;
            try_to_move_snek_body(coord_x,coord_y,board[x][y]+1);
        } else return;
    }
}

void move_snek(){
    if(die_if_touch_wall)
        if(board[snek_head_x+direction_x][snek_head_y+direction_y]==-11){
            game_over=true;
            return;
        }
    else{
            // MUST IMPLEMENT WALL TELEPORT THAT WILL KEEP BODY AS WELL
    }
    if(board[snek_head_x+direction_x][snek_head_y+direction_y]>0){
        game_over=true;
        return;
    }

    board[snek_head_x][snek_head_y]=-1;

    try_to_move_snek_body(snek_head_x,snek_head_y,1);

    if(board[snek_head_x+direction_x][snek_head_y+direction_y]==-5)
        has_eaten_fruit=true;

    snek_head_x+=direction_x;
    snek_head_y+=direction_y;
    board[snek_head_x][snek_head_y]=0;
}

void plant_fruit(){
    int x,y;
    x=rand()%(board_size+3)+1;
    y=rand()%(board_size+3)+1;
    if(board[x][y]>=0 || board[x][y]==-11){
        plant_fruit();
        return;
    }
    board[x][y]=-5;
}

void tick_once(){
    move_snek();
    if(has_eaten_fruit)
        plant_fruit();
}

void start_game(){
    tick_once();
    print_board();
    sleep_ms(game_speed);
    if(!game_over)
        start_game();
}

void get_key_press(){
    auto fi = std::async(std::launch::async,get_new_direction);
    sleep_ms(10);
}

int main(){
    std::cout<<"\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r \t\t\t\t\t\t\t\t\t\t\t\t\t\t Press ENTER to start";
    std::cin.get();

    initscr();
    nl();
    cbreak();
    noecho();

    auto fi = std::async(std::launch::async,get_key_press);

    initialize_board();
    create_snek();
    plant_fruit();
    start_game();

    endwin();
    clear_screen();
    std::cout<<"\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r \t\t\t\t\t\t\t\t\t\t\t\t\t\t Game Over! \n\r";
    std::cout<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t Final score: "<<current_snek_lenght<<"\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r";
}

//TO DO:

//start animation
//end animation     different for hitting a wall or the snek

//new music       maybe from mp3 file

//settings from file