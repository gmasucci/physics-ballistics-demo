#pragma once
#include <GLTools.h>
#include <GLBatch.h>
#include <GLFrame.h>

class Target
{
public:
	Target(void)	{
		mass =	1.0; energy = 0; width = 2.5;
		acceleration[0]=0;	acceleration[1]=0;	acceleration[2]=0;
		velocity[0]=0;		velocity[1]=0;		velocity[2]=0;
		startPos[0]=0;		startPos[1]=0;		startPos[2]=0;
	}
	Target(double imass, double ienergy, double accelX, double accelY, double accelZ, double velX, double velY, double velZ, double iposx, double iposy, double iposz){
		mass			=	imass;
		energy			=	ienergy;
		acceleration[0]	=	accelX;
		acceleration[1]	=	accelY;
		acceleration[2]	=	accelZ;
		velocity[0]		=	velX;
		velocity[1]		=	velY;
		velocity[2]		=	velZ;
		startPos[0]		=	iposx;
		startPos[1]		=	iposy;
		startPos[2]		=	iposz;
		width = 2.5;
	}
	Target(double imass, double ienergy, double iaccel[], double ivel[], double ipos[]){
		mass	=	imass;
		energy	=	ienergy;
		for (int i=0; i<3; i++)
		{
			acceleration[i]	=	iaccel[i];
			velocity[i]		=	ivel[i];
			startPos[i]		=	ipos[i];
		}
		width = 2.5;

	}
	~Target(void)	{
		mass = 0 ; energy = 0; width = 0;
		delete[] acceleration; 
		delete[] velocity; 
		delete[] startPos;
	}

	//	inlines
	//	acessors
	double getMass()			{	return mass;			}
	double getEnergy()			{	return energy;			}
	double* getAcceleration()	{	return acceleration;	}
	double* getVel()			{	return velocity;		}
	double* getPos()			{	return startPos;		}
	float getWidth()			{	return width;			}
	//	mutators
	void setMass(double imass)											{	mass = imass;																}
	void setEnergy(double iEnergy)										{	energy = iEnergy;															}
	void setAcceleration(double accelX, double accelY, double accelZ)	{	acceleration[0]=accelX; acceleration[1]=accelY; acceleration[2]=accelZ;		}
	void setVelocity(double velX, double velY, double velZ)				{	velocity[0]=velX; velocity[1]=velY; velocity[2]=velZ;						}
	void setPos(double ix, double iy, double iz)						{	startPos[0]=ix; startPos[1]=iy; startPos[2]=iz;								}
	void setAcceleration();
	void setVelocity();

	//	general functions
	void render();
	void init();

	//	public data members
	GLFrame frame;

private:
	double mass;
	double energy;
	double acceleration[3];
	double velocity[3];
	double startPos[3];
	float width;
	GLBatch batch;
	
};

