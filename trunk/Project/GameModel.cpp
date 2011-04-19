#include "GameModel.h"

using namespace DA;

#include <GLTools.h>
#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

GameModel::GameModel()
{
	this->currentAnim = MD2_STAND;
	this->currentFrame = 0;
	this->nextFrame = 1;
	this->interp = 0.0f;
}

GameModel::GameModel(const char *filename)
{
	this->ReadMD2Model(filename);
	this->currentAnim = MD2_STAND;
	this->currentFrame = 0;
	this->nextFrame = 1;
	this->interp = 0.0f;
}

GameModel::~GameModel()
{
	this->FreeModel();
}

/**
 * Load an MD2 model from file.
 *
 * Note: MD2 format stores model's data in little-endian ordering.  On
 * big-endian machines, you'll have to perform proper conversions.
 */
int GameModel::ReadMD2Model (const char *filename)
{
  FILE *fp;
  int i;

  fp = fopen (filename, "rb");
  if (!fp)
    {
      fprintf (stderr, "Error: couldn't open \"%s\"!\n", filename);
      return 0;
    }

  /* Read header */
  fread (&this->mdl.header, 1, sizeof (struct md2_header_t), fp);

  if ((this->mdl.header.ident != 844121161) ||
      (this->mdl.header.version != 8))
    {
      /* Error! */
      fprintf (stderr, "Error: bad version or identifier\n");
      fclose (fp);
      return 0;
    }

  /* Memory allocations */
  this->mdl.skins = (struct md2_skin_t *)
    malloc (sizeof (struct md2_skin_t) * mdl.header.num_skins);
  this->mdl.texcoords = (struct md2_texCoord_t *)
    malloc (sizeof (struct md2_texCoord_t) * mdl.header.num_st);
  this->mdl.triangles = (struct md2_triangle_t *)
    malloc (sizeof (struct md2_triangle_t) * mdl.header.num_tris);
  this->mdl.frames = (struct md2_frame_t *)
    malloc (sizeof (struct md2_frame_t) * mdl.header.num_frames);
  this->mdl.glcmds = (int *)malloc (sizeof (int) * mdl.header.num_glcmds);

  /* Read model data */
  fseek (fp, this->mdl.header.offset_skins, SEEK_SET);
  fread (this->mdl.skins, sizeof (struct md2_skin_t),
	 this->mdl.header.num_skins, fp);

  fseek (fp, this->mdl.header.offset_st, SEEK_SET);
  fread (this->mdl.texcoords, sizeof (struct md2_texCoord_t),
	 this->mdl.header.num_st, fp);

  fseek (fp, this->mdl.header.offset_tris, SEEK_SET);
  fread (this->mdl.triangles, sizeof (struct md2_triangle_t),
	 this->mdl.header.num_tris, fp);

  fseek (fp, this->mdl.header.offset_glcmds, SEEK_SET);
  fread (this->mdl.glcmds, sizeof (int), this->mdl.header.num_glcmds, fp);

  /* Read frames */
  fseek (fp, this->mdl.header.offset_frames, SEEK_SET);
  for (i = 0; i < this->mdl.header.num_frames; ++i)
    {
      /* Memory allocation for vertices of this frame */
      this->mdl.frames[i].verts = (struct md2_vertex_t *)
	malloc (sizeof (struct md2_vertex_t) * this->mdl.header.num_vertices);

      /* Read frame data */
      fread (this->mdl.frames[i].scale, sizeof (M3DVector3f), 1, fp);
      fread (this->mdl.frames[i].translate, sizeof (M3DVector3f), 1, fp);
      fread (this->mdl.frames[i].name, sizeof (char), 16, fp);
      fread (this->mdl.frames[i].verts, sizeof (struct md2_vertex_t),
	     this->mdl.header.num_vertices, fp);
    }

  fclose (fp);
  this->triangles.Begin(GL_TRIANGLES,(GLuint)this->mdl.header.num_tris * 3,1);

  return 1;
}

/**
 * Free resources allocated for the model.
 */
void GameModel::FreeModel ()
{
  int i;

  if (this->mdl.skins)
    {
      free (this->mdl.skins);
      mdl.skins = NULL;
    }

  if (this->mdl.texcoords)
    {
      free (this->mdl.texcoords);
      this->mdl.texcoords = NULL;
    }

  if (this->mdl.triangles)
    {
      free (this->mdl.triangles);
      this->mdl.triangles = NULL;
    }

  if (this->mdl.glcmds)
    {
      free (this->mdl.glcmds);
      this->mdl.glcmds = NULL;
    }

  if (this->mdl.frames)
    {
      for (i = 0; i < this->mdl.header.num_frames; ++i)
	{
	  free (this->mdl.frames[i].verts);
	  this->mdl.frames[i].verts = NULL;
	}

      free (this->mdl.frames);
      this->mdl.frames = NULL;
    }
}

