//
//  ForceField.h
//  simulation
//
//  Created by skyer on 14-4-13.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#ifndef __simulation__ForceField__
#define __simulation__ForceField__

#include <iostream>

#include "Particles.h"

class ForceField
{
public:
    static Vector3d gravity(Geometric* p);
    static Vector3d viscous(Geometric* p);
    static double k_drag;
};

#endif /* defined(__simulation__ForceField__) */
