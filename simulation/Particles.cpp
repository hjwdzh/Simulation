//
//  Particles.cpp
//  simulation
//
//  Created by skyer on 14-4-13.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#include "main.h"
#include "Particles.h"
#include "vmath.h"

Particles::Particles()
{}

Particles::Particles(int n)
{
    vp.resize(n);
}

Particles::~Particles()
{}

void Particles::Display()
{
    for (vector<Particle>::iterator it = vp.begin();
         it != vp.end(); ++it)
    {
        it->Display();
    }
}

int Particles::size() const
{
    return (int)vp.size();
}

void Particles::addElement(const Vector3d &x, double _m)
{
    vp.push_back(Particle(x, Vector3d(), _m));
}

void Particles::addElement(const Vector3d &x, const Vector3d &v, double _m)
{
    vp.push_back(Particle(x, v, _m));
}

void Particles::ExcertForceField(Vector3d (*forcefunc)(Geometric*))
{
    for (vector<Particle>::iterator it = vp.begin();
         it != vp.end(); ++it)
        it->ExcertForceField(forcefunc);
}

void Particles::clearForce()
{
    for (vector<Particle>::iterator it = vp.begin();
         it != vp.end(); ++it)
        it->clearForce();
}

Geometric* Particles::mouseSelect(double mouseX, double mouseY)
{
    double zbuffer = 1e30;
    Geometric* res = 0;
    for (vector<Particle>::iterator it = vp.begin();
         it != vp.end(); ++it)
    {
        Vector4d v(it->x[0], it->x[1], it->x[2], 1);
        v = g_camera->lookat * v;
        v = v / v[3];
        double dx = (v[0] / v[2] * (-g_d) - mouseX) / g_right * g_WindowWidth * 0.5;
        double dy = (v[1] / v[2] * (-g_d) - mouseY) / g_top * g_WindowHeight * 0.5;
        double dis = sqrt(dx * dx + dy * dy);
        if (dis < 10)
        {
            if (v[2] < zbuffer)
            {
                zbuffer = v[2];
                res = &(*it);
            }
        }
    }
    if (res)
        res->setSelected(true);
    return res;
}

void Particle::ExcertForce(const Vector3d &force)
{
    if (force[0] != 0 || force[1] != 0 || force[2] != 0)
    {
        int t = 0;
        t = t + 1;
    }
    f += force;
}

void Particle::ExcertForceField(Vector3d (*forcefunc)(Geometric*))
{
    f += forcefunc(this);
    if (f[0] != 0 || f[1] != 0 || f[2] != 0)
    {
        int t = 0;
        t = t + 1;
    }
}

void Particle::Display()
{
    if (selected)
        glColor3f(1.0f, 0.0f, 1.0f);
    else
        glColor3f(0.0, 1.0f, 0.0f);
    glPushMatrix();
    glTranslated(x[0], x[1], x[2]);
    glutSolidSphere(0.03f, 15, 15);
    if (extForce.length() > 0)
    {
        glColor3f(1.0f, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex3d(0, 0, 0);
        glVertex3d(extForce[0], extForce[1], extForce[2]);
        glEnd();
        glTranslated(extForce[0], extForce[1], extForce[2]);
        glutSolidSphere(0.01f, 15, 15);
        glTranslated(-extForce[0], -extForce[1], -extForce[2]);
    }
    if (userForce.length() > 0)
    {
        glColor3f(1.0f, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex3d(0, 0, 0);
        glVertex3d(userForce[0], userForce[1], userForce[2]);
        glEnd();
        glTranslated(userForce[0], userForce[1], userForce[2]);
        glutSolidSphere(0.01f, 15, 15);
    }
    glPopMatrix();
}

