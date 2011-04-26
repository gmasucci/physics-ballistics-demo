#pragma once
#include "enumerations.h"
#include <cmath>
#include <GLTools.h>
#include <GLBatch.h>
#include <GLFrame.h>
#define FREEGLUT_STATIC
#include <GL\freeglut.h>
#include <iostream>

using namespace std;



//const long double PI =  3.1415926535897932384626433832795028841968; 
/*
Ballistic Coefficient = SD  =  M
						---	  ---
						 i	   i.d.d
						 
SD = sectional density = mass of bullet divided by its caliber in m squared or inches squared
ie  mass of bullet in pounds or kilograms divided by its caliber squared in inches or meters; units are lb/in2 or kg/m2

i = form factor, i = CB/CG; (CG~ 0.5191)
CB = drag coefficient of the bullet
CG = drag coefficient of the G1 model bullet
M = mass of object (lb or kg)
d = diameter of object  (in or m)

*/

class Projectile
{
public:
	Projectile(float ix, float iy, float iz);
	~Projectile(void);


	class Velocity
	{
	public:
		//Velocity()	{};
		Velocity(double hVel = 0, double vVel=0, double Zvel=0)	{	xVel = hVel; yVel = vVel; zVel = Zvel;	}
		~Velocity()	{};
		double xVel;
		double yVel;
		double zVel;
		
		void calcVelocities(double angle, double speed)	{	xVel = speed * cos(angle*180/PI);	yVel = speed * sin(angle*180/PI); 	}
		double calcAvgVel(double startVel, double finalVel, double time)	{	return (finalVel - startVel)/time;	}
		double finalVel(float startVel, double accel, double time)			{	return startVel + accel * time;		}
		double acceleration(double startVel, double displacement, double time)	{	return (displacement - startVel * time)*2 / (time*time);	}
	};
	void init(); // create the projectile
	void render() {projectileBatch.Draw();} // draws the projectile on screen
	void move();
	float getRadius() {return radius;}
	class Rotation{
	public:
		Rotation(bool rotating = false, bool clockwise = false)	{	rotation = rotating;	clockwiseRotation = clockwise;	} 
		enum onOff{
			Off = 0,
			On
		};
		bool isRotating()			{	return rotation;			}
		bool rotatingClockwise()	{	return clockwiseRotation;	}
		void setRotation(bool rot)	{	rotation = rot;				}
		void setClockwise(bool clk)	{	clockwiseRotation = clk;	}
	private:
		bool rotation;
		bool clockwiseRotation;
	};

	float radius;
	double mass;					//	measure this in kg
	double diameter;				//	measure this in meters
	Velocity velocity;				//	meters per second
	double lastSetSpeed;
	double lastSetAngle;
	double force;					//	newtons
	double acceleration;			//	m/s/s
	double ballisticCoefficient;	//	
	double formFactor;				//  = Cg/Ci  or BC of bullet divided by bc of G1 model bullet (as defined in 1881 by Krupp)
	/*
	The Krupp artillery shell was 3 calibers long and had an ogival head with a 2 caliber radius. 
	(ogival head is one with a secant ogive of sharpness to describe its shape)
	The traditional or secant ogive is a surface of revolution of the same curve that forms a Gothic arch; that is, a circular arc, of greater radius than the diameter of the cylindrical section ("shank"), is drawn from the edge of the shank until it intercepts the axis.

	If this arc is drawn so that it meets the shank at zero angle 
	(that is, the distance of the centre of the arc from the axis, plus the radius of the shank, equals the radius of the arc), 
	then it is called a tangential or spitzer ogive. 
	This is a very common ogive for high velocity (supersonic) rifle bullets.

	This standard Krupp projectile had a rating of 1.0, and Ingalls defined the Ballistic Coefficient 
	of a bullet as it's ability to overcome air resistance in flight indexed to the Krupp standard reference projectile.
	*/
	double dragCoefficient;			//

	//const double CG

	//some inline functions
	double displacement(double startVel, float acceleration, double time)	{	return startVel * time + 0.5f * acceleration * time * time;	}
	double displacement(double startVel, double finalVel, double time)		{	return 0.5f * (finalVel - startVel)/time;	}
	//	the good old elementary level version, just in case
	double displacement(double speed, double time)							{	return speed / time;	}

	//	utility functions
	double grainsToKg(float grains)		{	return .00006479891 * grains;	}	//	returns the weight in Kg from the grain weight
	double inchesToMetres(float inches)	{	return inches * 0.00254;	}		
	double sectionalDensity()		{	return mass / diameter;	}	//	sectional density as a formula, rather than stored

	GLTriangleBatch projectileBatch;
	GLFrame projectileFrame;
	float x;
	float y;
	float z;
	bool active;
};

