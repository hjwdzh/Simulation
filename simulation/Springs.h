//
//  Springs.h
//  simulation
//
//  Created by skyer on 14-4-13.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#ifndef __simulation__Springs__
#define __simulation__Springs__

#include "Particles.h"

class Spring
{
public:
    Particle *p1, *p2;
    double r;
    void Display();
    void ForceApply(double ks, double kd);
};

class Springs
{
public:
    Springs();
    Springs(int n);
    ~Springs();
    
    void Display();
    
    void ForceApply(double ks, double kd);
    void addElement(Particle& p1, Particle& p2);
    int size() const;
    void clear();
    
    vector<Spring> vs;
};

#endif /* defined(__simulation__Springs__) */
