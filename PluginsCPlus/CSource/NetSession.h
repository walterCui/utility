//
//  NetSession.h
//  EPet
//
//  Created by walter on 14-10-13.
//  Copyright (c) 2014年 com.Example. All rights reserved.
//

#ifndef __EPet__NetSession__
#define __EPet__NetSession__

#include <stdio.h>
#include "NetBase.h"

class NetSeesion
{
    friend class NetDataBase;
public:
    static int GetDialogId();
    static unsigned long long GetUID();
    static void reset();
private:
    static int playerId;
    static int dialogId;
    static unsigned long long uId;
    
};

#endif /* defined(__EPet__NetSession__) */
