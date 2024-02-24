//exit with ret code 0
#pragma once
#include "./commons.h"

void _exit()
{
    asm("xor %eax, %eax;"
        "inc %eax;"
        "xor %ebx, %ebx;"
        "int $0x80;");
}

void exit(i32 code)
{
    asm("xor %%eax, %%eax;"
        "inc %%eax;"
        "mov %[code], %%ebx;"
        //"mov $0x0, %%bl;"
        "int $0x80;"
        ::[code]"i"(code)
        :"%eax","%ebx","memory");
}

//exit(8);//588
//_exit();//560 bytes
/*
C vs C++
deltas so far:
_exit   360     560     => 200  +55.5%
exit    368     588     => 220  +59.7%
        816     1192    => 376  +46.0%
        832     1212    => 380  +45.6%
        872     1248    => 376  +43.1%
so are we approatching 0????
//*/
