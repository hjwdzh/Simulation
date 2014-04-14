//
//  Geometric.h
//  simulation
//
//  Created by skyer on 14-4-14.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#ifndef __simulation__Geometric__
#define __simulation__Geometric__

#include <iostream>
#include "vmath.h"

class Geometric
{
public:
    Geometric();

    virtual void setSelected(bool selected);
    virtual void setExtForce(const Vector3d& ext);
    virtual void clearForce();
    virtual void setUserForce(const Vector3d& v);
    

    
    double mass;
    bool selected;
    Vector3d x, v, f, extForce, userForce;

    virtual void ExcertForce(const Vector3d& force) = 0;
    void ExcertForceField(Vector3d (*forcefunc)(Geometric*));
};

#endif /* defined(__simulation__Geometric__) */
