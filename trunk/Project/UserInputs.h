#pragma once

#define FREEGLUT_STATIC
#include <gl/freeglut.h>



class UserInputs
{
public:
	UserInputs();
	~UserInputs()	{	};
	void processNormalKeys(unsigned char key, int x, int y);
	void processNormalKeysUp(unsigned char key, int x, int y);
	void specialKeyUp(int key, int x, int y);
	void specialKey(int key, int x, int y); 

	bool keyOn[256];
	bool specialKeyOn[256];

	// key functions
	void leftKey();
	void rightKey();
	void upKey();
	void downKey();
	void spaceBar();
};