//
//  CPlusCallbackproxy.h
//  EPet
//
//  Created by walter on 14-10-15.
//  Copyright (c) 2014年 com.Example. All rights reserved.
//

#ifndef __EPet__CPlusCallbackproxy__
#define __EPet__CPlusCallbackproxy__

#include <stdio.h>
template<typename Tobject, typename Tparam1, typename Tparam2>
class CPlusCallbackProxy
{
    typedef void (Tobject::*funDelegate)(Tparam1,Tparam2);
public:
    void set(Tobject *instanceValue, funDelegate funValue);
    bool Exec(Tparam1 param1, Tparam2 param2);
private:
    funDelegate fun;
    Tobject *instance;
};
#endif /* defined(__EPet__CPlusCallbackproxy__) */
