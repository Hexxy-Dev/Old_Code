#include <iostream>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

void Sort3(int* buffer) {
asm volatile(
"mov 0x4(%0), %%r8d \n"
"mov 0x8(%0), %%edx \n"
"mov 0x8(%0), %%ecx \n"
"cmp %%r8d, %%ecx \n"
"cmovge %%r8d, %%edx \n"
"cmovl %%r8d, %%ecx \n"
"mov %%ecx, %%r8d \n"
"mov (%0), %%eax \n"
"cmp %%eax, %%r8d \n"
"cmovge %%eax, %%r8d \n"
"cmovl %%eax, %%ecx \n"
"mov %%ecx, 0x8(%0) \n"
"cmp %%edx, %%eax \n"
"cmovle %%edx, %%r8d \n"
"cmovg %%edx, %%eax \n"
"mov %%r8d, 0x4(%0) \n"
"mov %%eax, (%0) \n"
: "+r"(buffer)
:
: "eax", "ecx", "edx", "r8d", "memory");
}

void Sort4(int* buffer) {
asm volatile(
"mov (%0), %%eax \n"
"mov 0x4(%0), %%ecx \n"
"mov 0x8(%0), %%edx \n"
"cmp %%eax, %%edx \n"
"mov %%ecx, %%r9d \n"
"mov (%0), %%r8d \n"
"cmovg %%edx, %%r8d \n"
"mov %%r8d, %%r10d \n"
"cmovg %%eax, %%edx \n"
"mov 0xc(%0), %%eax \n"
"cmp %%ecx, %%eax \n"
"cmovge %%eax, %%r9d \n"
"cmovge %%ecx, %%eax \n"
"cmp %%r10d, %%r9d \n"
"cmovge %%r9d, %%r10d \n"
"cmovge %%r8d, %%r9d \n"
"mov %%r10d, 0xc(%0) \n"
"mov %%edx, %%r10d \n"
"cmp %%edx, %%eax \n"
"cmovge %%eax, %%r10d \n"
"cmovge %%edx, %%eax \n"
"mov %%eax, (%0) \n"
"cmp %%r9d, %%r10d \n"
"mov %%r9d, %%edx \n"
"cmovg %%r10d, %%edx \n"
"mov %%edx, 0x8(%0) \n"
"cmovge %%r9d, %%r10d \n"
"mov %%r10d, 0x4(%0) \n"
: "+r"(buffer)
:
: "eax", "ecx", "edx", "r8d", "r9d", "memory");
}

void Sort5(int* buffer) {
asm volatile(
"mov (%0), %%eax \n"
"mov %%eax, %%ecx \n"
"mov 0x4(%0), %%edx \n"
"cmp %%edx, %%eax \n"
"cmovg %%edx, %%eax \n"
"cmovl %%edx, %%ecx \n"
"mov 0x8(%0), %%r8d \n"
"mov 0xc(%0), %%r9d \n"
"mov %%r8d, %%r10d \n"
"cmp %%r9d, %%r10d \n"
"cmovl %%r9d, %%r10d \n"
"mov 0x10(%0), %%edx \n"
"cmovge %%r9d, %%r8d \n"
"mov %%r8d, %%r9d \n"
"cmp %%eax, %%r9d \n"
"cmovge %%eax, %%r8d \n"
"cmovge %%r9d, %%eax \n"
"cmp %%edx, %%r10d \n"
"mov %%edx, %%r9d \n"
"cmovg %%r10d, %%edx \n"
"cmovg %%r9d, %%r10d \n"
"cmp %%r9d, %%r8d \n"
"cmovle %%r8d, %%r9d \n"
"cmovle %%r10d, %%r8d \n"
"mov %%r9d, (%0) \n"
"cmp %%ecx, %%r10d \n"
"cmovge %%ecx, %%r8d \n"
"cmovl %%ecx, %%r10d \n"
"cmp %%eax, %%r8d \n"
"mov %%eax, %%r9d \n"
"cmovge %%r8d, %%eax \n"
"cmovg %%r9d, %%r8d \n"
"mov %%r8d, 0x4(%0) \n"
"cmp %%r10d, %%edx \n"
"cmovle %%edx, %%r10d \n"
"cmovge %%edx, %%ecx \n"
"mov %%ecx, 0x10(%0) \n"
"cmp %%eax, %%r10d \n"
"cmovl %%r10d, %%eax \n"
"cmovge %%r10d, %%r9d \n"
"mov %%eax, 0x8(%0) \n"
"mov %%r9d, 0xc(%0) \n"
: "+r"(buffer)
:
: "eax", "ecx", "edx", "r8d", "r9d", "r10d", "memory");
}

#include <chrono>

#define TESTI(N, SIZE, FUNCTION, ...)                                                                   \
do{                                                                                                     \
    int buffer[ SIZE ];                                                                                 \
    uint64_t total = 0;                                                                                 \
    for(uint64_t i = 0; i < iter; i++) {                                                                \
        for(int i = 0; i < sizeof buffer/sizeof *buffer; i++)                                           \
            buffer[i] = rand();                                                                         \
        auto StartTime = std::chrono::system_clock::now();                                              \
        FUNCTION(__VA_ARGS__);                                                                          \
        auto EndTime = std::chrono::system_clock::now();                                                \
        total += std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime).count();     \
        for(int i = 0; i < sizeof buffer/sizeof *buffer - 1; i++)                                       \
            if(buffer[i] > buffer[i+1])                                                                 \
               throw "NOOM";                                                                            \
    }                                                                                                   \
    multiple ## N += (long double)total / iter;                                                         \
}while(0)

#define TEST(SIZE)                                                          \
do{                                                                         \
    long double multiple1 = 0, multiple2 = 0;                               \
    for(int k = 0; k < outerIter; k++) {                                    \
        TESTI(1, SIZE, Sort ## SIZE, (buffer));                             \
        TESTI(2, SIZE, std::sort, buffer, &buffer[SIZE]);                   \
    }                                                                       \
    printf("------------------\nSort%d: %Lf\nstd::sort: %Lf\n", SIZE,       \
    multiple1 / outerIter, multiple2 / outerIter);                          \
}while(0)

int main()
{
    srand(time(NULL));
    uint64_t iter = 40000;
    uint64_t outerIter = 300;
    TEST(3);
    TEST(4);
    TEST(5);

    //only 32 bit
}
