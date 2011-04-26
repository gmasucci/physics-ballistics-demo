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