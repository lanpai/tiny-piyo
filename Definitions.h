#ifndef _TINY_PIYO_H
#define _TINY_PIYO_H

#define FRAMETIME_INTERVAL 60
#define MAX_UPDATE_STEPS 10

#define PI 3.141592653589793238462643383f

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

#endif
