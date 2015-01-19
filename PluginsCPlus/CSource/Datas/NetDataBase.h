//
//  NetDataBase.h
//  EPet
//
//  Created by walter on 14-10-13.
//  Copyright (c) 2014年 com.Example. All rights reserved.
//

#ifndef __EPet__NetDataBase__
#define __EPet__NetDataBase__

#include <stdio.h>
#include "IDataWraper.h"
#include "NetSession.h"
#include "Converter.h"

class NetDataBase : public IDataWraper
{
public:
    NetDataBase();
    //序列化.
    //将数据写入到data中并返回写入的长度.
    virtual int serialization(unsigned char data[]);
    //反序列化.
    virtual int deserialization(unsigned char data[], int offset);
public:
    short ReturnCode;
protected:
    short msgId;
    short msgType;
    unsigned char sourceType;
    unsigned char destType;
    int destId;
};
#endif /* defined(__EPet__NetDataBase__) */
