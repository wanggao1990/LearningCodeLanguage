#include "Date.h"

#ifndef _WIN32
#include <sys/time.h>
#endif

#include <cstdlib>
#include <iostream>
#include <string.h>

#ifdef _WIN32
#include <WinSock2.h>
#include <time.h>
#endif

namespace netlib{


const Date Date::date()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    int64_t seconds = tv.tv_sec;
    return Date(seconds * MICRO_SECONDS_PRE_SEC + tv.tv_usec);
}

const Date Date::after(double second) const
{
    return Date(microSecondsSinceEpoch_ + second * MICRO_SECONDS_PRE_SEC);
}

const Date Date::roundSecond() const
{
    return Date(microSecondsSinceEpoch_ -
                (microSecondsSinceEpoch_ % MICRO_SECONDS_PRE_SEC));
}


} // namespace netlib
