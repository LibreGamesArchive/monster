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

#include "monster.h"

BattleStats* Combatant::getBaseStats()
{
	return &baseStats;
}


BattleStats* Combatant::getModifiedStats()
{
	modifiedStats.hp = baseStats.hp;
	modifiedStats.maxHP = baseStats.maxHP;
	modifiedStats.latency = baseStats.latency;
	modifiedStats.turnReadyCount = baseStats.turnReadyCount;
	modifiedStats.turnCount = baseStats.turnCount;
	modifiedStats.experience = baseStats.experience;
	modifiedStats.mana = baseStats.mana;
	modifiedStats.maxMana = baseStats.maxMana;

	std::list<BattleAffect*>::iterator it = baseStats.affects.begin();

	while (it != baseStats.affects.end()) {
		BattleAffect* ba = *it;
		ba->apply(&modifiedStats);
		it++;
	}

	return &modifiedStats;
}

char* Combatant::getName()
{
	return name;
}

void Combatant::setNumber(int number)
{
	this->number = number;
}

int Combatant::getNumber()
{
	return number;
}

int Combatant::getX()
{
	return x;
}

int Combatant::getY()
{
	return y;
}

bool Combatant::showStatusDetails()
{
	return statusDetails;
}

void Combatant::setShowStatusDetails(bool details)
{
	statusDetails = details;
}

void Combatant::setSubAnimation(char* name)
{
	animSet->setSubAnimation(name);
}

int Combatant::getWidth()
{
	return width;
}

int Combatant::getHeight()
{
	return height;
}

int Combatant::getShadowOffset()
{
	return shadowOffset;
}

int Combatant::getShadowHeight()
{
	return shadowHeight;
}

void Combatant::update(int step)
{
	std::list<BattleAffect*>::iterator it = baseStats.affects.begin();

	while (it != baseStats.affects.end()) {
		BattleAffect* ba = *it;
		ba->update(step);
		it++;
	}
}

Combatant::Combatant(const char* name, int x, int y) :
	name(strdup(name)),
	x(x),
	y(y),
	statusDetails(true)
{
	baseStats.turnReadyCount = 0;
	baseStats.turnCount = 0;
}

Combatant::~Combatant()
{
	free(name);
	delete animSet;
}
