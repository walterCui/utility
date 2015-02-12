//
//  Converter.h
//  EPet
//
//  Created by walter on 14-10-13.
//  Copyright (c) 2014年 com.Example. All rights reserved.
//

#ifndef __EPet__Converter__
#define __EPet__Converter__

#include <stdio.h>
#define Byte unsigned char

class Converter
{
public:
    static int toBytes(Byte *bytes, int start, Byte value);
    static int toBytes(Byte *bytes, int start, char value);
    static int toBytes(Byte *bytes, int start, short value);
    static int toBytes(Byte *bytes, int start, unsigned short value);
    static int toBytes(Byte *bytes, int start, int value);
    static int toBytes(Byte *bytes, int start, long long value);
    static int toBytes(Byte *bytes, int start, unsigned long long value);
    static int toBytes(Byte *bytes, int start, char *string);
    static int toBytes(Byte *bytes, int start, float value);
    static int toBytes(Byte *bytes, int start, Byte *value, int len);
    
    static char getChar(Byte *bytes, int &start);
    static short getShort(Byte *bytes, int &start);
    static unsigned short getUShort(Byte *bytes, int &start);
    static int getInt(Byte *bytes, int &start);
    static long long getInt64(Byte *bytes, int &start);
    static unsigned long long getUInt64(Byte *bytes, int &start);
    static char* getString(Byte *bytes, int &start);
    static float getFloat(Byte *bytes, int &start);
    static Byte* getByteArray(Byte *bytes, int &start);
};
#undef Byte

#endif /* defined(__EPet__Converter__) */
