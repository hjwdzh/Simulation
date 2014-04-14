//
//  SysDynPtc.cpp
//  simulation
//
//  Created by skyer on 14-4-13.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#include "SysDynPtc.h"
#include "ForceField.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

SysDynPtc::SysDynPtc()
{}

SysDynPtc::~SysDynPtc()
{}

Geometric* SysDynPtc::mouseSelect(double mouseX, double mouseY)
{
    return m_particles.mouseSelect(mouseX, mouseY);
}

extern double g_top, g_right;
void SysDynPtc::Initialize()
{
    ks = 100; kd = 10;
    /* scene 3 */
    m_particles.addElement(Vector3d(-0.5,-0.5,-2), 1);
    m_particles.addElement(Vector3d(-0.5,0.5,-2), 1);
    m_particles.addElement(Vector3d(0.5,0.5,-2), 1);
    m_particles.addElement(Vector3d(0.5,-0.5,-2), 1);
    m_particles.addElement(Vector3d(-0.5,-0.5,-3), 1);
    m_particles.addElement(Vector3d(-0.5,0.5,-3), 1);
    m_particles.addElement(Vector3d(0.5,0.5,-3), 1);
    m_particles.addElement(Vector3d(0.5,-0.5,-3), 1);
    m_springs.addElement(m_particles.vp[0],m_particles.vp[1]);
    m_springs.addElement(m_particles.vp[1],m_particles.vp[2]);
    m_springs.addElement(m_particles.vp[2],m_particles.vp[3]);
    m_springs.addElement(m_particles.vp[3],m_particles.vp[0]);
    m_springs.addElement(m_particles.vp[4],m_particles.vp[5]);
    m_springs.addElement(m_particles.vp[5],m_particles.vp[6]);
    m_springs.addElement(m_particles.vp[6],m_particles.vp[7]);
    m_springs.addElement(m_particles.vp[7],m_particles.vp[4]);
    m_springs.addElement(m_particles.vp[0],m_particles.vp[4]);
    m_springs.addElement(m_particles.vp[1],m_particles.vp[5]);
    m_springs.addElement(m_particles.vp[2],m_particles.vp[6]);
    m_springs.addElement(m_particles.vp[3],m_particles.vp[7]);
    
    /* scene 2 */
/*    m_particles.addElement(Vector3d(-0.5,-0.5,-2), 1);
    m_particles.addElement(Vector3d(-0.5,0.5,-2), 1);
    m_particles.addElement(Vector3d(0.5,0.5,-2), 1);
    m_particles.addElement(Vector3d(0.5,-0.5,-2), 1);
    m_springs.addElement(m_particles.vp[0],m_particles.vp[1]);
    m_springs.addElement(m_particles.vp[1],m_particles.vp[2]);
    m_springs.addElement(m_particles.vp[2],m_particles.vp[3]);
    m_springs.addElement(m_particles.vp[3],m_particles.vp[0]);
    m_particles.vp[0].setExtForce(Vector3d(-0.3, 0.3, 0));
    m_particles.vp[1].setExtForce(Vector3d(0.3, 0.3, 0));
    m_particles.vp[2].setExtForce(Vector3d(0.3, -0.3, 0));
    m_particles.vp[3].setExtForce(Vector3d(-0.3, -0.3, 0));
*/
    /* scene 1 */
/*    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
        {
            Particle p;
            Vector3d x(0.4 * i - 0.8, 0.4 * j - 0.8, 0);
            p.x = x;
            m_particles.addElement(x, 1);
        }
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 4; ++j)
        {
            m_springs.addElement(m_particles.vp[i * 5 + j], m_particles.vp[i * 5 + j + 1]);
            m_springs.addElement(m_particles.vp[i + j * 5], m_particles.vp[i + (j + 1) * 5]);
        }
*/
}

void SysDynPtc::Display()
{
    m_particles.Display();
    m_springs.Display();
}

int SysDynPtc::getDim()
{
    return 6 * m_particles.size();
}

void SysDynPtc::clearForce()
{
    m_particles.clearForce();
}

double* SysDynPtc::getState()
{
    double *state = new double[6 * m_particles.size()];
    double* t = state;
    for (vector<Particle>::iterator it = m_particles.vp.begin();
         it != m_particles.vp.end(); ++it)
    {
        *t++ = it->x[0];
        *t++ = it->x[1];
        *t++ = it->x[2];
        *t++ = it->v[0];
        *t++ = it->v[1];
        *t++ = it->v[2];
    }
    return state;
}

void SysDynPtc::setState(double* state, double t)
{
    double* pt = state;
    for (vector<Particle>::iterator it = m_particles.vp.begin();
         it != m_particles.vp.end(); ++it)
    {
        it->x[0] = *pt++;
        it->x[1] = *pt++;
        it->x[2] = *pt++;
        it->v[0] = *pt++;
        it->v[1] = *pt++;
        it->v[2] = *pt++;
    }
    delete[] state;
    time = t;
}

double* SysDynPtc::DerivEval(double* state, double t)
{
    clearForce();
    ForceApply();
    double *delta = new double[6 * m_particles.size()];
    double *st = delta;
    for (vector<Particle>::iterator it = m_particles.vp.begin();
         it != m_particles.vp.end(); ++it)
    {
        *st++ = it->v[0];
        *st++ = it->v[1];
        *st++ = it->v[2];
        *st++ = it->f[0] / it->mass;
        *st++ = it->f[1] / it->mass;
        *st++ = it->f[2] / it->mass;
    }
    return delta;
}

void SysDynPtc::ForceApply()
{
//    m_particles.ExcertForceField(ForceField::gravity);
    m_particles.ExcertForceField(ForceField::viscous);
    m_springs.ForceApply(ks, kd);
}

double SysDynPtc::getTime()
{
    return time;
}
