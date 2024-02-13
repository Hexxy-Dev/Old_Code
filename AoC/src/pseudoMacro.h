#include "tools.h"
// NO INCLUDE GUARD ON PURPOSE
// Note especially FOO, which we can #define before #include-ing this file,
// in order to alter which files it will in turn #include.
// FOO fulfils the role of "parameter" in this pseudo-macro.

//#define INCLUDE_FILE(HEAD,TAIL) STRINGIFY( CAT_3(HEAD,FOO,TAIL) )

//#include INCLUDE_FILE(head1,tail1.hpp) // expands to #head1FOOtail1.hpp

#ifdef DAY
	#undef IDAY
	#define IDAY DAY
#else
	#define DAY IDAY
	#define DAY_FLAG
#endif // DAY

#define INCLUDE_FILE(TAIL) STRINGIFY( CAT_2(IDAY,TAIL) )
#include INCLUDE_FILE(.h)

#ifdef DAY_FLAG
	#undef DAY
	#undef DAY_FLAG
#endif // DAY_FLAG

#undef INCLUDE_FILE
#undef IDAY