//
//  NetDataBase.cpp
//  EPet
//
//  Created by walter on 14-10-13.
//  Copyright (c) 2014年 com.Example. All rights reserved.
//

#include "NetDataBase.h"

NetDataBase::NetDataBase()
{
    sourceType = 0;
    destType = 4;
    msgType = 0;
}

int NetDataBase::serialization(unsigned char *data)
{
    int i = Converter::toBytes(data, 0, 0); //set lenght;
    i += Converter::toBytes(data, i, 2);//seq.
    i += Converter::toBytes(data, i, NetSeesion::dialogId);
    i += Converter::toBytes(data, i, NetSeesion::uId);
    
    //
    i += Converter::toBytes(data, i, msgId);
    i += Converter::toBytes(data, i, msgType);
    i += Converter::toBytes(data, i, 111);
    i += Converter::toBytes(data, i, sourceType);
    i += Converter::toBytes(data, i, destType);
    i += Converter::toBytes(data, i, NetSeesion::playerId);
    i += Converter::toBytes(data, i, destId);
    return i;
}

int NetDataBase::deserialization(unsigned char *data, int offset)
{
    offset += 8; //ignore seq and length;
    NetSeesion::dialogId = Converter::getInt(data, offset);
    NetSeesion::uId = Converter::getUInt64(data, offset);
    NetSeesion::playerId = NetSeesion::dialogId;
    
    msgId = Converter::getShort(data, offset);
    msgType = Converter::getShort(data, offset);
    offset += 4;//ignore seq;
    sourceType = Converter::getChar(data, offset);
    destType = Converter::getChar(data, offset);
    offset += 8; //ignore sourceId and destId;
    if(msgType == 1)//response
        ReturnCode = Converter::getShort(data, offset);
    return  offset;
}