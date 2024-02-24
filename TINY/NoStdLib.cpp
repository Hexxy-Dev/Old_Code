//#include <stdarg.h>
#include "./start_essentials.h"
#include "./commons.h"
#include "./strings.h"
#include "./debug.h"

int main()
{
    ASSERT(sizeof(i32) == 4);       ASSERT(sizeof(ui32) == 4);
    ASSERT(sizeof(i16) == 2);     ASSERT(sizeof(ui16) == 2);
    ASSERT(sizeof(i8) == 1);      ASSERT(sizeof(ui8) == 1);
    ASSERT(sizeof(long long) == 8); ASSERT(sizeof(unsigned long long) == 8);
    
    ASSERT(sizeof(float) == 4);
    ASSERT(sizeof(double) == 8);
    ASSERT(sizeof(long double) == 12);//not 16??


    log("Hello, world!");
    log_raw('H');
    log_raw('H');
    log_raw('H');
    log_raw('\n');
    log("HMMMMMMMMMMM");
    ui32 x = 3147483647;
    log(x);
    log(24);
    log(2147483647);

    if(isAlpahNumeric('B') && isPunctuation('`') && isSymbol(0x7C) && isWhiteSpace(' '))
        log("SUCCESS");
    
    if(isAlpahNumeric('1') && isPunctuation('!') && isSymbol('$') && isWhiteSpace('\n'))
        log("SUCCESS2");
    
    if(!(isAlpahNumeric('!') || isPunctuation('A') || isSymbol('A') || isWhiteSpace('A')))
        log("SUCCESS3");

    //log(14);
    //log("HMMMMMM");
    //log('a');

    return 7;
}

extern "C" void _start() { 
    //asm("nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;");
    exit(main()); }