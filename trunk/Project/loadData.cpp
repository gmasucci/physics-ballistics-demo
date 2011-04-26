#include "loadData.h"
#include <iostream>
#include <GLTools.h>

#include <GLBatch.h>
#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <math.h>
#include <stdio.h>
using namespace std;

CLoadData* CLoadData::pLoadData = 0;

CLoadData* CLoadData::GetInstance()
{
		if(!pLoadData)
			pLoadData = new CLoadData;			
		return pLoadData;
}
CLoadData::CLoadData()
{
}

void CLoadData::LoadUWSM(GLTriangleBatch &_object, char *_fName)
{	
	ifstream::pos_type size;
	char *_memblock;

	ifstream file (_fName, ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{
		size = file.tellg();
		_memblock = new char [size];
		file.seekg (0, ios::beg);
		file.read (_memblock, size);
		file.close();
	}
	else
	{	// Creates empty triangle mesh if file fails to load
		cerr << "Unable to open file " << _fName << endl;
		_object.BeginMesh(0);
		_object.End();
		return;
	}

	stringstream strstream(_memblock); 	// Copy file into a stringstream

	string _magicnumber;					// Basic check: is this a uwsm file?
	strstream >> _magicnumber;
	if (_magicnumber.compare(0,4,"uwsm")!=0)
	{	// could also use the version number, but not doing that just now
		cerr << "File " << _fName << " is not a uwsm file." << endl;
		_object.BeginMesh(0);
		_object.End();
		return;
	}

	// Read geometry
	int i, _count; //count is number of floats, ie verts x 3
	strstream >> _count;
	M3DVector3f *vertices = new M3DVector3f[_count/3];
	for (i=0;i<_count/3;i++)
		strstream >> vertices[i][0] >> vertices[i][1] >> vertices[i][2];

	// Read normals
	strstream >> _count; // how many normals? normally will be same as vertices
	M3DVector3f *normals = new M3DVector3f[_count/3];
		for (i=0;i<_count/3;i++)
			strstream >> normals[i][0] >> normals[i][1] >> normals[i][2];	

	// Read texture coordinates
	strstream >> _count; // how many texture coords? need not be same as vertices
	M3DVector2f *uv = new M3DVector2f[_count/2];
	if (_count > 0)	// model has UV coordinates
		for (i=0;i<_count/2;i++)
			strstream >> uv[i][0] >> uv[i][1]; 
	
	int _triangles;
	strstream >> _triangles; // how many *triangles* in mesh?

	// Add data to GLTools TriangleBatch object
	// GLTriangleBatch will remove identical vertices, and free any unused memory
	_object.BeginMesh(_triangles*3); 
	int _v0, _v1, _v2, _t0, _t1, _t2;
	M3DVector3f triangleVerts[3], triangleNorms[3]; 
	M3DVector2f triangleTex[3];
	for (i=0;i<_triangles;i++)
	{
		// vertex & texture indices for one triangle
		strstream >> _v0 >> _t0 >> _v1 >> _t1 >> _v2 >> _t2;
		m3dCopyVector3(triangleVerts[0],vertices[_v0]);
		m3dCopyVector3(triangleVerts[1],vertices[_v1]);
		m3dCopyVector3(triangleVerts[2],vertices[_v2]);

		m3dCopyVector3(triangleNorms[0],normals[_v0]);
		m3dCopyVector3(triangleNorms[1],normals[_v1]);
		m3dCopyVector3(triangleNorms[2],normals[_v2]);

		m3dCopyVector2(triangleTex[0],uv[_t0]);
		m3dCopyVector2(triangleTex[1],uv[_t1]);
		m3dCopyVector2(triangleTex[2],uv[_t2]);
		_object.AddTriangle(triangleVerts,triangleNorms,triangleTex);
	}
	_object.End();

	delete [] _memblock;
	delete [] vertices; 
	delete [] normals;
	delete [] uv;
}

GLuint CLoadData::LoadTexture(char *_fName, GLuint *_texID)
{
	//Generate texture ID
	glGenTextures(1, _texID);
	//texture dimensions and data buffer
	GLint _width, _height, _components;
	GLenum format;
	GLbyte *pBytes;

	//load file - using GLTools library
	pBytes = gltReadTGABits(_fName, &_width, &_height, &_components, &format);
	if(pBytes==NULL)
	{
		cerr << "Something went wrong loading textures " << _fName << endl;
	}
	//Bind texture and set parameters
	glBindTexture(GL_TEXTURE_2D, *_texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,_components,_width,_height,0,format,GL_UNSIGNED_BYTE,pBytes);
	glGenerateMipmap(GL_TEXTURE_2D);
	// Texture loaded, free the temporary buffer
	free(pBytes);
	return *_texID; //Return value of texture ID
}


void CLoadData::LoadTXT(char *_fName, std::vector<GLuint> &_vName) /*This function will read a txt file,line by line, and add the file names to the vector*/
{
	ifstream _textureFile (_fName);
	if(_textureFile.is_open())
	{
		while(_textureFile.good())
		{
			string _temp;
			const char *_charTemp;
			char *_filename;
			GLuint _texture;
			getline(_textureFile,_temp);
			_charTemp=_temp.c_str();
			_filename=(char*)_charTemp;
			LoadTexture(_filename, &_texture);
			_vName.push_back(_texture);
		}
		_textureFile.close();
	}
}

//HSAMPLE CLoadData::LoadSample(char *_fName) /* Function will load a sound sample */
//{
//	HSAMPLE _sam;
//	if(_sam = BASS_SampleLoad(FALSE,_fName,0,0,3,BASS_SAMPLE_OVER_POS))
//	{
//		cout << "sample " << _fName << " loaded." << endl;
//	}else
//	{
//		cout << "Can't load sample";
//	}
//	return _sam;
//}