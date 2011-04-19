#pragma once
#ifndef SKYBOX_H
#define SKYBOX_H
#include <GLTools.h>
#include <GL/freeglut.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <GLShaderManager.h>
#include <StopWatch.h>
#include <time.h>
#include <GLFrame.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include "enumerations.h"
class Skybox
{
public:
	Skybox();
	void InitCamera(); //Initialize the camera to work with the skybox
	void Init(); //Initialize the skybox
	void Render(); //Render the skybox
private:
public:
	M3DMatrix44f		mCameraRotOnly;
	M3DMatrix44f		mInverseCamera;
	GLenum				m_cube[SKYBOX_SIDES];
	GLint				m_skyBoxShader;
	GLint				m_locMVPSkyBox;
	GLuint				m_cubeTexture;
	GLBatch				m_cubeBatch;
};

#endif