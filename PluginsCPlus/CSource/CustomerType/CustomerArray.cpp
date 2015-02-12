//
//  CustomerArrary.cpp
//  PluginsCPlus
//
//  Created by walter on 15/1/23.
//  Copyright (c) 2015年 com.enigma. All rights reserved.
//

#include "CustomerArray.h"

template<class T>
CustomerArray<T>::CustomerArray(int capacity)
{
    count = capacity;
    t = new T[count];
}

template<class T>
CustomerArray<T>::~CustomerArray<T>()
{
    if(t != nullptr)
        delete [] t;
}

template<class T>
T CustomerArray<T>::operator[](int index)
{
    if(t > 0 && t < count)
        return t[index];
    else
    {
        T tem;
        return tem;
    }
}
