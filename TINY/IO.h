#pragma once
#include "./commons.h"


void writeByte(byte c)
{
    asm("mov $0x4, %%eax;"
        "mov $0x1, %%ebx;"
        "mov %[c], %%ecx;"
        "mov $0x1, %%edx;"
        "int $0x80;"
        ::[c]"r"(&c)
        :"%eax","%ebx","%ecx","%edx","memory");
}

void writeBytes(const byte* s, ui32 size)
{
    asm("mov $0x4, %%eax;"
        "mov $0x1, %%ebx;"
        "mov %[sp], %%ecx;"
        "mov %[size], %%edx;"
        "int $0x80;"
        ::[sp]"r"(s),[size]"r"(size)
        :"%eax","%ebx","%ecx","%edx","memory");
}


// EXACT SAME FUNCTIONS BUT WITH DIFFERENT NAMES AND STDERR AS FILE DESCRIPTOR
#ifdef DEBUG

void logChar(char c)
{
    asm("mov $0x4, %%eax;"
        "mov $0x2, %%ebx;"
        "mov %[c], %%ecx;"
        "mov $0x1, %%edx;"
        "int $0x80;"
        ::[c]"r"(&c)
        :"%eax","%ebx","%ecx","%edx","memory");
}

void logCharP(const char* s, ui32 size)
{
    asm("mov $0x4, %%eax;"
        "mov $0x2, %%ebx;"
        "mov %[sp], %%ecx;"
        "mov %[size], %%edx;"
        "int $0x80;"
        ::[sp]"r"(s),[size]"r"(size)
        :"%eax","%ebx","%ecx","%edx","memory");
}

#endif