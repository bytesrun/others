#pragma once
class CPark
{
public:
	CPark();
	~CPark();
	void Transform(float alpha, float belta, float theta);
	float getId();
	float getIq();
private:
	float _id;
	float _iq;
};

