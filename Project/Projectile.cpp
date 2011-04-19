#include "Projectile.h"


Projectile::Projectile(float ix, float iy, float iz)
{
	//formFactor = 
	//ballisticCoefficient = mass / (diameter * diameter * formFactor);
	x=ix;
	y=iy;
	z=iz;
	active=false;
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
}

void Projectile::move()
{
	for (int i = 0; i<32; i++)
			cout << "\b \b";
	cout << velocity.yVel;
	if(active)
	{
		projectileFrame.MoveForward(velocity.zVel/FRAMERATE);
		projectileFrame.MoveUp(velocity.yVel/FRAMERATE);
		velocity.yVel=velocity.yVel + (GRAVITY/FRAMERATE);
		for (int i = 0; i<32; i++)
			cout << "\b \b";
		cout << velocity.yVel;
		if (projectileFrame.GetOriginY() <= -5)
		{
			velocity.yVel*=-1;
			velocity.zVel*=-0.5f;
		}
		projectileFrame.MoveRight(velocity.xVel/FRAMERATE);
		if (projectileFrame.GetOriginX()>=35*(800/600) || projectileFrame.GetOriginX()<= -35*(800/600))
			velocity.xVel*=-1;

	}
	//cout << velocity.yVel << endl;
}



