//
//  Plane.cpp
//  simulation
//
//  Created by skyer on 14-4-14.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#include "Plane.h"
#include "Particle.h"
#include "main.h"
Plane::Plane()
    : N(0, 1, 0)
{}

Plane::Plane(const Vector3d& _P, const Vector3d& _N)
    : P(_P), N(_N)
{}

Plane::Plane(const Vector3d& _P, const Vector3d& _N, double _kr)
: P(_P), N(_N)
{
    kr = _kr;
}

bool Plane::collid_detection(Geometric* object)
{
    Particle* ptc = dynamic_cast<Particle*>(object);
    if (ptc)
    {
        double dis = (ptc->x - P).dotProduct(N);
        double collid = N.dotProduct(ptc->v) / ptc->v.length();
        if (dis < EPSILON && collid < -EPSILON)
        {
            Vector3d vn = N * N.dotProduct(ptc->v);
            Vector3d vt = ptc->v - vn;
            ptc->v = vt - vn * (kr * ptc->kr);
            ptc->x = ptc->x - N * dis;
        }
    }
    return false;
}

bool Plane::contact_detection(Geometric* object)
{
    Particle* ptc = dynamic_cast<Particle*>(object);
    if (ptc)
    {
        double dis = (ptc->x - P).dotProduct(N);
        double collid = N.dotProduct(ptc->v);
        if (dis < EPSILON && abs(collid) < CONTACT_THRESHOLD)
        {
            ptc->x -= N * dis;
            ptc->v -= N * collid;
            double fn = N.dotProduct(ptc->f);
            if (fn < 0)
                object->ExcertForce(N * -fn);
        }
    }
    return false;
}

void Plane::Display()
{
    Vector3d x(0.3, 1.4, 5.3);
    Vector3d y = x.crossProduct(N) * 10000;
    x = y.crossProduct(N);
    glColor3f(0.0f, 0.5f, 0.2f);
    glBegin(GL_QUADS);
        glVertex3d(P[0] + x[0] + y[0], P[1] + x[1] + y[1], P[2] + x[2] + y[2]);
        glVertex3d(P[0] + x[0] - y[0], P[1] + x[1] - y[1], P[2] + x[2] - y[2]);
        glVertex3d(P[0] - x[0] - y[0], P[1] - x[1] - y[1], P[2] - x[2] - y[2]);
        glVertex3d(P[0] - x[0] + y[0], P[1] - x[1] + y[1], P[2] - x[2] + y[2]);
    glEnd();
}