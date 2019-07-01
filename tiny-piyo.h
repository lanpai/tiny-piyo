#ifndef _TINY_PIYO_H
#define _TINY_PIYO_H

#define PIYO_VERBOSITY 1

#ifdef PIYO_NONE
#   undef PIYO_VERBOSITY
#   define PIYO_VERBOSITY 0
#endif

#ifdef PIYO_WARNING
#   undef PIYO_VERBOSITY
#   define PIYO_VERBOSITY 2
#endif

#ifdef PIYO_VERBOSE
#   undef PIYO_VERBOSITY
#   define PIYO_VERBOSITY 3
#endif

/*
0 NONE
1 ERRORS
2 WARNINGS
3 VERBOSE
*/

#define GLEW_STATIC

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#endif
