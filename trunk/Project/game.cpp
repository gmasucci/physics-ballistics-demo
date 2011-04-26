#include "game.h"
#include <iostream>
using namespace std;

Game * Game::pGame = 0;

Game::Game()
{
	//m_updateRate = 40.0f;
	//m_scale = 20.0f;
}

Game* Game::GetInstance()
{
	if(!pGame)
		pGame = new Game;
	return pGame;
}

void Game::SetupWindow(int argc, char** argv)
{
	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("IPC Project ");
	GLenum err = glewInit();
	if(GLEW_OK != err)
	{
		//glewInit failed, something is wrong
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glutLeaveMainLoop();
	}

}

void Game::Reshape(int w, int h)
{
	
	glViewport(0, 0, w, h);
	viewFrustum.SetPerspective(35.0f, float(w)/float(h), 0.1f, 2000.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}
void Game::Update()
{
	projectile->move();
	if (projectile->active)
	{
		cameraFrame.SetOrigin(projectile->x, projectile->y, projectile->z);
		M3DVector3f bulletForwardVec;
		projectile->projectileFrame.GetForwardVector(bulletForwardVec);
		cameraFrame.SetForwardVector(bulletForwardVec);
		cameraFrame.TranslateLocal(0.0f, 0.5f, -10.0f);
	}

}

void Game::processKeys(unsigned char key, int x, int y)
{
	uinputs->processNormalKeys(key, x, y);
	if (key=='a' || key=='A')
	{
		cameraFrame.RotateLocalY(0.01);
		//cameraFrame.MoveRight(-30);
	}
	if (key=='d' || key=='D')
	{
		cameraFrame.RotateLocalY(-0.01);
		//cameraFrame.MoveRight(30);
	}
	if (key=='w' || key=='W')
	{
		cameraFrame.RotateLocalX(0.01);
		//cameraFrame.MoveUp(30);
	}
	if (key=='s' || key=='S')
	{
		cameraFrame.RotateLocalX(-0.01);
		//cameraFrame.MoveUp(-30);
	}
	if (key=='q' || key=='Q')
	{
		cameraFrame.MoveForward(-10);
	}
	if (key=='e' || key=='E')
	{
		cameraFrame.MoveForward(10);
	}
}

void Game::processKeysUp(unsigned char key, int x, int y)
{
	uinputs->processNormalKeysUp(key, x, y);

}

void Game::specials(int key, int x, int y)
{
	uinputs->specialKey(key,x,y);
}

void Game::specialsUp(int key, int x, int y)
{
	uinputs->specialKeyUp(key,x,y);
}
void Game::checkBullet()
{
	projectile->x = projectile->projectileFrame.GetOriginX();
	projectile->y = projectile->projectileFrame.GetOriginY();
	projectile->z = projectile->projectileFrame.GetOriginZ();

	if (projectile->z < -700)
	{
		delete projectile;
		projectile=NULL;
		projectile= new Projectile(0.0f,0.0f,-1.0f);
		projectile->init();
	}
}

void Game::Display()
{
	static GLfloat vWhiteColor[] = {1.0f,1.0f,1.0f,1.0f};
	static GLfloat tempProjCol[]=	{projectile->velColour[0], projectile->velColour[1],projectile->velColour[2], projectile->velColour[3]};
	cout << "colours: " << projectile->velColour[0] << projectile->velColour[1] << projectile->velColour[2] <<endl;
	static GLfloat lightColour[] =	{1.0f,1.0f,1.0f};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(clock() > m_timer+(CLOCKS_PER_SEC/FRAMERATE))
	{
		Update();
		m_timer=clock();
	}

	modelViewMatrix.PushMatrix();
		/*Skybox Code*/
		modelViewMatrix.PushMatrix();
			cameraFrame.GetCameraMatrix(mCamera);
			//Insert skybox here
			skybox->InitCamera();
			modelViewMatrix.MultMatrix(skybox->mCameraRotOnly);
			glUseProgram(skybox->m_skyBoxShader);
			glUniformMatrix4fv(skybox->m_locMVPSkyBox,1,GL_FALSE,transformPipeline.GetModelViewProjectionMatrix());
			glDisable(GL_DEPTH_TEST);
			skybox->Render();
			glEnable(GL_DEPTH_TEST);
		modelViewMatrix.PopMatrix();
		/*Skybox code ends*/
	
		modelViewMatrix.PushMatrix(mCamera);
			//Insert drawing code here

			modelViewMatrix.PushMatrix();
				modelViewMatrix.MultMatrix(projectile->projectileFrame);
				shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(),transformPipeline.GetProjectionMatrix(), projectile->velColour/*vWhiteColor*/,lightColour,0);
				projectile->render();
			modelViewMatrix.PopMatrix();

			modelViewMatrix.PushMatrix();
				modelViewMatrix.MultMatrix(target->frame);
				shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(),transformPipeline.GetProjectionMatrix(),vWhiteColor, lightColour,0);
				target->render();
			modelViewMatrix.PopMatrix();

	
		modelViewMatrix.PopMatrix();
	modelViewMatrix.PopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();

	checkBullet();
}

void Game::SetupRC()
{
	shaderManager.InitializeStockShaders();
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(0.0f,1.0f,0.0f,1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
	
	modelViewMatrix.LoadIdentity();
	cameraFrame.SetOrigin(0.0f,0.0f,100.0f);
	cameraFrame.SetForwardVector(0.0f, 0.0f, -1.0f);
	cameraFrame.SetUpVector(0.0f,1.0f,0.0f);
	skybox->Init();
	projectile->init();
	target->init();
	
}

void Game::Init()
{
	//uinputs = new UserInputs();
	double tpos[]={0,0,-450};
	double tvel[]={0,0,0};
	double taccel[]={0,0,0};
	target = new Target(100, 0, taccel, tvel, tpos);
	skybox = new Skybox();
	projectile = new Projectile(0.0f,0.0f,-1.0f);
	uinputs = new UserInputs();

	samples = NULL;
	if(!BASS_Init(-1,44100,0,0,NULL))
	{
		cout << "Can't initialize device" << endl;
	}
	samples = new HSAMPLE[1]; //CHange number to increase amount of sounds, or make a vector
	//samples[0] = LoadSample("SAMPLE.wav");
	
}

void Game::PlaySound(int sound)
{
	HCHANNEL ch = BASS_SampleGetChannel(samples[sound], FALSE);
	BASS_ChannelSetAttribute(ch, -1, 50);
	if(!BASS_ChannelPlay(ch,FALSE))
	{
		cout << "Can't play sound" << endl;
	}
}

HSAMPLE Game::LoadSample(char *fName)
{
	HSAMPLE sample;
	if(sample = BASS_SampleLoad(FALSE, fName, 0,0,3,BASS_SAMPLE_OVER_POS))
	{
		cout << "Sample " << fName << "has been loaded. " << endl;
	}else
	{
		cout << "Can't load sample";
	}
	return sample;
}