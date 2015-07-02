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

#ifndef _SPELL_H
#define _SPELL_H

struct BattleStats;

const int MAX_SPELLS = 64;

class SpellTarget
{
public:
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	bool getTowardsLeft();
	SpellTarget(int x, int y, int w, int h, bool towardsLeft);
private:
	/* Where the effect is targetting */
	int x; /* center */
	int y; /* center */
	int w;
	int h;
	bool towardsLeft;
};

class Spell
{
public:
	char* getName();
	bool isForBattleOnly();
	int getCost();
	bool affectsAll();
	bool noResults();
	/*
	 * A spell that produces no "results" must not use anything
	 * passed in to apply, they will all be NULL.
	 */
	virtual char* apply(PlayerStats* ps, BattleStats* bs, int defense, bool& isDamage, bool targetIsPlayer) = 0;
	/*
	 * Update animation
	 * Return true when finished
	 */
	virtual bool update(int step) = 0;
	virtual void draw(BITMAP* buffer) = 0;
	virtual void init(std::vector<SpellTarget*>& targets) = 0;
	Spell(char* name);
	virtual ~Spell();
protected:
	static char resultsBuffer[32];
	char* name;
	bool battleOnly;
	int cost;
	bool _affectsAll;
	bool _noResults;
};

extern void initSpells();
extern void destroySpells();
extern Spell* findSpell(char* name);
extern bool spellIsForBattleOnly(char* name);
extern int getSpellCost(char *name);
extern void setSpellMilestone(char *spellName);

#endif
