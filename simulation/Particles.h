//
//  Particles.h
//  simulation
//
//  Created by skyer on 14-4-13.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#ifndef __simulation__Particles__
#define __simulation__Particles__
#include <iostream>
#include <vector>
using namespace std;

#include "Geometric.h"
using namespace std;

class Particle : public Geometric
{
public:
    Particle()
    {}
    
    Particle(const Vector3d &_x, const Vector3d &_v, double _m)
    {
        x = _x;
        v = _v;
        mass = _m;
    }
    
    void Display();    
    void ExcertForce(const Vector3d& force);
    void ExcertForceField(Vector3d (*forcefunc)(Geometric*));
     
};

class Particles
{
public:
    Particles();
    Particles(int n);
    ~Particles();
    
    void Display();
    
    Geometric* mouseSelect(double mouseX, double mouseY);
    
    void addElement(const Vector3d &x, double _m);
    void addElement(const Vector3d &x, const Vector3d &v, double _m);
    
    void clearForce();
    void ExcertForceField(Vector3d (*forcefunc)(Geometric*));

    int size() const;
    void clear();
    
    vector<Particle> vp;
};

#endif /* defined(__simulation__Particles__) */
