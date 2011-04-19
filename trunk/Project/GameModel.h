#pragma once
/*
	this file and the corresponding cpp file are extrapolations of the
	md2model.h and .cpp code from daniel livingstone
*/

/* md2model.h - based on original:
 * md2.c -- md2 model loader
 * Modified to add very simple OO structure & some changes to
 * make it easy to import and use into existing code
 * last modification: November 2010 by Daniel Livingstone
 *
 * Copyright (c) 2005-2007 David HENRY
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * gcc -Wall -ansi -lGL -lGLU -lglut md2.c -o md2
 */

#include <GLTools.h>
#include <GLFrame.h>
#include <GLBatch.h>

// Animation List
// This contains the standard list of MD2 animations
// All Quake 2 models will conform to this list - but MD2 models can potentially
// store additional animations and frames. Such extensions are not be supported
// here.

static const enum ANIM
{
			MD2_STAND,
			MD2_RUN,
			MD2_ATTACK,
			MD2_PAIN1,
			MD2_PAIN2,
			MD2_PAIN3,
			MD2_JUMP,
			MD2_FLIP,
			MD2_SALUTE,
			MD2_TAUNT,
			MD2_WAVE,
			MD2_POINT,
			MD2_CRSTAND,
			MD2_CRWALK,
			MD2_CRATTACK,
			MD2_CRPAIN,
			MD2_CRDEATH,
			MD2_DEATH1,
			MD2_DEATH2,
			MD2_DEATH3
};

/* MD2 header */
struct md2_header_t
{
  int ident;
  int version;

  int skinwidth;
  int skinheight;

  int framesize;

  int num_skins;
  int num_vertices;
  int num_st;
  int num_tris;
  int num_glcmds;
  int num_frames;

  int offset_skins;
  int offset_st;
  int offset_tris;
  int offset_frames;
  int offset_glcmds;
  int offset_end;
};

/* Texture name */
struct md2_skin_t
{
  char name[64];
};

/* Texture coords */
struct md2_texCoord_t
{
  short s;
  short t;
};

/* Triangle info */
struct md2_triangle_t
{
  unsigned short vertex[3];
  unsigned short st[3];
};

/* Compressed vertex */
struct md2_vertex_t
{
  unsigned char v[3];
  unsigned char normalIndex;
};

/* Model frame */
struct md2_frame_t
{
  M3DVector3f scale;
  M3DVector3f translate;
  char name[16];
  struct md2_vertex_t *verts;
};

/* GL command packet */
struct md2_glcmd_t
{
  float s;
  float t;
  int index;
};

/* MD2 model structure */
struct md2_model_t
{
  struct md2_header_t header;

  struct md2_skin_t *skins;
  struct md2_texCoord_t *texcoords;
  struct md2_triangle_t *triangles;
  struct md2_frame_t *frames;
  int *glcmds;

  GLuint tex_id;
};

//	names of the sound array positions
enum Sounds
{
	WALK=0,
	REST,
	ATTACK,
	HURT,
	DIE,
	YELL
};

//	names of the texture array positions for the model
enum Skins
{
	BASE=0,
	ANGRY,
	PAIN,
	DEAD,
	ULTIMATE
};

namespace DA
{
	class GameModel
	{
	public:
		GameModel(void);
		GameModel(const char *fileToLoad);
		~GameModel(void);
		int ReadMD2Model(const char *filename);
		void FreeModel();
		void RenderFrameItp();
		void Animate(int animation, float dt);
		int setCurrentAnim(int n);
		int getAnim()				{	return currentAnim;		};
		GLFrame mdlFrame;

		float scale;
		unsigned long sounds[6];
		unsigned int textures[5];
		
		float interp;
	private:
		md2_model_t mdl;
		int currentAnim;
		int currentFrame;
		int nextFrame;
		//float interp;
		GLBatch triangles;
	};
}