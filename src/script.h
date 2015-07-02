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

#ifndef SCRIPTING_H
#define SCRIPTING_H

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "player.h"

const int ITEM_TYPE_ITEM = 0;
const int ITEM_TYPE_WEAPON = 1;
const int ITEM_TYPE_ARMOR = 2;
const int ITEM_TYPE_SPECIAL = 3;

extern void openLuaLibs(lua_State* state);
extern void initGame() throw (ReadError, ScriptError);
extern void callLua(lua_State* luaState, const char *func, const char *sig, ...);
extern void dumpLuaStack(lua_State* stack);
extern void registerCFunctions(lua_State* luaState);
extern char* getItemName(int id);
extern int getItemType(int id);
extern int getWeaponPower(int id);
extern int getArmorDefense(int id);
extern ItemEffects* getItemEffects(int itemNum);
extern char* getItemSound(int id);
extern void deleteItemEffects(ItemEffects* ie);
extern bool itemAffectsAll(int itemID);
void getItemDescription(int id, char *s1, char *s2, char *s3, int bufsize);

extern int accumulated_distance;
extern bool playerScripted;
extern bool battlesDisabled;

#endif
