//
//  CPlusCallbackproxy.cpp
//  EPet
//
//  Created by walter on 14-10-15.
//  Copyright (c) 2014年 com.Example. All rights reserved.
//

#include "CPlusCallbackProxy.h"
template<typename Tobject, typename Tparam1, typename Tparam2>
void CPlusCallbackProxy<Tobject, Tparam1, Tparam2>::set(Tobject *instanceValue, funDelegate funValue)
{
    instance = instanceValue;
    fun = funValue;
}

template<typename Tobject, typename Tparam1, typename Tparam2>
bool CPlusCallbackProxy<Tobject, Tparam1, Tparam2>::Exec(Tparam1 param1, Tparam2 param2)
{
    if(instance == NULL || fun == NULL)
        return false;

    instance->*fun(param1,param2);
    return true;
}