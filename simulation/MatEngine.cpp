//
//  MatEngine.cpp
//  simulation
//
//  Created by skyer on 14-4-15.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#include "MatEngine.h"

MatEngine::MatEngine()
{
    ep = engOpen("");
}

MatEngine::~MatEngine()
{
    engClose(ep);
}

void MatEngine::execute(const char* command)
{
    engEvalString(ep, command);
}

void MatEngine::putVariable(const char* name, const mxArray& m)
{
    engPutVariable(ep, name, &m);
}

mxArray* MatEngine::getVariable(const char* name)
{
    return engGetVariable(ep, name);
}