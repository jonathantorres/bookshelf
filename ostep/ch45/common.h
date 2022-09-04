#ifndef __COMMON_h__
#define __COMMON_h__

#include <stdio.h>
#include <sys/time.h>
#include <assert.h>

// Simple routine to return absolute time (in seconds).
double time_get_seconds() {
    struct timeval t;
    int rc = gettimeofday(&t, NULL);
    assert(rc == 0);
    return (double) ((double)t.tv_sec + (double)t.tv_usec / 1e6);
}

#endif
