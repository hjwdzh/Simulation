//
//  MatEngine.h
//  simulation
//
//  Created by skyer on 14-4-15.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#ifndef __simulation__MatEngine__
#define __simulation__MatEngine__

#include <iostream>
#include <engine.h>

class MatEngine
{
public:
    MatEngine();
    ~MatEngine();
    
    void execute(const char* command);
    void putVariable(const char* name, const mxArray& m);
    mxArray* getVariable(const char* name);
    
private:
    Engine *ep;
};

#endif /* defined(__simulation__MatEngine__) */
