#pragma once

//DEFAULT
//all others should be added as well
#ifndef LANGUAGE_RO
#ifndef LANGUAGE_EN
#define LANGUAGE_EN
#endif // !LANGUAGE_EN
#endif // !LANGUAGE


#ifdef LANGUAGE_EN
#include "EN.h"
#undef LANGUAGE_EN
#endif // EN

#ifdef LANGUAGE_RO
#include "RO.h"
#undef LANGUAGE_RO
#endif // RO