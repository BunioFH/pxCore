// pxCore CopyRight 2005-2006 John Robinson
// Portable Framebuffer and Windowing Library
// pxTimerNative.cpp

#include "../pxTimer.h"

#include <stdlib.h>
#include <sys/time.h>

#define USE_CGT

#ifndef USE_CGT
#include <sys/time.h>
#else
#include <time.h>
#endif

static inline double pxGetTime( const double mul = 1.0 ) {
#ifndef USE_CGT
    timeval tv;
    gettimeofday(&tv, NULL);
    return mul * tv.tv_sec + (mul * tv.tv_usec / 1000000.0);
#else
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return mul * ts.tv_sec + (mul * ts.tv_nsec / 1000000000.0 );
#endif
}

double  pxSeconds()
{
    return pxGetTime();
}

double pxMilliseconds()
{
    return pxGetTime( 1000.0 );
}

double  pxMicroseconds()
{
    return pxGetTime( 1000000.0 );
}

void pxSleepMS(unsigned long msToSleep)
{
    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1000 * msToSleep;
    select(0, NULL, NULL, NULL, &tv);
}
