//
//  Geometric.cpp
//  simulation
//
//  Created by skyer on 14-4-14.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#include "Geometric.h"

Geometric::Geometric()
: selected(false)
{}

void Geometric::setExtForce(const Vector3d &ext)
{
    extForce = ext;
}

void Geometric::clearForce()
{
    f = extForce + userForce;
}

void Geometric::setSelected(bool _sel)
{
    selected = _sel;
}

void Geometric::setUserForce(const Vector3d& v)
{
    userForce = v;
}

