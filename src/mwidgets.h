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

#ifndef AWIDGETS_H
#define AWIDGETS_H

#include <vector>
#include <string>

#include <TGUI/tgui.h>

#include "monster.h"

extern FONT* tinyfont;
extern bool useBitmapFont;

extern int mWgtFontHeight();
extern int mWgtTextWidth(const char* text);
extern void mWgtInit() throw (std::bad_alloc);
extern void mWgtShutdown();
extern int mWgtInterpolateColor(float ratio, int color1, int color2);
extern int mWgtDarken(int color);
extern int mWgtHighlight(int color);
extern void mWgtSet(int property, void* value);
extern void mWgtTextout(BITMAP* bmp, FONT* font, char* text, int x, int y,
		int textColor, int shadowColor, int shadowType);
extern void mPrintf(BITMAP* bmp, int x, int y, int fore, int back, bool center,
		bool shadow, const char* fmt, ...);
extern void drawFrame(BITMAP* bmp, int x, int y, int width, int height,
		int color, int alpha);

class MWidget : public TGUIWidget {
public:
	bool pointOnWidget(int x, int y);
};

class MWgtFrame : public MWidget {
public:
	int getColor();
	void draw();
	MWgtFrame(int x, int y, int width, int height, int color,
			int alpha);
	~MWgtFrame();
protected:
	int color;
	int alpha;
};

class MWgtButton : public MWidget {
public:
	void draw();
	int update(int step);
	bool handleKey(int key);
	bool acceptsFocus();
	MWgtButton(int x, int y, int width, char* text);
	~MWgtButton();
protected:
	char* text;
	bool pressed;
};

class MWgtText : public MWidget {
public:
	void setColor(int color);
	void draw();
	void setText(const char *text);
	MWgtText(int x, int y, const char* text, int color);
protected:
	const char* text;
	int color;
};


class MWgtCheckbox : public MWidget {
public:
	bool isChecked();
	void setChecked(bool checked);
	void draw();
	bool handleKey(int key);
	bool acceptsFocus();
	MWgtCheckbox(int x, int y, char* text);
	~MWgtCheckbox();
protected:
	char* text;
	bool checked;
};

class MWgtOption : public MWidget {
public:
	unsigned int getSelected();
	void setSelected(unsigned int selected);
	void draw();
	bool handleKey(int key);
	bool acceptsFocus();
	MWgtOption(int x, int y, int width, std::vector<char*>* options);
	~MWgtOption();
protected:
	int findWidth();
	std::vector<char*>* options;
	unsigned int selected;
};

class MWgtSlider : public MWidget {
public:
	int getStop();
	void setStop(int stop);
	void draw();
	bool handleKey(int key);
	bool acceptsFocus();
	MWgtSlider(int x, int y, int width, int numStops);
	~MWgtSlider();
protected:
	int getStopPos(int stop);
	int numStops;
	int currStop;
};

class MWgtIcon : public MWidget {
public:
	void draw();
	int update(int step);
	bool handleKey(int key);
	bool acceptsFocus();
	MWgtIcon(int x, int y, BITMAP* unselected, BITMAP* selected,
			bool selectable);
	~MWgtIcon();
protected:
	bool pressed;
	BITMAP* unselected;
	BITMAP* selected;
	bool selectable;
};

class MWgtSpeech : public MWidget {
public:
	// If already at a stop, move past
	// Otherwise advance to the next stop immediately
	bool advance();
	// true if at end of block
	bool atStop();
	int getMaxLines();
	void draw();
	int update(int step);
	MWgtSpeech(int x, int y, int width, const char* text);
	~MWgtSpeech();
protected:
	int currChar;
	int startChar;
	const char* text;
	int count;
	int maxLines;
};

class MWgtAdvancer : public MWidget {
public:
	void draw();
	bool handleKey(int key);
	MWgtAdvancer(int x, int y, MWgtSpeech* target);
protected:
	MWgtSpeech* target;
};

class MWgtTextButton : public MWidget {
public:
	void draw();
	int update(int step);
	bool handleKey(int key);
	bool acceptsFocus();
	MWgtTextButton(int x, int y, char* text);
	~MWgtTextButton();
protected:
	char* text;
	bool pressed;
};

class MWgtInventory : public MWidget {
public:
	void draw();
	int update(int step);
	bool handleKey(int k);
	bool acceptsFocus();
	void getPressed(int* p1, int *p2);
	int getSelected();
	int getHead();
	MWgtInventory(int x, int y, int width, int columns, int rows,
		bool arrange, int selected, int head, struct Item* inventory);
	~MWgtInventory();
protected:
	int columns;
	int rows;
	bool arrange;
	int head;
	bool done;
	Item* inventory;
	int selected;
	int pressed1;
	int pressed2;
};

class MWgtSelector : public MWidget {
public:
	int getPosition();
	void setPosition(int newpos);
	int update(int step);
	void draw();
	bool handleKey(int k);
	MWgtSelector(std::vector<Point*>* positions, bool left, bool blink);
	~MWgtSelector();
protected:
	std::vector<Point*>* positions;
	bool left;
	int position;
	bool done;
	bool blink;
};

class MWgtSpellSelector : public MWidget {
public:
	void draw();
	int update(int step);
	bool handleKey(int k);
	bool acceptsFocus();
	void getPressed(int* p1, int *p2);
	int getSelected();
	int getHead();
	MWgtSpellSelector(int x, int y, int width, int columns, int rows,
		bool arrange, int selected, int head, char** spells);
	~MWgtSpellSelector();
protected:
	int columns;
	int rows;
	bool arrange;
	int head;
	bool done;
	char** spells;
	int selected;
	int pressed1;
	int pressed2;
};

class MWgtTabs : public MWidget {
public:
	static const int PADDING = 16;
	int getColor();
	void draw();
	bool handleKey(int key);
	bool acceptsFocus();
	void focusCurrentTab();
	MWgtTabs(int x, int y, int color, int alpha,
		       std::vector<std::string>& tabNames,
		       std::vector<MWgtFrame*>& frames);
	~MWgtTabs();
protected:
	int findWidth();
	int findHeight();
	int color;
	int alpha;
	std::vector<std::string> tabNames;
	std::vector<MWgtFrame*> frames;
	unsigned int currTab;
};

#endif
