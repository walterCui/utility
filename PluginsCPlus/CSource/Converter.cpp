//
//  Converter.cpp
//  EPet
//
//  Created by walter on 14-10-13.
//  Copyright (c) 2014年 com.Example. All rights reserved.
//

#include "Converter.h"
#include <string.h>
#include <sys/types.h>

#define Byte unsigned char

int Converter::toBytes(Byte *bytes, int start, Byte value)
{
    bytes[start] = value;
    return 1;
}
int Converter::toBytes(Byte *bytes, int start, char value)
{
    bytes[start] = value;
    return 1;
}

int Converter::toBytes(Byte *bytes, int start, short value)
{
    Byte *ptr = bytes + start;
    HTONS(value);
    memcpy(ptr, &value, sizeof(short));
    return  sizeof(short);
}

int Converter::toBytes(Byte *bytes, int start, unsigned short value)
{
    return toBytes(bytes, start, (short)value);
}

int Converter::toBytes(Byte *bytes, int start, int value)
{
    Byte *ptr = bytes + start;
    HTONL(value);
    memcpy(ptr, &value, sizeof(int));
    return sizeof(int);
}

int Converter::toBytes(Byte *bytes, int start, long long value)
{
    Byte *ptr = bytes + start;
    HTONLL(value);
    memcpy(ptr, &value, sizeof(long long));
    return  sizeof(long long);
}


int Converter::toBytes(Byte *bytes, int start, unsigned long long value)
{
    return  toBytes(bytes, start, (long long)value);
}

int Converter::toBytes(Byte *bytes, int start, char *string)
{
    short len = strlen(string);
    start += toBytes(bytes, start, len);
    Byte *ptr = bytes + start;
    memcpy(ptr, string, len);
    return len+2;
}

int Converter::toBytes(Byte *bytes, int start, float value)
{
    Byte *ptr = (Byte*)&value;
    for(int i = 0; i < 4; i++)
        bytes[i+start] = ptr[i];
    start += 4;
    return  sizeof(float);
}
//===================//


char Converter::getChar(Byte *bytes, int &start)
{
    start++;
    return (char)bytes[start - 1];
}

short Converter::getShort(Byte *bytes, int &start)
{
    short tem = sizeof(short);
    Byte *ptr = bytes + start;
    start += tem;
    memcpy((void*)&tem,ptr, tem);
    return  ntohs(tem);
    
}

unsigned short Converter::getUShort(Byte *bytes, int &start)
{
    return  (unsigned short)getShort(bytes, start);
    
}


int Converter::getInt(Byte *bytes, int &start)
{
    int temp = 0;
    Byte *ptr = bytes + start;
    memcpy((void*)&temp, ptr, sizeof(int));
    start += sizeof(int);
    return ntohl(temp);
}


long long Converter::getInt64(Byte *bytes, int &start)
{
    long long tem = 8;
    Byte *ptr = bytes + start;
    start += tem;
    memcpy((void*)&tem,ptr, 8);
    return  ntohll(tem);
    
}

unsigned long long Converter::getUInt64(Byte *bytes, int &start)
{
    return (unsigned long long)getInt64(bytes, start);
}

char* Converter::getString(Byte *bytes, int &start)
{
    short len = getShort(bytes, start);
    char* temp = new char[len+1];
    Byte *ptr = bytes + start;
    memcpy(temp, ptr, len);
    temp[len] = 0;
    return  temp;
}

float Converter::getFloat(Byte *bytes, int &start)
{
    float temp = 0;
    Byte *ptr = (Byte*)&temp;
    for(int i = 0; i < 4; i++)
        ptr[i] = bytes[i+start];
    start += 4;
    return  temp;
}


#undef Byte
