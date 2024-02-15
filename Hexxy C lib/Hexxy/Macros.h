#ifndef HEXXY_MACROS_H
#define HEXXY_MACROS_H

#ifndef __STDC__
#define __STDC__ 0
#endif
#ifndef __STDC_VERSION__
#define __STDC_VERSION__ 0
#endif

// MACRO FOR FUNCTION WITH VARYING NUMBER OF ARGS

// example definition for FOO
//#define FOO(...) VFUNC(FOO, __VA_ARGS__)
//#define FOO2(x, y) ((x) + (y))
//#define FOO3(x, y, z) ((x) + (y) + (z))

// get number of arguments with __NARG__
#define __NARG__(...)  __NARG_I_(__VA_ARGS__,__RSEQ_N())
#define __NARG_I_(...) __ARG_N(__VA_ARGS__)
#define __ARG_N( \
	  _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
	 _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
	 _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
	 _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
	 _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
	 _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
	 _61,_62,_63,N,...) N
#define __RSEQ_N() \
	 63,62,61,60,                   \
	 59,58,57,56,55,54,53,52,51,50, \
	 49,48,47,46,45,44,43,42,41,40, \
	 39,38,37,36,35,34,33,32,31,30, \
	 29,28,27,26,25,24,23,22,21,20, \
	 19,18,17,16,15,14,13,12,11,10, \
	  9, 8, 7, 6, 5, 4, 3, 2, 1, 0

// general definition for any function name
#define _VFUNC_(name, n) name##n
#define _VFUNC(name, n) _VFUNC_(name, n)
#define VFUNC(func, ...) _VFUNC(func, __NARG__(__VA_ARGS__)) (__VA_ARGS__)




// MACRO FOR FUNCTION WITH DIFFERENT ARG TYPE

#define FIRST_ARG_(A, ...) A
#define SECOND_ARG_(A, B, ...) B
#define FIRST(A) FIRST_ARG_ A
#define SECOND(A) SECOND_ARG_ A

#if __STDC_VERSION__ >= 201112L

#define TSFUNC1(func, t1, ...) _Generic((SECOND((__VA_ARGS__))), \
										t1: func##_##t1			 \
										)(__VA_ARGS__)

#define TSFUNC2(func, t1, t2, ...) _Generic((SECOND((__VA_ARGS__))), \
										t1: func##_##t1,			 \
										t2: func##_##t2				 \
										)(__VA_ARGS__)


#define TFFUNC1(func, t1, ...) _Generic((FIRST((__VA_ARGS__))),	\
										t1: func##_##t1			\
										)(__VA_ARGS__)

#define TFFUNC2(func, t1, t2, ...) _Generic((FIRST((__VA_ARGS__))),	\
										t1: func##_##t1,			\
										t2: func##_##t2				\
										)(__VA_ARGS__)

#else
#define TSFUNC1(func, t1, ...)
#define TSFUNC2(func, t1, t2, ...)
#define TFFUNC1(func, t1, ...)
#define TFFUNC2(func, t1, t2, ...)
#endif



void check_compiler_version() {
	if (!__STDC__ && !__STDC_VERSION__) printf("The C compiler does not comply with the C89 or later standard!\nIt likely complies with the 1978 K&R C standard (informally known as C78).\n");
	else if (__STDC_VERSION__ >= 201710L) printf("The C compiler complies with the C17 standard.\n");
	else if (__STDC_VERSION__ >= 201112L) printf("The C compiler complies with the C11 standard.\n");
	else if (__STDC_VERSION__ >= 199901L) printf("The C compiler complies with the C99 standard.\n");
	else if (__STDC_VERSION__ >= 199409L) printf("The C compiler complies with the amended C90 standard (also known as C95).\n");
	else if (__STDC__) printf("The C compiler complies with the ANSI C89 / ISO C90 standard.\n");
	if (__STDC__) printf("\"__STDC__\": %ld\n", __STDC_VERSION__);
	if (__STDC_VERSION__) printf("\"__STDC_VERSION__\": %ld\n\n", __STDC_VERSION__);
}

#endif