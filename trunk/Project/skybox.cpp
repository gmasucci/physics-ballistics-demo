#include "game.h"
#include "skybox.h"
#include "loadData.h"
#include <iostream>
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
#define FREEGLUT_STATIC
#include <iostream>
#include <fstream>
#include <sstream>

#include <math.h>
#include <stdio.h>
using namespace std;
Skybox::Skybox()
{
	
}
void Skybox::Init()
{
	Game::GetInstance();
	char *m_skyboxFiles[SKYBOX_SIDES] = { "Textures/Skybox/pos_x.tga", "Textures/Skybox/neg_x.tga", "Textures/Skybox/pos_y.tga", "Textures/Skybox/neg_y.tga", "Textures/Skybox/pos_z.tga", "Textures/Skybox/neg_z.tga" };
	GLuint _skyboxTexture;

	gltMakeCube(m_cubeBatch, 20.0f);
	m_cube[0]=GL_TEXTURE_CUBE_MAP_POSITIVE_X;
	m_cube[1]=GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
	m_cube[2]=GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
	m_cube[3]=GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
	m_cube[4]=GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
	m_cube[5]=GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
	

	GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;
    int i;
       
    // Cull backs of polygons
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //glEnable(GL_DEPTH_TEST);
        
    glGenTextures(1, &_skyboxTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTexture);
        
    // Set up texture maps        
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);       
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
  
    // Load Cube Map images
    for(i = 0; i < 6; i++)
        {        
        // Load this texture map
        pBytes = gltReadTGABits(m_skyboxFiles[i], &iWidth, &iHeight, &iComponents, &eFormat);
        glTexImage2D(m_cube[i], 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
        free(pBytes);
        }
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
                                           
    m_skyBoxShader = gltLoadShaderPairWithAttributes("SkyBox.vp", "SkyBox.fp", 2, 
                                                GLT_ATTRIBUTE_VERTEX, "vVertex",
                                                GLT_ATTRIBUTE_NORMAL, "vNormal");

	m_locMVPSkyBox = glGetUniformLocation(m_skyBoxShader, "mvpMatrix");

	m_cube[0]=game->m_skyboxTextures[0];
	m_cube[1]=game->m_skyboxTextures[1];
	m_cube[2]=game->m_skyboxTextures[2];
	m_cube[3]=game->m_skyboxTextures[3];
	m_cube[4]=game->m_skyboxTextures[4];
	m_cube[5]=game->m_skyboxTextures[5];
}
void Skybox::InitCamera()
{
	game->cameraFrame.GetCameraMatrix(mCameraRotOnly,true);
	m3dInvertMatrix44(mInverseCamera, mCameraRotOnly);
}
void Skybox::Render()
{
	//game->modelViewMatrix.MultMatrix(mCameraRotOnly);
	//glUseProgram(m_skyBoxShader);
	//glUniformMatrix4fv(m_locMVPSkyBox, 1, GL_FALSE, game->transformPipeline.GetModelViewProjectionMatrix());
	//glDisable(GL_DEPTH_TEST);
	m_cubeBatch.Draw();
	//glEnable(GL_DEPTH_TEST);
}