#include "CPiAdapter.h"
#include "stdio.h"
#include "stdlib.h"


CPiAdapter::CPiAdapter()
{
	PID_init();
}


CPiAdapter::~CPiAdapter()
{
}

void CPiAdapter::PID_init() {
	printf("PID_init begin \n");
	m_SetPoint = 0.0;
	m_ActualPoint = 0.0;
	m_err = 0.0;
	m_err_last = 0.0;
	m_result = 0.0;
	m_integral = 0.0;
	m_Kp = 0.2;				
	m_Ki = 0.015;			
	//m_Kd = 0.2;				
	m_Kd = 0.0;
	m_max = 1;
	m_min = -1;
	printf("PID_init end \n");
}

float CPiAdapter::PID_realize(float setPoint) {
	m_SetPoint = setPoint;
	m_err = m_SetPoint - m_ActualPoint;	
	m_err_last = m_err;					
	if (m_result > m_max)
	{
		if (m_err <= 0)
		{
			m_integral += m_err;
		}
	}
	else if (m_result < m_min)
	{
		if (m_err >= 0)
		{
			m_integral += m_err;
		}
	}
	else
	{
		m_integral += m_err;
	}
	m_result = m_Kp * m_err + m_Ki * m_integral + m_Kd * (m_err - m_err_last);
	return m_ActualPoint;					//返回
}

float CPiAdapter::PID_realize2(float setPoint) {
	m_SetPoint = setPoint;						//设定值
	m_err = m_SetPoint - m_ActualPoint;	//设定值-实际值
	m_integral += m_err;					//积分值，偏差累加
	m_result = m_Kp * m_err + m_Ki * m_integral + m_Kd * (m_err - m_err_last);
	//pid.voltage = pid.Kp*pid.err + pid.Ki*pid.integral + pid.Kd*(pid.err - pid.err_last);
	m_err_last = m_err;					//上一个偏差值
										//m_ActualPoint = m_result*1.0;		//算出实际值
	if (m_result > 1 || m_result<-1)
	{
		//printf("m_result is %f\n", m_result);
		m_result = m_result > 1 ? 1 : -1;
		//system("pause");
	}

	return m_ActualPoint;					//返回
}
