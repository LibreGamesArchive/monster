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

#ifndef CONFIG_H
#define CONFIG_H

#include "graphics.h"
#include "input.h"

const int NUM_BATTLE_SPEEDS = 2;

class Configuration {
public:
	ScreenDescriptor* getWantedGraphicsMode();
	void setWantedGraphicsMode(ScreenDescriptor& sd);
	InputType getInputType();
	void setInputType(InputType it);
	bool showDebugMessages();
	bool useCompiledScripts();
	unsigned int getFrameSkip();
	void setFrameSkip(unsigned int frameSkip);
	bool getWaitForVsync();
	void setWaitForVsync(bool vs);
	//void setNoGamepadAvailable();
	//void setGamepadAvailable();
	bool getGamepadAvailable();
	bool useSmoothScaling();
	void setUseSmoothScaling(bool smooth);
	bool useDirtyRectangles();
	void setUseDirtyRectangles(bool dirty);
	int getBattleSpeed();
	void setBattleSpeed(int speed);
	int getSFXVolume();
	void setSFXVolume(int volume);
	int getMusicVolume();
	void setMusicVolume(int volume);
	int getJoyButton1();
	void setJoyButton1(int b1);
	int getJoyButton2();
	void setJoyButton2(int b2);
	int getJoyButton3();
	void setJoyButton3(int b3);
	int getKey1(void);
	void setKey1(int k1);
	int getKey2(void);
	void setKey2(int k2);
	int getKeyLeft(void);
	void setKeyLeft(int kl);
	int getKeyRight(void);
	void setKeyRight(int kr);
	int getKeyUp(void);
	void setKeyUp(int ku);
	int getKeyDown(void);
	void setKeyDown(int kd);
	void read() throw (ReadError);
	void write() throw (WriteError);
	Configuration();
private:
	InputType inputType;		// keyboard or gamepad
	ScreenDescriptor wantedMode;	// wanted screen resolution & depth
	bool debugMessages;		// show debugging messages?
	bool compiledScripts;		// use compiled scripts?
	unsigned int frameSkip;
	bool waitForVsync;
	bool loaded;	// loaded from file or default?
	bool gamepadAvailable;
	bool smoothScaling;
	bool dirtyRectangles;
	int battleSpeed;
	int sfxVolume;
	int musicVolume;
	int joyB1;
	int joyB2;
	int joyB3;
	int key1;
	int key2;
	int keyLeft;
	int keyRight;
	int keyUp;
	int keyDown;
};

extern Configuration config;

extern bool configurate();
extern char* getConfigFilename();

#endif
