#include "Projectile.h"


Projectile::Projectile(float ix, float iy, float iz)
{
	//formFactor = 
	//ballisticCoefficient = mass / (diameter * diameter * formFactor);
	x=ix;
	y=iy;
	z=iz;
	active=false;
	dragCoefficient = 0.295;
 
}


Projectile::~Projectile(void)
{
}

void Projectile::init()
{
	if (Dbg)
		cout << "INIT CALLED" << endl;
	gltMakeSphere(projectileBatch,0.3f,13,22);
	projectileFrame.SetOrigin(x,y,z);
	for (int colouriterator=0; colouriterator<4;colouriterator++)
	{
		this->velColour[colouriterator] = 1.0f;
	}
}

void Projectile::move()
{
	cout << velocity.yVel << endl;
	if(active)
	{
		projectileFrame.MoveForward(velocity.zVel/FRAMERATE);
		projectileFrame.MoveUp(velocity.yVel/FRAMERATE);
		velocity.yVel=velocity.yVel + (GRAVITY/FRAMERATE);
		cout << velocity.yVel << endl;
		if (projectileFrame.GetOriginY() <= -5)
		{
			velocity.yVel*=-1;
			velocity.zVel*=-0.5f;
		}
		projectileFrame.MoveRight(velocity.xVel/FRAMERATE);
		if (projectileFrame.GetOriginX()>=35*(800/600) || projectileFrame.GetOriginX()<= -35*(800/600))
			velocity.xVel*=-1;

	}
	velColour[0]=1.0-((this->velocity.xVel/FRAMERATE) *0.01) + ((this->velocity.yVel/FRAMERATE) *0.01) + ((this->velocity.zVel/FRAMERATE) *0.01);
	velColour[1]=0.0;//+((this->velocity.yVel/FRAMERATE) *0.01);
	velColour[2]=0.0;//+((this->velocity.zVel/FRAMERATE) *0.01);
	velColour[3]=1.0f;
	cout << velocity.yVel << endl;
}



