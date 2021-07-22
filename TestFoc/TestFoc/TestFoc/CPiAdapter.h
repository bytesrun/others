#pragma once
class CPiAdapter
{
public:
	CPiAdapter();
	~CPiAdapter();
	void PID_init();
	float PID_realize(float setPoint);
	float PID_realize2(float setPoint);
public:
	float m_SetPoint; 		//定义设定值
	float m_ActualPoint; 		//定义实际值
	float m_err; 				//定义偏差值
	float m_err_last; 		//定义上一个偏差值
	float m_Kp, m_Ki, m_Kd; 		//定义比例、积分、微分系数
	float m_result; 			//定义电压值（控制执行器的变量）
	float m_integral;		    //定义积分值
	float m_max;
	float m_min;
};



