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

#ifndef OBJECT_H
#define OBJECT_H

#include "animation.h"
#include "input.h"
#include "collision.h"

enum ObjectType {
	OBJECT_NORMAL = 0,
	OBJECT_CHARACTER = 1
};

/*
 * These speeds correspond to pixels moved per millisecond.
 */
const float WALK_SPEED = 0.05f;
const int WALK_ANIM_DELAY = 800;
const int MIN_OBJECT_SIZE = 8;

class Area;

class Object {
public:
	void setAnimationSet(AnimationSet* anim_set);
	void setInput(Input* input);
	Input* getInput();
	void deleteInput();
	void draw(BITMAP* buf);
	void update(Area* area, int step);
	void updateAnimation(int step);
	int getX();	// get x/y as int
	int getY();
	float getFX();	// get x/y as float
	float getFY();
	bool isHigh();
	void setHigh(bool high);
	void setPosition(float x, float y);
	void setType(ObjectType type);
	void setWalkSpeed(float speed);
	void setDirection(Direction direction);
	Direction getDirection();
	void setHidden(bool hidden);
	bool isHidden();
	int getWidth();
	int getHeight();
	int getTotalHeight();
	void setTotalHeight(int th);
	void setSolid(bool solid);
	bool isSolid();
	void advanceAnimation();
	bool isAnimated();
	void setAnimated(bool animated);
	BoundingBox* getBoundingBox();
	void setAnimationFrame(int frame);
	void setSubAnimation(int sub);
	bool setSubAnimation(const char* name);
	/*
	 * Objects are created with their base on the
	 * highest point in the area on the tile where
	 * x,y falls.
	 */
	Object(int x, int y, int w, int base_h, int total_height);
	virtual ~Object();
protected:
	float x;
	float y;		// bottom (feet)
	/*
	 * The last known position where the object was
	 * on solid ground.
	 */
	float good_x;
	float good_y;
	float speed_xy;
	int totalHeight;
	BoundingBox base;
	AnimationSet* animSet;
	Input* input;
	bool high;
	ObjectType type;
	float walkSpeed;
	bool hidden;
	bool solid;
	bool animated;
};

extern Object* player;

#endif
