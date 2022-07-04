#ifndef CAN_MSG_RECEIVE_H
#define CAN_MSG_RECEIVE_H
#include "controlcan.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "controlcan.h"

#include <ctime>
#include <cstdlib>
#include "unistd.h"

namespace canmsgreceive {
    class Can_Msg_Receive
    {
        private:
            /* data */
        public:
            Can_Msg_Receive(/* args */);
            ~Can_Msg_Receive();
    }; 
}

#endif 
