
#include <glut.h>
using namespace std;
/*
λ����pid
*/
#include <stdio.h>
#include <stdlib.h>
//#include <ioctl.h>

struct _pid {
	float SetSpeed; 		//�����趨ֵ
	float ActualSpeed; 		//����ʵ��ֵ
	float err; 				//����ƫ��ֵ
	float err_last; 		//������һ��ƫ��ֵ
	float Kp, Ki, Kd; 		//������������֡�΢��ϵ��
	float voltage; 			//�����ѹֵ������ִ�����ı�����
	float integral;		    //�������ֵ
}pid;

//��Ŀ�л�ȡ���Ĳ���
void PID_init() {
	printf("PID_init begin \n");
	pid.SetSpeed = 0.0;
	pid.ActualSpeed = 0.0;
	pid.err = 0.0;
	pid.err_last = 0.0;
	pid.voltage = 0.0;
	pid.integral = 0.0;
	pid.Kp = 0.2;				//�Լ��趨
	pid.Ki = 0.015;			//�Լ��趨
	pid.Kd = 0.2;				//�Լ��趨
	pid.Kd = 0.0;
	printf("PID_init end \n");
}

float PID_realize(float speed) {
	pid.SetSpeed = speed;						//�趨ֵ
	pid.err = pid.SetSpeed - pid.ActualSpeed;	//�趨ֵ-ʵ��ֵ
	pid.integral += pid.err;					//����ֵ��ƫ���ۼ�
	pid.voltage = pid.Kp*pid.err + pid.Ki*pid.integral + pid.Kd*(pid.err - pid.err_last);
	//pid.voltage = pid.Kp*pid.err + pid.Ki*pid.integral + pid.Kd*(pid.err - pid.err_last);
	pid.err_last = pid.err;					//��һ��ƫ��ֵ
	pid.ActualSpeed = pid.voltage*1.0;		//���ʵ��ֵ
	return pid.ActualSpeed;					//����
}
//#include "windows.h"
int main4(int argc, char ** argv) {
	printf("System begin \n");
	PID_init();
	int count = 0;
	while (count<1000)
	{
		float speed = PID_realize(200.0);
		printf("%f\n", speed);
		count++;
		if (count % 20 == 0) system("pause");
	}
	system("pause");
	return 0;
}

void PID_Display() {	
	glClear(GL_COLOR_BUFFER_BIT);//buffer����Ϊ��ɫ��д
	
	//glShadeModel(GL_SMOOTH);//����Ϊ�⻬����ģʽ	
glBegin(GL_LINE_STRIP);//��ʼ��������
	PID_init();
	int count = 0;
	double dw = 1.9 / 100.0;
	double dh = 1.8 / 400.0;
	glColor3f(1.0, 1.0, 0.0);//���õ�һ������Ϊ��ɫ
	glVertex2f(- 0.9, -0.8);
	while (count<100)
	{
		
		float speed = PID_realize(200.0);
		printf("%f\n", speed);
		glColor3f(1.0, 1.0, 0.0);//���õ�һ������Ϊ��ɫ
		glVertex2f(dw*count-0.9, dh*speed-0.8);//���õ�һ�����������Ϊ��-1.0��-1.0��
		count++;
		
	}
	glEnd();//�����ν���
	
	glFlush();//ǿ��OpenGL����������ʱ��������
}

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

static void myDisplay2()
{
	glClear(GL_COLOR_BUFFER_BIT);//buffer����Ϊ��ɫ��д
	glBegin(GL_TRIANGLES);//��ʼ��������
	glShadeModel(GL_SMOOTH);//����Ϊ�⻬����ģʽ
	glColor3f(1.0, 0.0, 0.0);//���õ�һ������Ϊ��ɫ
	glVertex2f(0.0, -1.0);//���õ�һ�����������Ϊ��-1.0��-1.0��
	glColor3f(0.0, 1.0, 0.0);//���õڶ�������Ϊ��ɫ
	glVertex2f(1.0, -1.0);//���õڶ������������Ϊ��0.0��-1.0��
	glColor3f(0.0, 0.0, 1.0);//���õ���������Ϊ��ɫ
	glVertex2f(0.5, 1.0);//���õ��������������Ϊ��-0.5��1.0��
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

int main(int argc, char ** argv)
{
	/*��ʼ��*/
	glutInit(&argc, argv);
	//glutInit(&argc, argv);//������ʼ��GLUT�Ⲣͬ����ϵͳ�Ի�Э��
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//����ȷ�����������ڵ���ʾģʽ�������еĲ���GLUT_SINGLE ָ�������洰�ڣ���Ҳ��ȱʡģʽ����Ӧ��ģʽΪGLUT_DOUBLE ˫���洰�ڡ�����GLUT_RGBָ����ɫRGBAģʽ����Ҳ��ȱʡģʽ����Ӧ��ģʽΪGLUT_INDEX ��ɫ����ģʽ���ڡ�
	glutInitWindowSize(800, 400);//��ʼ�����ڵĴ�С����һ������Ϊ���ڵĿ�ȣ��ڶ�������Ϊ���ڵĸ߶ȣ�������Ϊ��λ��
	glutInitWindowPosition(200, 200);// ���ó�ʼ���ڵ�λ�ã���һ������Ϊ�������Ͻ�x�����꣬�ڶ�������Ϊ�������Ͻ�y�����꣬������Ϊ��λ����Ļ�����Ͻǵ�����Ϊ��0��0�������������������ӣ����������������ӡ�
									 /*��������*/
	glutCreateWindow("Triangle");//�������㴰�ڣ����ڵ�����Ϊ�����еĲ�����
								 /*��������ʾ*/
	background();//�Լ���װ�Ļ��Ʊ���
	//glutReshapeFunc(myReshape);//ע�ᵱǰ���ڵ���״�仯�ص����������ı䴰�ڴ�Сʱ���ô��ڵ���״�ı�ص������������á��ڴ����о���myReshapeָ����״�仯������
	//glutDisplayFunc(myDisplay);// ע�ᵱǰ���ڵ���ʾ�ص���������һ�����ڵ�ͼ�����Ҫ���»���ʱ��GLUT�����øô��ڵĵ���ʾ�ص��������ڴ����е�mydisplay������ʾ�ص���������ʾ�ص����������κβ���������������ͼ���Ļ��ơ����ǵĴ󲿷ֹ�������������������С�
	glutDisplayFunc(PID_Display);
	glutMainLoop();//?glutMainLoop ����GLUT�¼�����ѭ����glutMainLoop������GLUT���������ֻ�ܵ���һ�Σ���һ�������þͲ��ٷ��أ����ҵ���ע����Ļص�������������������������ע��ص������ĺ��棬������ΪglutReshapeFunc�� glutDisplayFunc��
	return(0);
}

