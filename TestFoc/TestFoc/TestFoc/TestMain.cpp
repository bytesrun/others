
#include <glut.h>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include "pid.h"
#include "Clark.h"
#include "CPark.h"
#include "CPiAdapter.h"
#include "CInvPark.h"
#include "CSvpwm.h"
static void background(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);//设置背景颜色为黑色
}
static void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//buffer设置为颜色可写
	glBegin(GL_TRIANGLES);//开始画三角形
	glShadeModel(GL_SMOOTH);//设置为光滑明暗模式
	glColor3f(1.0, 0.0, 0.0);//设置第一个顶点为红色
	glVertex2f(-1.0, -1.0);//设置第一个顶点的坐标为（-1.0，-1.0）
	glColor3f(0.0, 1.0, 0.0);//设置第二个顶点为绿色
	glVertex2f(0.0, -1.0);//设置第二个顶点的坐标为（0.0，-1.0）
	glColor3f(0.0, 0.0, 1.0);//设置第三个顶点为蓝色
	glVertex2f(-0.5, 1.0);//设置第三个顶点的坐标为（-0.5，1.0）
	glEnd();//三角形结束
	glFlush();//强制OpenGL函数在有限时间内运行
}


static void myReshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);//设置视口
	glMatrixMode(GL_PROJECTION);//指明当前矩阵为GL_PROJECTION
	glLoadIdentity();//将当前矩阵置换为单位阵
	if (w <= h)
		gluOrtho2D(-1.0, 1.5, -1.5, 1.5*(GLfloat)h / (GLfloat)w);//定义二维正视投影矩阵 
	else
		gluOrtho2D(-1.0, 1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5);//大概是定义三个顶点的坐标
	glMatrixMode(GL_MODELVIEW);//指明当前矩阵为GL_MODELVIEW

}

static void Clark_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//buffer设置为颜色可写
	glBegin(GL_LINE_STRIP);//开始画三角形
	glShadeModel(GL_SMOOTH);//设置为光滑明暗模式
	Clark_Data test;
	float w = 0.01;
	for (int t = 0; t <= 628; ++t)
	{
		float a = sin(w*t);
		float b = sin(w*t - 6.28 / 3);
		test.TransForm(a, b);
		float x = test.getAlpha()/2;
		float y = test.getBelta()/2;
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(x, y);
		test.print();
	}
	glEnd();//三角形结束
	glFlush();//强制OpenGL函数在有限时间内运行
}

static void Foc_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//buffer设置为颜色可写
	glBegin(GL_LINE_STRIP);//开始画三角形
	glShadeModel(GL_SMOOTH);//设置为光滑明暗模式
	Clark_Data test;
	CPark park;
	CPiAdapter pid_q;
	CPiAdapter pid_d;
	CInvPark invPark;
	CSvpwm svpwm;
	float w = 6.28*5;
	float theta = 0;
	for (int t = 0; t <= 3200; ++t)
	{
		theta = w * t;
		float a = 0.8*sin(theta);
		float b = 0.8*sin(theta - 6.28 / 3);
		test.TransForm(a, b);
		park.Transform(test.getAlpha(), test.getBelta(), theta);
		pid_q.m_ActualPoint = park.getIq();
		pid_d.m_ActualPoint = park.getId();
		pid_q.PID_realize(-1.0);
		pid_d.PID_realize(0.0);
		invPark.Transform(pid_d.m_result, pid_q.m_result, theta);
		svpwm.calTcm(invPark.getAlpha(), invPark.getBelta());
		float y = 1*svpwm.m_T1/svpwm._Tpwm;
		//printf("t: %d, t1: %f, t2: %f, t3: %f\n", t, svpwm.m_T1, svpwm.m_T2, svpwm.m_T3);
		float x = (float)t*1.0/3200;
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(x, y);
		printf("t: %d, t1: %f, t2: %f, t3: %f, x: %f, y: %f\n", t, svpwm.m_T1, svpwm.m_T2, svpwm.m_T3, x, y);
		printf(" iq: %f, id: %f\n", park.getIq(), park.getId());
		//test.print();
		//if (t % 20 == 0) system("pause");
		//if (y<0) system("pause");
	}
	glEnd();//三角形结束
	glFlush();//强制OpenGL函数在有限时间内运行
}

int main(int argc, char ** argv)
{
	/*初始化*/
	glutInit(&argc, argv);
	//glutInit(&argc, argv);//用来初始化GLUT库并同窗口系统对话协商
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//用来确定所创建窗口的显示模式。本例中的参数GLUT_SINGLE 指定单缓存窗口，这也是缺省模式，对应的模式为GLUT_DOUBLE 双缓存窗口。参数GLUT_RGB指定颜色RGBA模式，这也是缺省模式，对应的模式为GLUT_INDEX 颜色索引模式窗口。
	glutInitWindowSize(600, 600);//初始化窗口的大小，第一个参数为窗口的宽度，第二个参数为窗口的高度，以像素为单位。
	glutInitWindowPosition(200, 200);// 设置初始窗口的位置，第一个参数为窗口左上角x的坐标，第二个参数为窗口左上角y的坐标，以像素为单位。屏幕的左上角的坐标为（0，0），横坐标向右逐渐增加，纵坐标向下逐渐增加。
									 /*创建窗口*/
	glutCreateWindow("Triangle");//创建顶层窗口，窗口的名字为扩号中的参数。
								 /*绘制与显示*/
	background();//自己封装的绘制背景
	//glutDisplayFunc(Clark_Display);
	glutDisplayFunc(Foc_Display);
	glutMainLoop();//?glutMainLoop 进入GLUT事件处理循环。glutMainLoop函数在GLUT程序中最多只能调用一次，它一旦被调用就不再返回，并且调用注册过的回调函数。所以这个函数必须放在注册回调函数的后面，此例中为glutReshapeFunc， glutDisplayFunc。
	return(0);
}

