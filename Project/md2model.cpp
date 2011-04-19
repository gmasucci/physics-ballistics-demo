/* md2model.cpp - based on original:
 * md2.c -- md2 model loader
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

#define WIN32
#include <GLTools.h>
#include <GLFrame.h>
#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md2model.h"


#include <iostream>
using namespace std;

/* Table of precalculated normals */
M3DVector3f anorms_table[162] = {
#include "anorms.h"
};

// Table of animation begin/end frames
static int animFrameList[40] = {
	0, 39, // stand
	40, 45, // run
	46, 53, // attack
	54, 57, //pain1
	58, 61, //pain2
	62, 65, //pain3
	66, 71, //jump
	72, 83, //flip
	84, 94, //salute
	95, 111, //taunt
	112, 122, //wave
	123, 134, //point
	135, 153, //crstnd
	154, 159, //crwalk
	160, 168, //crattak
	169, 172, //crpain
	173, 177, //crdeath
	178, 183, //death1
	184, 189, //death2
	190, 196 //death3
};

md2model::md2model()
{
	m_currentAnim = 0;
	m_currentFrame = 0;
	m_nextFrame = 1;
	m_interp = 0.0f;
	m_delete=false;
}

md2model::md2model(const char *_filename)
{
	ReadMD2Model(_filename);
	m_currentAnim = 0;
	m_currentFrame = 0;
	m_nextFrame = 1;
	m_interp = 0.0f;
	m_delete=false;
	
}

md2model::~md2model()
{
	FreeModel();
}

/**
 * Load an MD2 model from file.
 *
 * Note: MD2 format stores model's data in little-endian ordering.  On
 * big-endian machines, you'll have to perform proper conversions.
 */
int md2model::ReadMD2Model (const char *_filename)
{
  FILE *fp;
  int i;

  fp = fopen (_filename, "rb");
  if (!fp)
    {
      fprintf (stderr, "Error: couldn't open \"%s\"!\n", _filename);
      return 0;
    }

  /* Read header */
  fread (&mdl.header, 1, sizeof (struct md2_header_t), fp);

  if ((mdl.header.ident != 844121161) ||
      (mdl.header.version != 8))
    {
      /* Error! */
      fprintf (stderr, "Error: bad version or identifier\n");
      fclose (fp);
      return 0;
    }

  /* Memory allocations */
  mdl.skins = (struct md2_skin_t *)
    malloc (sizeof (struct md2_skin_t) * mdl.header.num_skins);
  mdl.texcoords = (struct md2_texCoord_t *)
    malloc (sizeof (struct md2_texCoord_t) * mdl.header.num_st);
  mdl.triangles = (struct md2_triangle_t *)
    malloc (sizeof (struct md2_triangle_t) * mdl.header.num_tris);
  mdl.frames = (struct md2_frame_t *)
    malloc (sizeof (struct md2_frame_t) * mdl.header.num_frames);
  mdl.glcmds = (int *)malloc (sizeof (int) * mdl.header.num_glcmds);

  /* Read model data */
  fseek (fp, mdl.header.offset_skins, SEEK_SET);
  fread (mdl.skins, sizeof (struct md2_skin_t),
	 mdl.header.num_skins, fp);

  fseek (fp, mdl.header.offset_st, SEEK_SET);
  fread (mdl.texcoords, sizeof (struct md2_texCoord_t),
	 mdl.header.num_st, fp);

  fseek (fp, mdl.header.offset_tris, SEEK_SET);
  fread (mdl.triangles, sizeof (struct md2_triangle_t),
	 mdl.header.num_tris, fp);

  fseek (fp, mdl.header.offset_glcmds, SEEK_SET);
  fread (mdl.glcmds, sizeof (int), mdl.header.num_glcmds, fp);

  /* Read frames */
  fseek (fp, mdl.header.offset_frames, SEEK_SET);
  for (i = 0; i < mdl.header.num_frames; ++i)
    {
      /* Memory allocation for vertices of this frame */
      mdl.frames[i].verts = (struct md2_vertex_t *)
	malloc (sizeof (struct md2_vertex_t) * mdl.header.num_vertices);

      /* Read frame data */
      fread (mdl.frames[i].scale, sizeof (M3DVector3f), 1, fp);
      fread (mdl.frames[i].translate, sizeof (M3DVector3f), 1, fp);
      fread (mdl.frames[i].name, sizeof (char), 16, fp);
      fread (mdl.frames[i].verts, sizeof (struct md2_vertex_t),
	     mdl.header.num_vertices, fp);
    }

  fclose (fp);
  triangles.Begin(GL_TRIANGLES,(GLuint)mdl.header.num_tris * 3,1);
  return 1;
}


/**
 * Free resources allocated for the model.
 */
void md2model::FreeModel ()
{
  int i;

  if (mdl.skins)
    {
      free (mdl.skins);
      mdl.skins = NULL;
    }

  if (mdl.texcoords)
    {
      free (mdl.texcoords);
      mdl.texcoords = NULL;
    }

  if (mdl.triangles)
    {
      free (mdl.triangles);
      mdl.triangles = NULL;
    }

  if (mdl.glcmds)
    {
      free (mdl.glcmds);
      mdl.glcmds = NULL;
    }

  if (mdl.frames)
    {
      for (i = 0; i < mdl.header.num_frames; ++i)
	{
	  free (mdl.frames[i].verts);
	  mdl.frames[i].verts = NULL;
	}

      free (mdl.frames);
      mdl.frames = NULL;
    }
}


