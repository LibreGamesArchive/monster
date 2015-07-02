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

#ifndef INPUT_H
#define INPUT_H

enum InputType {
	INPUT_KEYBOARD = 0,
	INPUT_GAMEPAD
};

enum Direction {
	DIRECTION_NORTH = 0,
	DIRECTION_EAST,
	DIRECTION_SOUTH,
	DIRECTION_WEST
};

struct InputDescriptor {
	bool left;
	bool right;
	bool up;
	bool down;
	bool button1;
	bool button2;
	Direction direction;
};

class Input {
public:
	void set(bool l, bool r, bool u, bool d);
	void set(bool b1, bool b2);
	void set(bool l, bool r, bool u, bool d, bool b1, bool b2);
	virtual void update() = 0; 
	InputDescriptor* getDescriptor();
	void setDirection(Direction direction);
	bool isPlayerControlled() { return playerControlled; }
	Input();
	virtual ~Input() {}
protected:
	InputDescriptor descriptor;
	bool playerControlled;
};

class KeyboardInput : public Input {
public:
	void update();
	KeyboardInput() { playerControlled = true; }
	~KeyboardInput() {}
};

class GamepadInput : public Input {
public:
	void update();
	GamepadInput() { playerControlled = true; }
	~GamepadInput() {}
};

class ScriptInput : public Input {
public:
    ScriptInput() { playerControlled = false; }
    void update() {}
};

extern void gamepad2Keypresses(int step);
extern Input* createInput(InputType type);
extern bool escapePressed();
extern void handleSpecialKeys();
extern void waitForRelease();

#endif
