#include "CSvpwm.h"
#include "math.h"


CSvpwm::CSvpwm()
{
	_Tpwm = 0.000645;
	_Tpwm = 0.0002;
	//_Tpwm = 0.00645;
	_Udc = 10;
}


CSvpwm::~CSvpwm()
{
}

int CSvpwm::calSector(float Ualpha, float Ubelta)
{
	float ref1 = Ubelta;
	float ref2 = (sqrt(3)*Ualpha - Ubelta) / 2;
	float ref3 = (-sqrt(3)*Ualpha - Ubelta) / 2;
	m_sector = 0;
	if (ref1 > 0)
	{
		m_sector = 1;
	}

	if (ref2 > 0)
	{
		m_sector += 2;
	}

	if (ref3 > 0)
	{
		m_sector += 4;
	}

	return m_sector;
}

void CSvpwm::calTcm(float Ualpha, float Ubelta)
{
	calSector(Ualpha, Ubelta);
	float X = sqrt(3)*Ubelta*_Tpwm / _Udc;
	float Y = _Tpwm / _Udc * (3 / 2 * Ualpha + sqrt(3) / 2 * Ubelta);
	float Z = _Tpwm / _Udc * (-3 / 2 * Ualpha + sqrt(3) / 2 * Ubelta);

	float T1, T2;
	switch (m_sector)
	{
	case 1:
		T1 = Z;
		T2 = Y;
		break;
	case 2:
		T1 = Y;
		T2 = -X;
		break;
	case 3:
		T1 = -Z;
		T2 = X;
		break;
	case 4:
		T1 = -X;
		T2 = Z;
		break;
	case 5:
		T1 = X;
		T2 = -Y;
		break;
	case 6:
		T1 = -Y;
		T2 = -Z;
		break;
	}

	if (T1 + T2 > _Tpwm)
	{
		T1 = T1 / (T1 + T2);
		T2 = T2 / (T1 + T2);
	}
	float Ta = (_Tpwm - (T1 + T2)) / 4.0;
	float Tb = Ta + T1 / 2;
	float Tc = Tb + T2 / 2;

	switch (m_sector)
	{
	case 1:
		m_T1 = Tb;
		m_T2 = Ta;
		m_T3 = Tc;
		break;
	case 2:
		m_T1 = Ta;
		m_T2 = Tc;
		m_T3 = Tb;
		break;

	case 3:
		m_T1 = Ta;
		m_T2 = Tb;
		m_T3 = Tc;
		break;
	case 4:
		m_T1 = Tc;
		m_T2 = Tb;
		m_T3 = Ta;
		break;
	case 5:
		m_T1 = Tc;
		m_T2 = Ta;
		m_T3 = Tb;
		break;
	case 6:
		m_T1 = Tb;
		m_T2 = Tc;
		m_T3 = Ta;
		break;
	}
}