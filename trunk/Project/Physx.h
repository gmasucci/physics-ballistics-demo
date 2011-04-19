#pragma once
#include "enumerations.h"
//const long double PI =  3.1415926535897932384626433832795028841968;
class Physx
{
public:
	Physx(void);
	~Physx(void);

	//	general functions
	float toRads(float theta)						{	return theta*(PI/180);	}
	float acceleration(float force, float mass)		{	return force/mass;		}
	float updateYposByGravity(float oldPosition)	{	return oldPosition + (GRAVITY/FRAMERATE);	}
	float updatePosByWind()		{/*	need this later, updates all 3 axis coordinates*/}
	inline float squared(float numToSqr)			{	return numToSqr * numToSqr;		}
	inline float cubed(float numToCube)					{	return numToCube * numToCube * numToCube;	}




protected:
	double mass;
	double angle;


};

