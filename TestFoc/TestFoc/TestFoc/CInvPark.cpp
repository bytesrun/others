#include "CInvPark.h"
#include "math.h"


CInvPark::CInvPark()
{
}


CInvPark::~CInvPark()
{
}

void CInvPark::Transform(float id, float iq, float theta)
{
	_uAlpha = id * cos(theta) - iq * sin(theta);
	_uBelta = id * sin(theta) + iq * cos(theta);
}

float CInvPark::getAlpha()
{
	return _uAlpha;
}

float CInvPark::getBelta()
{
	return _uBelta;
}