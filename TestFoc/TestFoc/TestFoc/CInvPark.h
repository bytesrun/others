#pragma once
class CInvPark
{
public:
	CInvPark();
	~CInvPark();
	void Transform(float id, float iq, float theta);
	float getAlpha();
	float getBelta();
private:
	float _uAlpha;
	float _uBelta;
};

