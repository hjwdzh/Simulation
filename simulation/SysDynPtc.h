//
//  SysDynPtc.h
//  simulation
//
//  Created by skyer on 14-4-13.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#ifndef __simulation__SysDynPtc__
#define __simulation__SysDynPtc__

#include "Springs.h"
#include "SystemPhy.h"

class SysDynPtc: public SystemPhy
{
public:
    SysDynPtc();
    ~SysDynPtc();
    
    virtual void Initialize();
    virtual void Display();
    virtual Geometric* mouseSelect(double mouseX, double mouseY);
    virtual int getDim();
    virtual double* getState();
    virtual void setState(double* state, double t);
    
    virtual double* DerivEval(double* state, double t);
    double getTime();

protected:
    virtual void clearForce();
    virtual void ForceApply();
    Springs m_springs;
    Particles m_particles;
    double time;
    double ks, kd;
};

#endif /* defined(__simulation__SysDynPtc__) */
