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

#ifndef AREA_H
#define AREA_H

#include <new>
#include <vector>

extern "C" {
#include <lua.h>
}

#include "object.h"
#include "util.h"

const int TILE_SIZE = 16;
const int TILE_FRAMES = 2;
/*
 * Delay between frames for animated tiles.
 */
const int TILE_DELAY = 333;
const int TILE_LAYERS = 3;

struct Tile {
	int anims[TILE_LAYERS];		// -1 for none
	bool solid;
};

enum TransitionType {
	TRANSITION_FADE = 1,
	TRANSITION_SCROLL_N = 2,
	TRANSITION_SCROLL_E = 3,
	TRANSITION_SCROLL_S = 4,
	TRANSITION_SCROLL_W = 5
};

extern TransitionType transitionType;

class Area {
public:
	static const int MAX_AREA_NAME = 256;
	static const int WIDTH = 20;
	static const int HEIGHT = 15;
	static const int MAX_ANIMATED_TILES_FOR_DIRTY_RECTANGLES = (WIDTH * HEIGHT) / 5;
	void updateDirty(unsigned int objNum);
	void update(int step);
	void draw(BITMAP* bmp);
	void drawSurrounding(BITMAP* dest, int layer, int tx, int ty, int n);
	void drawDirty(BITMAP* bmp);
	Tile* getTile(int x, int y);
	void writeTile(int tile, PACKFILE* f) throw (WriteError);
	Tile* loadTile(PACKFILE* f);
	void save(char* filename) throw (WriteError);
	void calcTilePositions();
	void sortObjects(int beg, int end);
	void addObject(Object* obj) throw (std::bad_alloc);
	void removeObject(int n);
	Object* getObject(int i);
	bool checkCollision(Object* o, int x, int y, BoundingBox* box);
	void initLua() throw (std::bad_alloc, ReadError, ScriptError);
	char* getName();
	std::vector<Object*>* getObjects();
	bool tileIsAnimated(int x, int y);
	void activate(unsigned int objNum, Direction direction);
	bool alreadyCollided(int o1, int o2);
	lua_State* getLuaState();
	Area(const char* filename) throw (std::bad_alloc, ReadError);
#ifdef EDITOR
	Area() throw (std::bad_alloc);	// create empty area for editor
#endif
	~Area();
private:
	void load() throw (std::bad_alloc, ReadError);
	char name[MAX_AREA_NAME];
	Tile** tiles;
	Point tilePos[WIDTH][HEIGHT];
	/*
	 * Object 0 is always the player.
	 */
	std::vector<Object*> objects;
	std::vector<Object*> sObjects;	// sorted objects
	lua_State* luaState;
	std::vector<Point*> collisions;
	bool oldDirtyRectanglesState;
};

extern Area* currArea;
extern Area* oldArea;
extern int numTiles;
extern char* prevAreaName;

extern void loadTileAnimations() throw (std::bad_alloc, ReadError);
extern void destroyTileAnimations();
extern Animation* getTile(int n);
extern void startArea(const char* name);

#endif