/**
 * Render the model with interpolation between frame n and n+1.
 * interp is the interpolation percent. (from 0.0 to 1.0)
 */
void GameModel::RenderFrameItp()
{
  int i, j;
  GLfloat s, t;
  M3DVector3f v, norm, v_curr, v_next;
  float *n_curr, *n_next;
  struct md2_frame_t *pframe1, *pframe2;
  struct md2_vertex_t *pvert1, *pvert2;

  /* Check if currentFrame is in a valid range */
  if ((this->currentFrame < 0) || (this->currentFrame > this->mdl.header.num_frames))
    return;
  // Clear the current batch contents
  this->triangles.Reset();

  /* Add model to batch */
  //this->triangles.Begin(GL_TRIANGLES,(GLuint)mdl.header.num_tris * 3,1);

    /* Draw each triangle */
    for (i = 0; i < this->mdl.header.num_tris; ++i)
      {
	/* Draw each vertex */
	for (j = 0; j < 3; ++j)
	  {
	    pframe1 = &this->mdl.frames[this->currentFrame];
	    pframe2 = &this->mdl.frames[this->nextFrame];
	    pvert1 = &pframe1->verts[this->mdl.triangles[i].vertex[j]];
	    pvert2 = &pframe2->verts[this->mdl.triangles[i].vertex[j]];

	    /* Compute texture coordinates */
	    s = (GLfloat)this->mdl.texcoords[mdl.triangles[i].st[j]].s / this->mdl.header.skinwidth;
	    t = (GLfloat)this->mdl.texcoords[mdl.triangles[i].st[j]].t / this->mdl.header.skinheight;

	    /* Pass texture coordinates to batch */
		this->triangles.MultiTexCoord2f(0,s,t);

		/* Interpolate normals */
	    n_curr = anorms_table[pvert1->normalIndex];
	    n_next = anorms_table[pvert2->normalIndex];

	    norm[0] = n_curr[0] + interp * (n_next[0] - n_curr[0]);
	    norm[1] = n_curr[1] + interp * (n_next[1] - n_curr[1]);
	    norm[2] = n_curr[2] + interp * (n_next[2] - n_curr[2]);

		this->triangles.Normal3fv(norm);

	    /* Interpolate vertices */
		// Doing these scaling operations *every* refresh is *very* wasteful
		// Should do all the scaling calculations once only, when loading the file
	    v_curr[0] = pframe1->scale[0] * pvert1->v[0] + pframe1->translate[0];
	    v_curr[1] = pframe1->scale[1] * pvert1->v[1] + pframe1->translate[1];
	    v_curr[2] = pframe1->scale[2] * pvert1->v[2] + pframe1->translate[2];

	    v_next[0] = pframe2->scale[0] * pvert2->v[0] + pframe2->translate[0];
	    v_next[1] = pframe2->scale[1] * pvert2->v[1] + pframe2->translate[1];
	    v_next[2] = pframe2->scale[2] * pvert2->v[2] + pframe2->translate[2];

	    v[0] = v_curr[0] + interp * (v_next[0] - v_curr[0]);
	    v[1] = v_curr[1] + interp * (v_next[1] - v_curr[1]);
	    v[2] = v_curr[2] + interp * (v_next[2] - v_curr[2]);

		this->triangles.Vertex3fv(v);
	  }
    }
	this->triangles.End();
	this->triangles.Draw();
}

/**
 * Calculate the current frame in animation, based on
 * selected animation and current frame. If current frame
 * is not in selected animation sequence, new current frame
 * is start of animation sequence.
 * If interpolation is past 1.0, move current frame to next
 * and next frame = current frame + 1
 */
void GameModel::Animate (int animation, float dt)
{
	int start = animFrameList[animation * 2];
	int end =  animFrameList[animation * 2 + 1];
	if ((this->currentFrame < start) || (this->currentFrame > end))
	{
		this->currentFrame = start;
		this->nextFrame = start + 1;
	}
	this->interp += dt;
	if (this->interp >= 1.0f)
    {
		/* Move to next frame */
		this->interp = 0.0f;
		this->currentFrame = this->nextFrame;
		this->nextFrame++;

		if (this->nextFrame >= end+1)
		this->nextFrame = start;
    }
}