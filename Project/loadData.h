#pragma once
#ifndef LOADDATA_H
#define LOADDATA_H
#include <GLTools.h>
#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <GLShaderManager.h>
//#include <StopWatch.h>
//#include <time.h>
//#include <GLFrame.h>



#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class CLoadData
{
public:
	static CLoadData* GetInstance();
	void LoadTXT(char *_fName, vector<GLuint> &_vName); //Load texture filenames from .txt file
	void LoadUWSM(GLTriangleBatch &_object, char* _fName); //Load models from .uwsm files
	GLuint LoadTexture(char *_fName, GLuint *_texID); //Load texture
	//HSAMPLE LoadSample(char* _fName); //Load sounds
protected:
	CLoadData();
public:
	static CLoadData*		pLoadData;
};

#endif
