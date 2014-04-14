#include "main.h"

// 描绘函数
void DrawFunc()
{
    // 清屏
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    g_camera->Render();
    g_sys->Display();
    glPopMatrix();
    
    // 显示文本信息
    float x = 10.0f;
    float y = 20.0f;
    
    DrawTextHHL("Author: hjwdzh@gmail.com", x, y);
    
    // 交换显示缓冲区
    glutSwapBuffers() ;
}

// 在屏幕上显示文本，x 和 y 为屏幕坐标
void DrawTextHHL(const char* text, float x, float y)
{
    const char* c = text;
    // 检查OpenGL状态
    int isDepthOpen = 0;
    int isStencilOpen = 0;
    int isLightOpen = 0;
    int isFogOpen = 0;
    
    if(glIsEnabled(GL_DEPTH_TEST))
    {
        isDepthOpen = 1;
        glDisable(GL_DEPTH_TEST);
    }
    if(glIsEnabled(GL_STENCIL_TEST))
    {
        isStencilOpen = 1;
        glDisable(GL_STENCIL_TEST);
    }
    if(glIsEnabled(GL_LIGHTING))
    {
        isLightOpen = 1;
        glDisable(GL_LIGHTING);
    }
    if(glIsEnabled(GL_FOG))
    {
        isFogOpen = 1;
        glDisable(GL_FOG);
    }
    
    
    
    // 设置字体颜色
    glColor3f(1.0, 1.0, 0.0);
    
    /*
     * 设置正投影
     */
    
    glMatrixMode(GL_PROJECTION);
    
    // 保存当前投影矩阵
    glPushMatrix();
    
    glLoadIdentity();
    gluOrtho2D( 0, g_WindowWidth, 0, g_WindowHeight );
    
    // 反转Y轴（朝下为正方向）(与窗口坐标一致)
    glScalef(1, -1, 1);
    // 将原点移动到屏幕左上方(与窗口坐标一致)
    glTranslatef(0, -g_WindowHeight, 0);
    glMatrixMode(GL_MODELVIEW);
    
    // 保存当前模型视图矩阵
    glPushMatrix();
    glLoadIdentity();
    
    // 设置文字位置
    glRasterPos2f( x, y );
    
    // 依次描绘所有字符(使用显示列表)
    for( ; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    
    // 恢复之前保存的模型视图矩阵
    glPopMatrix();
    
    glMatrixMode(GL_PROJECTION);
    
    // 恢复之前保存的投影矩阵
    glPopMatrix();
    
    // 返回模型视图矩阵状态
    glMatrixMode(GL_MODELVIEW);
    
    // 恢复OpenGL状态
    if(isDepthOpen)
    {
        glEnable(GL_DEPTH_TEST);
    }
    if(isStencilOpen)
    {
        glEnable(GL_STENCIL_TEST);
    }
    if(isLightOpen)
    {
        glEnable(GL_LIGHTING);
    }
    if(isFogOpen)
    {
        glEnable(GL_FOG);
    }
}
