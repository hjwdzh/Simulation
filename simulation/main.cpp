//
//  main.cpp
//  simulation
//
//  Created by skyer on 14-4-13.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#include "main.h"
//
//  main.c
//  simulation
//
//  Created by skyer on 14-4-13.
//  Copyright (c) 2014年 skyer. All rights reserved.
//

#define bool int

#ifndef false
#define false FALSE
#endif

#ifndef true
#define true TRUE
#endif
//=============================================================
// 函数声明
//=============================================================

void ReshapeFunc(int width, int height);            // glut窗口重置回调函数
void KeyboardFunc(unsigned char key, int x, int y);    // glut键盘回调函数
void MouseFunc(int button, int state, int x, int y);// glut鼠标按下与释放回调函数
void MotionFunc(int x, int y);                        // glut鼠标移动回调函数
void IdleFunc();                                    // glut空闲处理回调函数


void DrawTextHHL(const char* text, float x, float y);  // 在屏幕上显示文本

//=============================================================
// 全局变量
//=============================================================
const static float PI_2 = 6.2831852f;

// 窗口相关
const static int g_WindowPosX = 240;
const static int g_WindowPosY = 200;

int g_WindowWidth = 512;
int g_WindowHeight = 384;
double g_d = 1.0;
SysDynPtc* g_sys = 0;
Camera* g_camera = 0;
MatEngine* g_engine = 0;

const char* g_WindowTitle = "Simulation Demo";

// 显示模式:双缓冲，RGBA，深度缓存
const static int g_DisplayMode = (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);    // GLUT_STENCIL GLUT_ACCUM
const static float g_fov = 60.0f;
double g_top = 1.0;
double g_right = g_top * (double)g_WindowWidth / g_WindowHeight;

//=============================================================
// main 函数
//=============================================================
//void main()
int main(int argc, char** argv)
{
    // 初始化opengl, glut, glew
    glutInit(&argc, argv);
    glutInitDisplayMode(g_DisplayMode);
    
    // 创建window
    glutInitWindowPosition(g_WindowPosX, g_WindowPosY);
    glutInitWindowSize(g_WindowWidth, g_WindowHeight);
    glutCreateWindow(g_WindowTitle);
    
    // 初始化应用程序
    Initialize() ;
    
    // 设定glut回调函数
    glutDisplayFunc(DrawFunc);
    glutReshapeFunc(ReshapeFunc);
    glutKeyboardFunc(KeyboardFunc);
    glutMouseFunc(MouseFunc);
    glutMotionFunc(MotionFunc);
    glutTimerFunc(33, Animate, 1);
    glutIdleFunc(IdleFunc);
    // 进入glut事件处理循环
    glutMainLoop();
    
    // 清理应用程序
    Uninitialize();
    
    return 0;
}

// 空闲处理
void IdleFunc()
{
    // 请求重绘
    glutPostRedisplay();
}

// 响应窗口重置事件
void ReshapeFunc(int width, int height)
{
    g_WindowWidth = width;
    g_WindowHeight = height;
    
    glViewport(0, 0, g_WindowWidth, g_WindowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double x = (double)g_WindowWidth / g_WindowHeight;
    glFrustum(-x, x, -1, 1, g_d, 30);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
