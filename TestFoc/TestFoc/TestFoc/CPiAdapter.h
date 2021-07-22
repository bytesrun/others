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
	float m_SetPoint; 		//�����趨ֵ
	float m_ActualPoint; 		//����ʵ��ֵ
	float m_err; 				//����ƫ��ֵ
	float m_err_last; 		//������һ��ƫ��ֵ
	float m_Kp, m_Ki, m_Kd; 		//������������֡�΢��ϵ��
	float m_result; 			//�����ѹֵ������ִ�����ı�����
	float m_integral;		    //�������ֵ
	float m_max;
	float m_min;
};



