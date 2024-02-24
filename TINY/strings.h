#pragma once

#include "./commons.h"

i32 isDigit(char c) { return (c >= '0' && c <= '9'); }
i32 isLowerCaseLetter(char c) { return (c >= 'a' && c <= 'z'); }
i32 isUpperCaseLetter(char c) { return (c >= 'A' && c <= 'Z'); }
i32 isWhiteSpace(char c) { return (c >= 0x09 && c <= 0x0D || c == 0x20); }
i32 isSymbol(char c) { return ((c >= 0x21 && c <= 0x2F) || (c >= 0x3A && c <= 0x40) || (c >= 0x5B && c <= 0x60) || (c >= 0x7B && c <= 0x7E)); }
i32 isPunctuation(char c) { return (c == '!' || c == '"' || c == '\'' || c == ',' || c == '.' || c == ':' || c == ';' || c == '?' || c == '`'); }
i32 isAlpha(char c) { return (isLowerCaseLetter(c) || isUpperCaseLetter(c)); }
i32 isAlpahNumeric(char c) { return (isDigit(c) || isAlpha(c)); }

int strlen(const char* s)
{
    ui32 i = 0;
    while(s[i] != '\0') ++i;
    return i;
}

ui32 intToCharP(ui32 n, char* buf)
{
    ui32 size = 0;
    asm("mov $10, %%ecx;"
        "mov %[n], %%eax;"
        "l1:;"
        "xor %%edx, %%edx;"
        "cmp $0, %%eax;"
        "jz l1e;"
        "div %%ecx;"
        "incl %[size];"
        "add $0x30, %%edx;"
        "push %%edx;"
        "jmp l1;"
        "l1e:;"
        "mov %[size], %%ecx;"
        "mov %[buf], %%edx;"
        "l2:;"
        "cmp $0, %%ecx;"
        "jz l2e;"
        "pop %%eax;"
        "movb %%al, (%%edx, 1);"
        "incl %%edx;"
        "dec %%ecx;"
        "jmp l2;"
        "l2e:;"
        ::[size]"m"(size),[n]"r"(n),[buf]"r"(buf)
        :"eax","edx","ecx","memory");
    return size;
}

ui32 intToStr(ui32 n, char* buf)
{
    ui32 i = intToCharP(n, buf);
    buf[i] = '\0';
    return i;
}