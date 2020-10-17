#pragma once

#include "netlib/utils/NonCopyable.h"

#include <string>

#ifndef _WIN32
#include <unistd.h>
#endif

#include <fcntl.h>


namespace netlib{

// socket
class Socket : NonCopyable
{
public:
    static int createNonblockingSocketOrDie(int family);




    int fd()
    {
        return sockFd_;
    }

protected:
    int sockFd_;

};





}