/**
 * Render the model with interpolation between frame n and n+1.
 * interp is the interpolation percent. (from 0.0 to 1.0)
 */
void md2model::RenderFrameItp()
{
  int i, j;
  GLfloat s, t;
  M3DVector3f v, norm, v_curr, v_next;
  float *_n_curr, *_n_next;
  struct md2_frame_t *pframe1, *pframe2;
  struct md2_vertex_t *pvert1, *pvert2;

  /* Check if currentFrame is in a valid range */
  if ((m_currentFrame < 0) || (m_currentFrame > mdl.header.num_frames))
    return;
  // Clear the current batch contents
  triangles.Reset();
  /* Add model to batch */
  //triangles.Begin(GL_TRIANGLES,(GLuint)mdl.header.num_tris * 3,1);
	  
    /* Draw each triangle */
    for (i = 0; i < mdl.header.num_tris; ++i)
      {
	/* Draw each vertex */
	for (j = 0; j < 3; ++j)
	  {
	    pframe1 = &mdl.frames[m_currentFrame];
	    pframe2 = &mdl.frames[m_nextFrame];
	    pvert1 = &pframe1->verts[mdl.triangles[i].vertex[j]];
	    pvert2 = &pframe2->verts[mdl.triangles[i].vertex[j]];

	    /* Compute texture coordinates */
	    s = (GLfloat)mdl.texcoords[mdl.triangles[i].st[j]].s / mdl.header.skinwidth;
	    t = (GLfloat)mdl.texcoords[mdl.triangles[i].st[j]].t / mdl.header.skinheight;

	    /* Pass texture coordinates to batch */
		triangles.MultiTexCoord2f(0,s,t);

		/* Interpolate normals */
	    _n_curr = anorms_table[pvert1->normalIndex];
	    _n_next = anorms_table[pvert2->normalIndex];

	    norm[0] = _n_curr[0] + m_interp * (_n_next[0] - _n_curr[0]);
	    norm[1] = _n_curr[1] + m_interp * (_n_next[1] - _n_curr[1]);
	    norm[2] = _n_curr[2] + m_interp * (_n_next[2] - _n_curr[2]);

		triangles.Normal3fv(norm);

	    /* Interpolate vertices */
		// Doing these scaling operations *every* refresh is *very* wasteful
		// Should do all the scaling calculations once only, when loading the file
	    v_curr[0] = pframe1->scale[0] * pvert1->v[0] + pframe1->translate[0];
	    v_curr[1] = pframe1->scale[1] * pvert1->v[1] + pframe1->translate[1];
	    v_curr[2] = pframe1->scale[2] * pvert1->v[2] + pframe1->translate[2];

	    v_next[0] = pframe2->scale[0] * pvert2->v[0] + pframe2->translate[0];
	    v_next[1] = pframe2->scale[1] * pvert2->v[1] + pframe2->translate[1];
	    v_next[2] = pframe2->scale[2] * pvert2->v[2] + pframe2->translate[2];

	    v[0] = v_curr[0] + m_interp * (v_next[0] - v_curr[0]);
	    v[1] = v_curr[1] + m_interp * (v_next[1] - v_curr[1]);
	    v[2] = v_curr[2] + m_interp * (v_next[2] - v_curr[2]);

		triangles.Vertex3fv(v);
	  }
    }
	triangles.End();
	triangles.Draw();
}


/**
 * Calculate the current frame in animation, based on
 * selected animation and current frame. If current frame
 * is not in selected animation sequence, new current frame
 * is start of animation sequence. 
 * If interpolation is past 1.0, move current frame to next
 * and next frame = current frame + 1
 */
void md2model::Animate (int _animation, float _dt)
{
	//CTimeManager* tm = CTimeManager::GetInstance();
	
	m_endFrame=false;
	int _start = animFrameList[_animation * 2];
	int _end =  animFrameList[_animation * 2 + 1];
	if ((m_currentFrame < _start) || (m_currentFrame > _end))
	{
		m_currentFrame = _start;
		m_nextFrame = _start + 1;
	}
	m_interp += _dt;
	if (m_interp >= 1.0f)
    {

		/* Move to next frame */
		m_interp = 0.0f;
		m_currentFrame = m_nextFrame;
		m_nextFrame++;
		if (m_nextFrame >= _end+1 && _animation == MD2_DEATH1){
			m_endFrame=true;
			m_delete=true;
		}
		else if(m_nextFrame >= _end+1){
			m_endFrame=true;
			m_nextFrame = _start;
		}
    }
}
void md2model::setCurrentAnim(int _n)
{
	m_currentAnim = _n;
}

int md2model::GetCurrentAnim()
{
	return m_currentAnim;
}
int md2model::GetCurrentFrame()
{
	return m_currentFrame;
}
bool md2model::IsEndFrame()
{
	return m_delete;//m_endFrame;
}
