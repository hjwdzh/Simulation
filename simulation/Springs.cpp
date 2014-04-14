//
//  Springs.cpp
//  simulation
//
//  Created by skyer on 14-4-13.
//  Copyright (c) 2014年 skyer. All rights reserved.
//
#include "main.h"

Springs::Springs()
{}

Springs::Springs(int n)
{
    vs.resize(n);
}

Springs::~Springs()
{}

int Springs::size() const
{
    return (int)vs.size();
}

void Springs::Display()
{
    glColor3f(1.0f, 0.6f, 0.0f);
    glBegin(GL_LINES);
    for (vector<Spring>::iterator it = vs.begin();
         it != vs.end(); ++it)
        it->Display();
    glEnd();
}

void Springs::ForceApply(double ks, double kd)
{
    for (vector<Spring>::iterator it = vs.begin();
         it != vs.end(); ++it)
        it->ForceApply(ks, kd);
}

void Springs::addElement(Particle &p1, Particle &p2)
{
    Spring s;
    s.p1 = &p1;
    s.p2 = &p2;
    s.r = (p1.x - p2.x).length();
    vs.push_back(s);
}

void Springs::clear()
{
    vs.clear();
}

void Spring::ForceApply(double ks, double kd)
{
    Vector3d dx = p1->x - p2->x;
    Vector3d dv = p1->v - p2->v;
    double len = dx.length();
    Vector3d f2 = dx * ((ks * (len - r) + (dv.dotProduct(dx)) * (kd / len)) / len);
    Vector3d f1 = -f2;
    if (f1[0] != 0 || f1[1] != 0 || f1[2] != 0)
    {
        int t = 0;
        t = t + 1;
    }
    p1->ExcertForce(f1);
    p2->ExcertForce(f2);
}

void Spring::Display()
{
	glVertex3d(p1->x[0], p1->x[1], p1->x[2]);
	glVertex3d(p2->x[0], p2->x[1], p2->x[2]);
}
