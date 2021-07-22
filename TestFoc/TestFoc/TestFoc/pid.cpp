
#include <glut.h>
using namespace std;
/*
位置型pid
*/
#include <stdio.h>
#include <stdlib.h>

struct _pid {
	float SetSpeed; 		//定义设定值
	float ActualSpeed; 		//定义实际值
	float err; 				//定义偏差值
	float err_last; 		//定义上一个偏差值
	float Kp, Ki, Kd; 		//定义比例、积分、微分系数
	float voltage; 			//定义电压值（控制执行器的变量）
	float integral;		    //定义积分值
}pid;

//项目中获取到的参数
void PID_init() {
	printf("PID_init begin \n");
	pid.SetSpeed = 0.0;
	pid.ActualSpeed = 0.0;
	pid.err = 0.0;
	pid.err_last = 0.0;
	pid.voltage = 0.0;
	pid.integral = 0.0;
	pid.Kp = 0.2;				//自己设定
	pid.Ki = 0.015;			//自己设定
	pid.Kd = 0.2;				//自己设定
	pid.Kd = 0.0;
	printf("PID_init end \n");
}

float PID_realize(float speed) {
	pid.SetSpeed = speed;						//设定值
	pid.err = pid.SetSpeed - pid.ActualSpeed;	//设定值-实际值
	pid.integral += pid.err;					//积分值，偏差累加
	pid.voltage = pid.Kp*pid.err + pid.Ki*pid.integral + pid.Kd*(pid.err - pid.err_last);
	//pid.voltage = pid.Kp*pid.err + pid.Ki*pid.integral + pid.Kd*(pid.err - pid.err_last);
	pid.err_last = pid.err;					//上一个偏差值
	pid.ActualSpeed = pid.voltage*1.0;		//算出实际值
	return pid.ActualSpeed;					//返回
}
//#include "windows.h"
//int main4(int argc, char ** argv) {
//	printf("System begin \n");
//	PID_init();
//	int count = 0;
//	while (count<1000)
//	{
//		float speed = PID_realize(200.0);
//		printf("%f\n", speed);
//		count++;
//		if (count % 20 == 0) system("pause");
//	}
//	system("pause");
//	return 0;
//}

void PID_Display() {
	glClear(GL_COLOR_BUFFER_BIT);//buffer设置为颜色可写

								 //glShadeModel(GL_SMOOTH);//设置为光滑明暗模式	
	glBegin(GL_LINE_STRIP);//开始画三角形
	PID_init();
	int count = 0;
	double dw = 1.9 / 100.0;
	double dh = 1.8 / 400.0;
	glColor3f(1.0, 1.0, 0.0);//设置第一个顶点为红色
	glVertex2f(-0.9, -0.8);
	while (count<100)
	{

		float speed = PID_realize(200.0);
		printf("%f\n", speed);
		glColor3f(1.0, 1.0, 0.0);//设置第一个顶点为红色
		glVertex2f(dw*count - 0.9, dh*speed - 0.8);//设置第一个顶点的坐标为（-1.0，-1.0）
		count++;

	}
	glEnd();//三角形结束

	glFlush();//强制OpenGL函数在有限时间内运行
}









