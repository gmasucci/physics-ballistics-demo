#include "game.h"
#include "Projectile.h"
#include "Physx.h"
#include "loadData.h"
#include "md2model.h"
#include <GLTools.h>
#define FREEGLUT_STATIC
#include <GL/freeglut.h>



md2model model;

void Reshape(int w, int h)
{
	Game *g = Game::GetInstance();
	g->Reshape(w,h);
}

void Display()
{
	Game *g = Game::GetInstance();
	g->Display();
}
void CleanUp()
{
	Game *g = Game::GetInstance();
	delete g;
}
void processKeys(unsigned char key, int x, int y)
{
	game->processKeys(key, x, y);
}
void processKeysUp(unsigned char key, int x, int y)
{
	game->processKeysUp(key,x,y);
}
void specials(int key, int x, int y)
{
	game->specials(key,x,y);
}
void specialsUp(int key, int x, int y)
{
	game->specialsUp(key,x,y);
}


int main(int argc, char* argv[])
{
	//glutKeyboardFunc(KeyboardFunc);
	Game *g = Game::GetInstance();
	g->SetupWindow(argc, argv);
	g->Init();
	g->SetupRC();
	atexit(CleanUp);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(processKeys);
	glutKeyboardUpFunc(processKeysUp);
	glutSpecialFunc(specials);
	glutSpecialUpFunc(specialsUp);
	glutMainLoop();
	return 0;
}

