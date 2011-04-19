#pragma once

#ifndef ENUMS_H
#define ENUMS_H

const long double PI = 3.1415926535897932384626433832795028841968;
const int SKYBOX_SIDES = 6;
const float SCALE = 20.0f;
const int FRAMERATE = 40;

//	earth standard average gravity, yes there are problems with the internal usage of this
const double GRAVITY = -9.80665;		// with 000000000006 thrown in after it by a rubbish fpu

//	are we in debug mode?
const bool Dbg = false;			//	debug mode if this is true, normal mode if false

#endif