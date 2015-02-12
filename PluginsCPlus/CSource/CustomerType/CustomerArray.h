//
//  CustomerArrary.h
//  PluginsCPlus
//
//  Created by walter on 15/1/23.
//  Copyright (c) 2015年 com.enigma. All rights reserved.
//

#ifndef __PluginsCPlus__CustomerArrary__
#define __PluginsCPlus__CustomerArrary__

#include <stdio.h>
template<class T>
class CustomerArray
{
public:
    int count;
    
public:
    CustomerArray(int capacity);
    ~CustomerArray();
    T operator[](int index);
    
private:
    T *t;
};

#endif /* defined(__PluginsCPlus__CustomerArrary__) */
