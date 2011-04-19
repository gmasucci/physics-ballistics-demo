#include "Target.h"




void Target::render(){
	batch.Draw();
}

void Target::init(){
	frame.SetOrigin(startPos[0], startPos[1], startPos[2]);
	gltMakeCube(batch, 2.5);
}