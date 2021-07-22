#pragma once
class CSvpwm
{
public:
	CSvpwm();
	~CSvpwm();
public:
	int calSector(float Ualpha, float Ubelta);
	void calTcm(float Ualpha, float Ubelta);
	float m_T1;
	float m_T2;
	float m_T3;
	int m_sector;
public:
	float _Tpwm;
	float _Udc;
};

