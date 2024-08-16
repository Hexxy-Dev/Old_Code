#include <stdio.h>
#define addi        puts("1");
#define j           puts("2");
#define li          puts("3");
#define ret         puts("4");
#define add         puts("5");
#define bge         puts("6");
#define beqz        puts("7");
#define fmv_s       puts("8");
#define mv          puts("9");
#define sd          puts("10");
#define call        puts("11");
#define lb          puts("12");
#define ld          puts("13");
#define lw          puts("14");
#define sb          puts("15");
#define fld         puts("16");
#define fsw         puts("17");
#define la          puts("18");
#define slli        puts("19");
#define ble         puts("20");
#define fgt_s       puts("21");
#define flt_s       puts("22");
#define flw         puts("23");
#define fmul_d      puts("24");
#define fsub_d      puts("25");
#define srai        puts("26");
#define bgt         puts("27");
#define bnez        puts("28");
#define fadd_d      puts("29");
#define fadd_s      puts("30");
#define fmul_s      puts("31");
#define fmv_s_x     puts("32");
#define fsqrt_d     puts("33");
#define sub         puts("34");


const char* hmmmmmmmm;
int x = 0;
int nextbit(){ return hmmmmmmmm[x++] - '0'; }

const char* hmmmmm2[] = {
"111","1101","1100","1001","1000","0001","0000","10111","10100","10110","01010","01110","01011","01101","01100","00110","011111","101010","101011","001010","001111","010000","010001","010010","010011","001000","0011101","0010010", "0010011","0111100","0111101","0010110","0010111","0011100"
};
int hmm3=sizeof(hmmmmm2)/sizeof(hmmmmm2[0]);


void hmm(){
if(nextbit())//1
    if(nextbit())//11
        if(nextbit())//111
            addi
        else//110
            if(nextbit())//1101
                j
            else//1100
                li
    else//10
        if(nextbit())//101
            if(nextbit())//1011
                if(nextbit())//10111
                    fmv_s
                else//10110
                    sd
            else//1010
                if(nextbit())//10101
                    if(nextbit())//101011
                        slli
                    else//101010
                        la
                else//10100
                    mv
        else//100
            if(nextbit())//1001
                ret
            else//1000
                add
else//0
    if(nextbit())//01
        if(nextbit())//011
            if(nextbit())//0111
                if(nextbit())//01111
                    if(nextbit())//011111
                        fsw
                    else//011110
                        if(nextbit())//0111101
                            fmul_s
                        else//0111100
                            fadd_s
                else//01110
                    lb
            else//0110
                if(nextbit())//01101
                    lw
                else//01100
                    sb
        else//010
            if(nextbit())//0101
                if(nextbit())//01011
                    ld
                else//01010
                    call
            else//0100
                if(nextbit())//01001
                    if(nextbit())//010011
                        fsub_d
                    else//010010
                        fmul_d
                else//01000
                    if(nextbit())//010001
                        flw
                    else//010000
                        flt_s
    else//00
        if(nextbit())//001
            if(nextbit())//0011
                if(nextbit())//00111
                    if(nextbit())//001111
                        fgt_s
                    else//001110
                        if(nextbit())//0011101
                            bgt
                        else//0011100
                            sub
                else//00110
                    fld
            else//0010
                if(nextbit())//00101
                    if(nextbit())//001011
                        if(nextbit())//0010111
                            fsqrt_d
                        else//0010110
                            fmv_s_x
                    else//001010
                        ble
                else//00100
                    if(nextbit())//001001
                        if(nextbit())//0010011
                            fadd_d
                        else//0010010
                            bnez
                    else//001000
                        srai
        else//000
            if(nextbit())//0001
                bge
            else//0000
                beqz
}

unsigned int getrand() {
    unsigned int randval;
    FILE *f = fopen("/dev/random", "r");
    fread(&randval, sizeof(randval), 1, f);
    fclose(f);
    return randval;
}
#include <string.h>

int hmmmm[1000];
const char* hmmm[] ={"addi","j","li","ret","add","bge","beqz","fmv.s","mv","sd","call","lb","ld","lw","sb","fld","fsw","la","slli","ble","fgt.s","flt.s","flw","fmul.d","fsub.d","srai","bgt","bnez","fadd.d","fadd.s","fmul.s","fmv.s.x","fsqrt.d","sub"};
const int hmmml = sizeof(hmmm)/sizeof(hmmm[0]);

#define HASH_SIZE 34  // You can adjust this based on the size of your array

unsigned int custom_hash(const char *str) {
    unsigned int hash = 0;

    while (*str) {
        hash = (hash * 31) + (*str++);  // 31 is a prime number, helps with distribution
    }

    return hash % HASH_SIZE;
}
int main(){
    //for(int i = 0; i < 1000; ++i) {
    //    x = 0;
    //    hmmmmmmmm = hmmmmm2[getrand() % hmm3];
    //    hmm();
    //}

    for(int y = hmmml; y < hmmml+30; ++y) {
        for(int i = 0; i < 1000; ++i)
            hmmmm[i] = 0;

        for(int i = 0; i < hmmml; ++i) {
            //int s = 0;
            //for(int k = 0; k < strlen(hmmm[i]); ++k)
            //    s += hmmm[i][k] - '0';
            //int a = s % y;
            //hmmmm[a]++;
            hmmmm[custom_hash(hmmm[i]) % y]++;
        }
        
        int s = 0;
        for(int i = 0; i < 1000; ++i) {
            if(hmmmm[i])
                s++;
            //printf("%d ", hmmmm[i]);
        }
        printf("%d - %d\t\t", y, s);
        if(s == 0)
            puts("WINNERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR");
    }
}


















/*
THIS SUCCESSFULLY PRINTS OUT ALL KEYWORDS USED IN A FILE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    byte buffer[300];
    byte c = ' ';
    while(c != '\0') {
        c = '\0';
        readByte(c);//logChar(c);
        if(c == '\t') readByte(c);
        if(c == '#') while(c != '\n' && c != '\0') {
            c = '\0';
            readByte(c);
        }

        if(isLowerCaseLetter(c)) {
            ui8 index = 0;
            buffer[index++] = c;
            readByte(c);
            buffer[index++] = c;
            if(isDigit(c)) { // register name
                buffer[index] = '\0';
                log((char*)buffer);
                logChar('\n');
            } else {
                while(isLowerCaseLetter(c)) {
                    readByte(c);
                    buffer[index++] = c;
                }
                buffer[index] = '\0';
                log((char*)buffer);
                logChar('\n');
                //with this approach we eat the thing after the word as well :/

            }
        } else if(isDigit(c)) { //label
            do {
                c = '\0';
                readByte(c);
            } while(c != '\n' && c != '\0');
        } else
            if(c == '.') { // . directives
                readByte(c);
                switch(c) {
                    case 's': {
                        readBytes(buffer, 8); // .section .
                        readByte(c);
                        if(c == 't') // .section .t
                            readBytes(buffer, 4); //ext\n
                    }break;
                    case 'g': {
                        readBytes(buffer, 6); // .global 
                        ui8 func_name_len = 0;
                        do { // function label + \n
                            readByte(c); 
                            ++func_name_len;
                        } while(c != '\n');
                        readBytes(buffer, func_name_len); // function label + \n
                    }break;
                }
            }
    }
*/
