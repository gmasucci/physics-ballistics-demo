#include "game.h"
#include "UserInputs.h"
#include "Projectile.h"



UserInputs::UserInputs(){
	for (int i=0; i<256; i++)
	{
		keyOn[i]=false;
		specialKeyOn[i]=false;
	}
}

void UserInputs::processNormalKeysUp(unsigned char key, int x, int y){
	keyOn[key]=false;
}

void UserInputs::specialKeyUp(int key, int x, int y){
	specialKeyOn[key]=false;
}

void UserInputs::leftKey()
{
}

void UserInputs::rightKey()
{
}

void UserInputs::upKey()
{
	game->projectile->velocity.zVel=110;
	game->projectile->velocity.yVel=20;
	game->projectile->active=true;

}

void UserInputs::downKey()
{
	Game::GetInstance()->projectile->velocity.calcVelocities(45, -30);
	game->projectile->lastSetAngle*=-0.5;
	game->projectile->lastSetSpeed*=-1;
}

void UserInputs::spaceBar()
{
	Game::GetInstance()->projectile->velocity.calcVelocities(45, 30);
	game->projectile->lastSetAngle=45;
	game->projectile->lastSetSpeed=30;
}

void UserInputs::specialKey(int key, int x, int y) {
	specialKeyOn[key]=true;
  
    //if(glutGetModifiers() & GLUT_ACTIVE_SHIFT) { // testing SHIFT status
    switch(key) {

		case GLUT_KEY_F1:
			{
				//window2FS();  //not implemented yet
			}
			break;
		case GLUT_KEY_F8:
			{
				//selectShotTypeKey();
				break;
			}
		case GLUT_KEY_F9:
			{
				//WindON = !WindON;
				break;
			}
		case GLUT_KEY_F12:
			{
				//f12Key();
				break;
			}
        case GLUT_KEY_LEFT:
          // code here 100
			{
				leftKey();
				break;
			}
			
          /*break;*/
        case GLUT_KEY_RIGHT:
          // code here 102
			{
				rightKey();
				break;
			}
          /*break;*/
        case GLUT_KEY_UP:
          // code here 101
			{
				upKey();
				break;
			}
			
        case GLUT_KEY_DOWN:
          // code here 103
			{
				downKey();
				break;
			}
	         /*break;*/
	}

}



void UserInputs::processNormalKeys(unsigned char key, int x, int y){ 
	keyOn[/*(int)*/key]=true;
	//if(keyOn[32])
	//	spaceBar();
	int tmpkey = (int)key;
	switch ((int)key){
		case (27)://escape
			{
				cout << "\nWell, you just hit escape.\n\n\aWhy would you do that?!?!?!?\n\n";
				exit(0);
				break;
			}
		case (32)://space
			{
				spaceBar();
				break;
			}
		case (72)://H
			{
				if (keyOn[key]){
					//displayHelpText= !displayHelpText;
					break;
				}
				break;
			}
		case (104)://h
			{
				if (keyOn[key]){
					//displayHelpText= !displayHelpText;
					break;
				}
				break;
			}
			break;
	}
	if(keyOn['l'])
	{
		Game *g = g->GetInstance();
		g->cameraFrame.SetOrigin(g->projectile->projectileFrame.GetOriginX(),g->projectile->projectileFrame.GetOriginY(),g->projectile->projectileFrame.GetOriginZ());
		g->cameraFrame.RotateLocalX(m3dDegToRad(90));
	}
}