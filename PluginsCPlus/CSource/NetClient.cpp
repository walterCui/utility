//
//  NetClient.cpp
//  EPet
//
//  Created by walter on 14-9-26.
//  Copyright (c) 2014年 com.Example. All rights reserved.
//

#include "NetClient.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>
#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>
#include "Converter.h"


#define Byte unsigned char

bool NetClient::connect(char *ip, int port)
{
    if(socketFileDescriptor == -1)
    {
        error = (char*)"the socketFileDescriptor is null";
        return  false;
    }
    
    struct sockaddr_in address;
    bzero(&address, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);
    //std::thread(connectThreaddddd);
    
    int oldFL = fcntl(socketFileDescriptor, F_GETFL,0);
    
    if(fcntl(socketFileDescriptor, F_SETFL, oldFL | O_NONBLOCK) < 0)
    {
        //error.
        error = strerror(errno);
        return false;
    }
    
    int connectResult = ::connect(socketFileDescriptor,(struct sockaddr*)&address,sizeof(struct sockaddr));
    if(-1 == connectResult)
    {
        if(errno != EINPROGRESS)
        {
            error = strerror(errno);
        }
        else
        {
            fd_set fdCnn;
            __DARWIN_FD_ZERO(&fdCnn);
            __DARWIN_FD_SET(socketFileDescriptor,&fdCnn);
            struct timeval timeout;
            timeout.tv_sec = 3;
            timeout.tv_usec = 0;
            if(select(socketFileDescriptor+1, NULL, &fdCnn, NULL, &timeout) > 0)
            {
                if(__DARWIN_FD_ISSET(socketFileDescriptor, &fdCnn))
                {
                    int errorNum;
                    socklen_t len = sizeof(errorNum);
                    getsockopt(socketFileDescriptor, SOL_SOCKET, SO_ERROR, &errorNum, &len);
                    if(errorNum != 0)
                    {
                        error = strerror(errorNum);//(char*)"connect error";
                    }
                    else
                        error = NULL;
                    
                }
                else
                {
                    error = (char*)"connect error";
                }
            }
            else
            {
                error = strerror(errno);//(char*)"time out";
            }

        }
    }
    else{
        error = NULL;
    }
    
    fcntl(socketFileDescriptor, F_SETFL, oldFL);
    return  error == NULL;
}

void NetClient::HandleData(Byte *data)
{
    int i = 20;//head.
    short msgId = Converter::getShort(data, i);
    short msgType = Converter::getShort(data, i);
    if(msgType == 1)
    {
        //response.
        if(delegate!= NULL)
            delegate->handleResponse(msgId, data);
    }
    else if (msgType == 2)
    {
        //event.
        if(delegate != NULL)
            delegate->handleEvent(msgId,data);
    }
    //由使用者决定什么时候释放.
    //delete [] data;
}
#undef Byte