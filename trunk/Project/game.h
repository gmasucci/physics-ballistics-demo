#pragma once

#ifndef GAME_H
#define GAME_H
 
#include <GLTools.h>
#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <GLFrustum.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLShaderManager.h>
#include <GLGeometryTransform.h>
#include "GameModel.h"
#include "skybox.h"
#include "bass.h"
#include "Projectile.h"
#include "UserInputs.h"
#include "Target.h"
#include <math3d.h>

#include "loadData.h"

#include <time.h>

#define game Game::GetInstance()


class Game
{
public:
	static Game* GetInstance();
	void SetupWindow(int argc, char** argv);
	void Reshape(int width, int height);
	void Display();
	void SetupRC();
	void Init();
	void Update();
	HSAMPLE LoadSample(char* fName);
	void PlaySound(int sound);
	void checkCollision();
	void processKeys(unsigned char key, int x, int y);
	void processKeysUp(unsigned char key, int x, int y);
	void specials(int key, int x, int y);
	void specialsUp(int key, int x, int y);

	void checkBullet();
	
protected:
	Game();
private:
	static Game*		pGame;
	GLFrustum			viewFrustum;
	GLMatrixStack		modelViewMatrix;
	GLMatrixStack		projectionMatrix;
	GLShaderManager		shaderManager;
	GLGeometryTransform	transformPipeline;

public:
	GLFrame				cameraFrame;
	M3DMatrix44f		mCamera;
	GLuint				m_skyboxTextures[SKYBOX_SIDES];
	Skybox				*skybox;
	HSAMPLE				*samples;
	Projectile			*projectile;
	Target				*target;
	DA::GameModel		*models;

	clock_t				m_timer;
	UserInputs			*uinputs;
	//float				m_updateRate;
	//float				m_scale;

private:
	void cameraInit();
	void placeThem();
public:
	vector<unsigned int> textures;

};

#endif