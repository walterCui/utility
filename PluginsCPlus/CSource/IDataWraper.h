//
//  IDataWraper.h
//  EPet
//
//  Created by walter on 14-9-26.
//  Copyright (c) 2014年 com.Example. All rights reserved.
//

#ifndef EPet_IDataWraper_h
#define EPet_IDataWraper_h

#define Byte unsigned char

//网络数据的序列化和反序列化接口.
class IDataWraper
{
public:
    //序列化.
    //将数据写入到data中并返回写入的长度.
    virtual int serialization(Byte data[]) = 0;
    //反序列化.
    virtual int deserialization(Byte data[], int offset) = 0;
};

#undef Byte

#endif
