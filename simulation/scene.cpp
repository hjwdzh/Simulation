#include "main.h"
#include "ForceField.h"
#include <engine.h>

void SetParameters()
{
    ForceField::k_drag = 1.8;
    
}

// 初始化应用程序
void Initialize()
{
    
    g_sys = new SysDynPtc();
    g_sys->Initialize();
    g_camera = new Camera();
    g_engine = new MatEngine();
    
    SetParameters();
    // 设置清屏颜色
    glClearColor (0.0, 0.0, 0.0, 0.0);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    // 设置视口，投影信息
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

// 清理应用程序
void Uninitialize()
{
    // nothing
    delete g_sys;
    delete g_camera;
    delete g_engine;
}