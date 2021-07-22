#pragma once
#include "math.h"
#define SQRT3 (sqrt(3))
class Clark_Data 
{
public:
	void setCurrent(float a, float b);
	void TransForm(float a, float b);
	float getAlpha();
	float getBelta();
	void print();
private:
	float ia;
	float ib;
	float ic;

	float alpha;
	float belta;
};