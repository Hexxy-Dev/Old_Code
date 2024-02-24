//#include <stdarg.h>

void _start();
typedef int i32;    typedef unsigned int ui32;
typedef short i16;  typedef unsigned short ui16;
typedef char i8;    typedef unsigned char ui8;
typedef unsigned char byte;

#define DEBUG

i32 isDigit(char c) { return (c >= '0' && c <= '9'); }
i32 isLowerCaseLetter(char c) { return (c >= 'a' && c <= 'z'); }
i32 isUpperCaseLetter(char c) { return (c >= 'A' && c <= 'Z'); }
i32 isWhiteSpace(char c) { return (c >= 0x09 && c <= 0x0D || c == 0x20); }
i32 isSymbol(char c) { return ((c >= 0x21 && c <= 0x2F) || (c >= 0x3A && c <= 0x40) || (c >= 0x5B && c <= 0x60) || (c >= 0x7B && c <= 0x7E)); }
i32 isPunctuation(char c) { return (c == '!' || c == '"' || c == '\'' || c == ',' || c == '.' || c == ':' || c == ';' || c == '?' || c == '`'); }
i32 isAlpha(char c) { return (isLowerCaseLetter(c) || isUpperCaseLetter(c)); }
i32 isAlpahNumeric(char c) { return (isDigit(c) || isAlpha(c)); }

//exit with ret code 0
void _exit()
{
    asm("xor %eax, %eax;"
        "inc %eax;"
        "xor %ebx, %ebx;"
        "int $0x80;");
}
//*
void exit(i32 code)
{
    asm("xor %%eax, %%eax;"
        "inc %%eax;"
        "mov %0, %%ebx;"
        //"mov $0x0, %%bl;"
        "int $0x80;"
        ::"r"(code)
        :"%eax","%ebx","memory");
}

void writeChar(char c)
{
    asm("mov $0x4, %%eax;"
        "mov $0x1, %%ebx;"
        "mov %0, %%ecx;"
        "mov $0x1, %%edx;"
        "int $0x80;"
        ::"r"(&c)
        :"%eax","%ebx","%ecx","%edx","memory");
}

int strlen(const char* s)
{
    ui32 i = 0;
    while(s[i] != '\0') ++i;
    return i;
}

void writeCharP(const char* s, ui32 size)
{
    asm("mov $0x4, %%eax;"
        "mov $0x1, %%ebx;"
        "mov %0, %%ecx;"
        "mov %1, %%edx;"
        "int $0x80;"
        ::"r"(s),"r"(size)
        :"%eax","%ebx","%ecx","%edx","memory");
}
void writeStr(const char* s) { writeCharP(s,strlen(s)); }


ui32 intToChrP(ui32 n, char* buf)
{
    // TRY TO REWRITE IN ASM WITH STACK!!!!
    i32 i = -1;
    while(n){
        buf[++i] = '0' + n % 10;
        n /= 10;
    }
    for(ui32 j = 0; j < (i + 1) / 2; ++j){
        char t = buf[i - j];
        buf[i - j] = buf[j];
        buf[j] = t;
    }
    return i + 1;
}
void intToStr(ui32 n, char* buf)
{
    ui32 i = intToChrP(n, buf);
    buf[i] = '\0';
}

void writeInt(int n)
{
    static char FUNCTION_WRITE_INT_INTERNAL_BUFFER[10];//2147483647 (maxint) has 10 digits
    intToStr(n, FUNCTION_WRITE_INT_INTERNAL_BUFFER);
    writeStr(FUNCTION_WRITE_INT_INTERNAL_BUFFER);
}


void aFailed(const char* file, int line, const char* expr) {
    writeStr("ASSERTION FAILED: ");
    writeStr(file);
    writeStr(" at line: ");
    writeInt(line);
    writeStr(" (");
    writeStr(expr);
    writeStr(")\n");
    exit(-1);
}

#ifdef DEBUG
#define ASSERT(expr) \
    if (!(expr)) \
        aFailed(__FILE__, __LINE__,#expr)
#else
#define ASSERT(expr)
#endif

//void log_raw(char c) { writeChar(c); }
//void log_raw(const char* s) { writeStr(s); }
//void log_raw(i32 n) { writeInt(n); }
//
//void log(char c) { log_raw(c); writeChar('\n'); }
//void log(const char* s) { log_raw(s); writeChar('\n'); }
//void log(i32 n) { log_raw(n); writeChar('\n'); }

int main()
{
    ASSERT(sizeof(i32) == 4);       ASSERT(sizeof(ui32) == 4);
    ASSERT(sizeof(i16) == 2);     ASSERT(sizeof(ui16) == 2);
    ASSERT(sizeof(i8) == 1);      ASSERT(sizeof(ui8) == 1);
    ASSERT(sizeof(long long) == 8); ASSERT(sizeof(unsigned long long) == 8);
    
    ASSERT(sizeof(float) == 4);
    ASSERT(sizeof(double) == 8);
    ASSERT(sizeof(long double) == 12);//not 16??


    writeStr("Hello, world!\n");
    writeChar('H');
    writeChar('H');
    writeChar('H');
    writeChar('\n');
    writeStr("HMMMMMMMMMMM\n");
    writeInt(24);
    writeChar('\n');
    writeInt(2147483647);

    if(isAlpahNumeric('B') && isPunctuation('`') && isSymbol(0x7C) && isWhiteSpace(' '))
        writeStr("SUCCESS");
    
    if(isAlpahNumeric('1') && isPunctuation('!') && isSymbol('$') && isWhiteSpace('\n'))
        writeStr("SUCCESS2");
    
    if(!(isAlpahNumeric('!') && isPunctuation('A') && isSymbol('A') && isWhiteSpace('A')))
        writeStr("SUCCESS3");

    //log(14);
    //log("HMMMMMM");
    //log('a');

    return 7;
}//*/


void _start()
{
    //asm("nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;");
    asm("nop;nop;");
    //asm("1:nop;nop;jmp 1;nop");
    exit(main());//816 bytes
    //exit(8);//368 bytes
    
    //_exit();//360 bytes
}