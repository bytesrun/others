#include "CPark.h"
#include "math.h"


CPark::CPark()
{
}


CPark::~CPark()
{
}

void CPark::Transform(float alpha, float belta, float theta)
{
	_id = alpha * cos(theta) + belta * sin(theta);
	_iq = -alpha * sin(theta) + belta * cos(theta);
}

float CPark::getId()
{
	return _id;
}

float CPark::getIq()
{
	return _iq;
}