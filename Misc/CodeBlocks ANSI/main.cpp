#include <windows.h>
#include <iostream>

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN  0x0008

int main(){
    DWORD l_mode;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hStdout,&l_mode);
    SetConsoleMode( hStdout, l_mode |
                    ENABLE_VIRTUAL_TERMINAL_PROCESSING |
                    DISABLE_NEWLINE_AUTO_RETURN );

    for (int i = 0; i < 10; ++i)
        std::cout << "\x1b[38;2;" << 5 * i << ";" << 255 - 10 * i << ";220m"
                << "ANSI Escape Sequence " << i << std::endl;

        std::cout<<"\33[104m   ";
}