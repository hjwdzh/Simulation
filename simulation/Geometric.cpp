//
//  Geometric.cpp
//  simulation
//
//  Created by skyer on 14-4-14.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#include "Geometric.h"

Geometric::Geometric()
: selected(false), nailed(false), kr(1)
{}

Geometric::~Geometric()
{}

void Geometric::setExtForce(const Vector3d &ext)
{
    extForce = ext;
}

void Geometric::clearForce()
{
    if (nailed)
        f = Vector3d();
    else
        f = extForce + userForce;
}

void Geometric::setSelected(bool _sel)
{
    selected = _sel;
}

void Geometric::setNailed()
{
    nailed = !nailed;
    if (nailed)
    {
        v = Vector3d();
    }
}

void Geometric::setUserForce(const Vector3d& v)
{
    userForce = v;
}

void Geometric::setKr(double _kr)
{
    kr = _kr;
}

