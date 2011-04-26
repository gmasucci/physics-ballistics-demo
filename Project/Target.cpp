#include "Target.h"




void Target::render(){
	batch.Draw();
}

void Target::init(){
	frame.SetOrigin(startPos[0], startPos[1], startPos[2]);
	//gltMakeCube(batch, width);
	batch.Begin(GL_TRIANGLES, 36, 1);

	/////////////////////////////////////////////
	// Top of cube
	batch.Normal3f(0.0f, 1.0f, 0.0f);
	batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	batch.Vertex3f(width, width, width);

	batch.Normal3f(0.0f, 1.0f, 0.0f);
	batch.MultiTexCoord2f(0, 1.0f, 0.0f);
	batch.Vertex3f(width, width, -width);

	batch.Normal3f(0.0f, 1.0f, 0.0f);
	batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	batch.Vertex3f(-width, width, -width);

	batch.Normal3f(0.0f, 1.0f, 0.0f);
	batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	batch.Vertex3f(width, width, width);

	batch.Normal3f(0.0f, 1.0f, 0.0f);
	batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	batch.Vertex3f(-width, width, -width);

	batch.Normal3f(0.0f, 1.0f, 0.0f);
	batch.MultiTexCoord2f(0, 0.0f, 1.0f);
	batch.Vertex3f(-width, width, width);


	////////////////////////////////////////////
	// Bottom of cube
	batch.Normal3f(0.0f, -1.0f, 0.0f);
	batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	batch.Vertex3f(-width, -width, -width);

	batch.Normal3f(0.0f, -1.0f, 0.0f);
	batch.MultiTexCoord2f(0, 1.0f, 0.0f);
	batch.Vertex3f(width, -width, -width);

	batch.Normal3f(0.0f, -1.0f, 0.0f);
	batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	batch.Vertex3f(width, -width, width);

	batch.Normal3f(0.0f, -1.0f, 0.0f);
	batch.MultiTexCoord2f(0, 0.0f, 1.0f);
	batch.Vertex3f(-width, -width, width);

	batch.Normal3f(0.0f, -1.0f, 0.0f);
	batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	batch.Vertex3f(-width, -width, -width);

	batch.Normal3f(0.0f, -1.0f, 0.0f);
	batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	batch.Vertex3f(width, -width, width);

	///////////////////////////////////////////
	// Left side of cube
	batch.Normal3f(-1.0f, 0.0f, 0.0f);
	batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	batch.Vertex3f(-width, width, width);

	batch.Normal3f(-1.0f, 0.0f, 0.0f);
	batch.MultiTexCoord2f(0, 1.0f, 0.0f);
	batch.Vertex3f(-width, width, -width);

	batch.Normal3f(-1.0f, 0.0f, 0.0f);
	batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	batch.Vertex3f(-width, -width, -width);

	batch.Normal3f(-1.0f, 0.0f, 0.0f);
	batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	batch.Vertex3f(-width, width, width);

	batch.Normal3f(-1.0f, 0.0f, 0.0f);
	batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	batch.Vertex3f(-width, -width, -width);

	batch.Normal3f(-1.0f, 0.0f, 0.0f);
	batch.MultiTexCoord2f(0, 0.0f, 1.0f);
	batch.Vertex3f(-width, -width, width);

	// Right side of cube
	batch.Normal3f(1.0f, 0.0f, 0.0f);
	batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	batch.Vertex3f(width, -width, -width);

	batch.Normal3f(1.0f, 0.0f, 0.0f);
	batch.MultiTexCoord2f(0, 1.0f, 0.0f);
	batch.Vertex3f(width, width, -width);

	batch.Normal3f(1.0f, 0.0f, 0.0f);
	batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	batch.Vertex3f(width, width, width);

	batch.Normal3f(1.0f, 0.0f, 0.0f);
	batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	batch.Vertex3f(width, width, width);

	batch.Normal3f(1.0f, 0.0f, 0.0f);
	batch.MultiTexCoord2f(0, 0.0f, 1.0f);
	batch.Vertex3f(width, -width, width);

	batch.Normal3f(1.0f, 0.0f, 0.0f);
	batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	batch.Vertex3f(width, -width, -width);

	// Front and Back
	// Front
	batch.Normal3f(0.0f, 0.0f, 1.0f);
	batch.MultiTexCoord2f(0, 1.0f, 0.0f);
	batch.Vertex3f(width, -width, width);

	batch.Normal3f(0.0f, 0.0f, 1.0f);
	batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	batch.Vertex3f(width, width, width);

	batch.Normal3f(0.0f, 0.0f, 1.0f);
	batch.MultiTexCoord2f(0, 0.0f, 1.0f);
	batch.Vertex3f(-width, width, width);

	batch.Normal3f(0.0f, 0.0f, 1.0f);
	batch.MultiTexCoord2f(0, 0.0f, 1.0f);
	batch.Vertex3f(-width, width, width);

	batch.Normal3f(0.0f, 0.0f, 1.0f);
	batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	batch.Vertex3f(-width, -width, width);

	batch.Normal3f(0.0f, 0.0f, 1.0f);
	batch.MultiTexCoord2f(0, 1.0f, 0.0f);
	batch.Vertex3f(width, -width, width);

	// Back
	batch.Normal3f(0.0f, 0.0f, -1.0f);
	batch.MultiTexCoord2f(0, 1.0f, 0.0f);
	batch.Vertex3f(width, -width, -width);

	batch.Normal3f(0.0f, 0.0f, -1.0f);
	batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	batch.Vertex3f(-width, -width, -width);

	batch.Normal3f(0.0f, 0.0f, -1.0f);
	batch.MultiTexCoord2f(0, 0.0f, 1.0f);
	batch.Vertex3f(-width, width, -width);

	batch.Normal3f(0.0f, 0.0f, -1.0f);
	batch.MultiTexCoord2f(0, 0.0f, 1.0f);
	batch.Vertex3f(-width, width, -width);

	batch.Normal3f(0.0f, 0.0f, -1.0f);
	batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	batch.Vertex3f(width, width, -width);

	batch.Normal3f(0.0f, 0.0f, -1.0f);
	batch.MultiTexCoord2f(0, 1.0f, 0.0f);
	batch.Vertex3f(width, -width, -width);

	batch.End();
}

void Target::collision(Projectile *p)
{
	/*

	m1*v1i + m2*v2i = m1*v1f + m2*v2f 
	(m1*v1i +m2*v2i )-m1*v1f / m2
	
	page 382 Beginning Maths and Physics for Game Programming
	*/

	double m1 = p->getMass();
	double m2 = mass;
	double v1i[3] = { p->velocity.xVel, p->velocity.yVel, p->velocity.zVel};
	double v2i[3] = {velocity[0],velocity[1],velocity[2]};
	double v1f[3] = {0.0f,0.0f,0.0f};

	/*v1i[0] = m1*v1i[0]; v1i[1]=m1*v1i[1]; v1i[2] = m1*v1i[2];
	v2i[0] = m2*v2i[0]; v2i[1]=m2*v2i[1]; v2i[2] = m2*v2i[2];
	v1f[0] = m1*-v1f[0]; v1f[1]=m1*-v1f[1]; v1f[2] = m1*-v1f[2];*/

	for (int i = 0; i<3; i++)
	{
		velocity[i] = (m1*v1i[i] + m2*v2i[i] - m1*v1f[i]) / m2;		
	}
}

void Target::move(){
	frame.SetOrigin(frame.GetOriginX()+velocity[0], 0, frame.GetOriginZ()-velocity[2]);
}