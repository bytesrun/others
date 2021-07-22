#include "Clark.h"
#include "stdio.h"
void Clark_Data::setCurrent(float a, float b)
{
	ia = a;
	ib = b;
}

void Clark_Data::TransForm(float a, float b)
{
	setCurrent(a, b);
	alpha = ia;
	belta = (ia + 2*ib) / SQRT3;
	//belta = sqrt(ib*ib - ia * ia) / SQRT3;
}

float Clark_Data::getAlpha()
{
	return alpha;
}

float Clark_Data::getBelta()
{
	return belta;
}

void Clark_Data::print()
{
	printf("ia: %f, ib: %f\n", ia, ib);
	printf("alpha: %f, belta: %f\n\n", alpha, belta);
}