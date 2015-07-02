/*
 * Copyright (c) 2007, Trent Gamblin
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ANIM_H
#define ANIM_H

#include <new>

#include <allegro.h>

#include "error.h"

class Animation {
public:
	char* getName();
	int getFrame();
	void setFrame(int frame);
	int getNumFrames();
	int getDelay(int frame);
	void draw(BITMAP* bmp, int x, int y);
	void drawTrans(BITMAP* bmp, int x, int y);
	void saveFrame(BITMAP* bmp, int delay, PACKFILE* f) throw (WriteError);
	void save(PACKFILE* f) throw (WriteError);
	void loadFrame(int w, int h, BITMAP* dest, int* delay, PACKFILE* f)
		throw (ReadError);
	void load(PACKFILE* f) throw (std::bad_alloc, ReadError);
	void load(char  *filename) throw (std::bad_alloc, ReadError);
	void advance();
	bool update(int step);
	void reset();
	BITMAP* getBitmap(int frame);
	BITMAP* getCurrentBitmap();
	Animation(char* name, int numFrames, BITMAP** frames, int* delays)
		throw (std::bad_alloc);
	Animation();	// does no initialization (for loading)
	~Animation();
private:
	char* name;
	BITMAP** frames;
	/*
	 * Delay between each frame of the animation
	 */
	int* delays;
	int count;	// how long before changing frames?
	int numFrames;
	int currFrame;
};

class AnimationSet {
public:
	void setSubAnimation(int anim);
	bool setSubAnimation(const char* subName);
	void setFrame(int frame);
	int getFrame();
	void draw(BITMAP* dest, int x, int y);
	bool update(int step);
	Animation* getCurrentAnimation();
	AnimationSet(const char* filename) throw (std::bad_alloc, ReadError);
	~AnimationSet();
private:
	char* name;
	Animation** anims;
	int currAnim;
	int numAnims;
};

#endif
