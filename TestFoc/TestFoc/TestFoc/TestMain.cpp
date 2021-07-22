
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
	glClearColor(0.0, 0.0, 0.0, 0.0);//���ñ�����ɫΪ��ɫ
}
static void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//buffer����Ϊ��ɫ��д
	glBegin(GL_TRIANGLES);//��ʼ��������
	glShadeModel(GL_SMOOTH);//����Ϊ�⻬����ģʽ
	glColor3f(1.0, 0.0, 0.0);//���õ�һ������Ϊ��ɫ
	glVertex2f(-1.0, -1.0);//���õ�һ�����������Ϊ��-1.0��-1.0��
	glColor3f(0.0, 1.0, 0.0);//���õڶ�������Ϊ��ɫ
	glVertex2f(0.0, -1.0);//���õڶ������������Ϊ��0.0��-1.0��
	glColor3f(0.0, 0.0, 1.0);//���õ���������Ϊ��ɫ
	glVertex2f(-0.5, 1.0);//���õ��������������Ϊ��-0.5��1.0��
	glEnd();//�����ν���
	glFlush();//ǿ��OpenGL����������ʱ��������
}


static void myReshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);//�����ӿ�
	glMatrixMode(GL_PROJECTION);//ָ����ǰ����ΪGL_PROJECTION
	glLoadIdentity();//����ǰ�����û�Ϊ��λ��
	if (w <= h)
		gluOrtho2D(-1.0, 1.5, -1.5, 1.5*(GLfloat)h / (GLfloat)w);//�����ά����ͶӰ���� 
	else
		gluOrtho2D(-1.0, 1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5);//����Ƕ����������������
	glMatrixMode(GL_MODELVIEW);//ָ����ǰ����ΪGL_MODELVIEW

}

static void Clark_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//buffer����Ϊ��ɫ��д
	glBegin(GL_LINE_STRIP);//��ʼ��������
	glShadeModel(GL_SMOOTH);//����Ϊ�⻬����ģʽ
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
	glEnd();//�����ν���
	glFlush();//ǿ��OpenGL����������ʱ��������
}

static void Foc_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//buffer����Ϊ��ɫ��д
	glBegin(GL_LINE_STRIP);//��ʼ��������
	glShadeModel(GL_SMOOTH);//����Ϊ�⻬����ģʽ
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
	glEnd();//�����ν���
	glFlush();//ǿ��OpenGL����������ʱ��������
}

int main(int argc, char ** argv)
{
	/*��ʼ��*/
	glutInit(&argc, argv);
	//glutInit(&argc, argv);//������ʼ��GLUT�Ⲣͬ����ϵͳ�Ի�Э��
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//����ȷ�����������ڵ���ʾģʽ�������еĲ���GLUT_SINGLE ָ�������洰�ڣ���Ҳ��ȱʡģʽ����Ӧ��ģʽΪGLUT_DOUBLE ˫���洰�ڡ�����GLUT_RGBָ����ɫRGBAģʽ����Ҳ��ȱʡģʽ����Ӧ��ģʽΪGLUT_INDEX ��ɫ����ģʽ���ڡ�
	glutInitWindowSize(600, 600);//��ʼ�����ڵĴ�С����һ������Ϊ���ڵĿ�ȣ��ڶ�������Ϊ���ڵĸ߶ȣ�������Ϊ��λ��
	glutInitWindowPosition(200, 200);// ���ó�ʼ���ڵ�λ�ã���һ������Ϊ�������Ͻ�x�����꣬�ڶ�������Ϊ�������Ͻ�y�����꣬������Ϊ��λ����Ļ�����Ͻǵ�����Ϊ��0��0�������������������ӣ����������������ӡ�
									 /*��������*/
	glutCreateWindow("Triangle");//�������㴰�ڣ����ڵ�����Ϊ�����еĲ�����
								 /*��������ʾ*/
	background();//�Լ���װ�Ļ��Ʊ���
	//glutDisplayFunc(Clark_Display);
	glutDisplayFunc(Foc_Display);
	glutMainLoop();//?glutMainLoop ����GLUT�¼�����ѭ����glutMainLoop������GLUT���������ֻ�ܵ���һ�Σ���һ�������þͲ��ٷ��أ����ҵ���ע����Ļص�������������������������ע��ص������ĺ��棬������ΪglutReshapeFunc�� glutDisplayFunc��
	return(0);
}

