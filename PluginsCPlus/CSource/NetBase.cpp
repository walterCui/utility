//
//  NetBase.cpp
//  EPet
//
//  Created by walter on 14-9-26.
//  Copyright (c) 2014年 com.Example. All rights reserved.
//

#include "NetBase.h"

#include <netinet/in.h>
#include <unistd.h>
#include "Converter.h"

#define Byte unsigned char
#define MIN(i,j) ( i > j ? j : i )

NetBase::NetBase()
{
    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1) {
        error = (char*)"not create socket.";
    }
    else
    {
        init();
        error = NULL;
    }
}

NetBase::NetBase(int socketHandle)
{
    socketFileDescriptor = socketHandle;
    if (socketFileDescriptor == -1) {
        error = (char*)"not create socket.";
    }
    else
    {
        init();
        error = NULL;
    }

}

void NetBase::init()
{
    writeBuff = new std::queue<IDataWraper*>;
    readBuff = new std::queue<Byte*>;
    swapeBuff = new std::queue<IDataWraper*>;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100;
}

NetBase::~NetBase()
{
    delete writeBuff;
    delete readBuff;
    delete swapeBuff;
    
    close();
}

char* NetBase::getError()
{
    return  error;
}

bool NetBase::send(IDataWraper *data)
{
    if(socketFileDescriptor == -1)
        return  false;
    if(data == NULL)
        return true;
    mtx.lock();
    writeBuff->push(data);
    mtx.unlock();
    return  true;
}

void NetBase::update()
{
    Byte *ptr;
    std::queue<IDataWraper*> *temp;
    //write.
    mtx.lock();
    if(!writeBuff->empty())
    {
        temp = writeBuff;
        writeBuff = swapeBuff;
        swapeBuff = temp;
    }
    mtx.unlock();
    for(int i = 0, max  = swapeBuff->size(); i < max; i++)
    {
        dateWraper = swapeBuff->front();
        dataSize = dateWraper->serialization(data);
        if(dataSize > 0)
        {
            Converter::toBytes(data, 0, dataSize);
            ptr = data;
            while (true) {
                wtRdSize = write(socketFileDescriptor, ptr, dataSize);
                if(wtRdSize <= 0)
                {
                    //error.
                    break;
                }
                else
                {
                    if(wtRdSize < dataSize)
                    {
                        //not write over.
                        dataSize -= wtRdSize;
                        ptr += wtRdSize;
                    }
                    else
                        break;
                }
            }
            
        }
        swapeBuff->pop();
    }
    
    //read.
    __DARWIN_FD_ZERO(&fdset);
    __DARWIN_FD_SET(socketFileDescriptor,&fdset);
    if(select(socketFileDescriptor+1, &fdset, NULL, NULL, &timeout) > 0)
    {
        if(__DARWIN_FD_ISSET(socketFileDescriptor, &fdset))
        {
            wtRdSize = read(socketFileDescriptor, data, BUFFMAXSIZE);
            UnPackData(wtRdSize, 0);
        }
    }
}

void NetBase::UnPackData(int length, int start)
{
    if(length <= 0)
    {
        //error.
        return;
    }
    
    int needLength;
    
    //new data.
    if(readDataTemp.data == NULL)
    {
        readDataTemp.dataLength = Converter::getInt(data, start);
        start -= 4; //因为Converter::getInt 会修改start的数值,故需要还原回去.
        if(readDataTemp.dataLength <= 0)
        {
            //error.
            readDataTemp.data = NULL;
            return;
        }
        readDataTemp.data = new Byte[readDataTemp.dataLength];
        
        //copy data.
        readDataTemp.index = MIN(readDataTemp.dataLength, length);
        for(int i = 0; i < readDataTemp.index; i++)
        {
            readDataTemp.data[i] = data[i+start];
        }
        
        needLength = readDataTemp.dataLength;
    }
    else
    {
        needLength = readDataTemp.dataLength - readDataTemp.index;
        int min = MIN(needLength, length);
        
        for(int i = 0;  i < min; i++)
        {
            readDataTemp.data[i+readDataTemp.index] = data[i+start];
        }
        readDataTemp.index += min;
    }
    
    if(length >= needLength)
    {
        //pushReadData();
        HandleData(readDataTemp.data);
        readDataTemp.data = NULL;
    }
    
    if(length > needLength)
    {
        UnPackData(length - needLength, needLength + start);
    }
}

void NetBase::close()
{
    if(socketFileDescriptor != -1)
    {
        if (shutdown(socketFileDescriptor, SHUT_RDWR) == -1) {
            error = (char*)"not shutdow.";
        }
        else
        {
            error = NULL;
        }
    }
}
#undef  Byte
