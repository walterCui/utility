//
//  NetBase.h
//  EPet
//
//  Created by walter on 14-9-26.
//  Copyright (c) 2014年 com.Example. All rights reserved.
//

#ifndef __EPet__NetBase__
#define __EPet__NetBase__

#include <stdio.h>
#include "IDataWraper.h"
#include <mutex>
#include <queue>
#include <sys/time.h>
#include <sys/select.h>

#define BUFFMAXSIZE 2048
#define Byte unsigned char

typedef void (*handleDelegate) (short code, Byte *data);

class NetBase
{
public:
    
    NetBase();
    NetBase(int sockedHandle);
    ~NetBase();
    
    char* getError();
    bool send(IDataWraper *data);
    //virtual void update();
    void update();
    
    void close();
    
protected:
    virtual void HandleData(Byte *data) = 0;
private:
    void init();
    void UnPackData(int length, int start);
    
protected:
    int socketFileDescriptor;
    char* error;
    
    std::mutex mtx;
    std::queue<IDataWraper*> *writeBuff;
    std::queue<IDataWraper*> *swapeBuff;
    std::queue<Byte*> *readBuff;
    
private:
    Byte data[BUFFMAXSIZE]; //用于序列化的buff.
    int dataSize;//序列化后的数据长度.
    IDataWraper *dateWraper;//临时数据.
    int wtRdSize;//用与记录读写socket时的数据长度.
    struct timeval timeout;
    fd_set fdset;
    
    //用于缓存都到的数据是用到的.
    struct ByteArray_t
    {
        Byte * data;
        int index;
        int dataLength;
    } readDataTemp;
    
//    inline void pushReadData()
//    {
//        readBuff->push(readDataTemp.data);
//        readDataTemp.data = NULL;
//
//    }
};
#undef Byte

#endif /* defined(__EPet__NetBase__) */
