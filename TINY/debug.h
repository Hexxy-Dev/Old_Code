#pragma once

#include "./start_essentials.h"
#include "./strings.h"
#include "./IO.h"

#ifdef DEBUG

// TODO: REMOVE THIS AND IMPLEMENT OWN!!!!!!
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_same<T, char>::value>::type
log_raw(T c) { logChar(c); }

void log_raw(const char* s) { logCharP(s,strlen(s)); }

template<typename T>
typename std::enable_if<std::is_same<T, ui32>::value || std::is_same<T, ui16>::value || std::is_same<T, ui8>::value || std::is_same<T, byte>::value || std::is_same<T, i32>::value || std::is_same<T, i16>::value || std::is_same<T, i8>::value>::type
log_raw(T n) {
    static char FUNCTION_WRITE_INT_INTERNAL_BUFFER[10];//2147483647 (maxint) has 10 digits
    if(n < 0)
        logChar('-');
    intToStr(n, FUNCTION_WRITE_INT_INTERNAL_BUFFER);
    log_raw(FUNCTION_WRITE_INT_INTERNAL_BUFFER);
}



template<typename T>
typename std::enable_if<std::is_same<T, char>::value>::type
log(T c) { log_raw(c); logChar('\n'); }

void log(const char* s) { log_raw(s); logChar('\n'); }

template<typename T>
typename std::enable_if<std::is_same<T, ui32>::value || std::is_same<T, ui16>::value || std::is_same<T, ui8>::value || std::is_same<T, byte>::value || std::is_same<T, i32>::value || std::is_same<T, i16>::value || std::is_same<T, i8>::value>::type
log(T n) { log_raw(n); logChar('\n'); }


void aFailed(const char* file, ui32 line, const char* expr) {
    log_raw("ASSERTION FAILED: ");
    log_raw(file);
    log_raw(" at line: ");
    log_raw(line);
    log_raw(" (");
    log_raw(expr);
    log_raw(")\n");
    exit(-1);
}


#define ASSERT(expr) \
    if (!(expr)) \
        aFailed(__FILE__, __LINE__,#expr)
#define log_raw(X) log_raw(X)
#define log(X) log(X)

#else

#define ASSERT(expr)
#define log_raw(X)
#define log(X)

#endif