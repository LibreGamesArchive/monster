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

#ifndef IO_H
#define IO_H

#include <allegro.h>

#include "monster.h"

extern void iputl(long l, PACKFILE *f) throw (WriteError);
extern long igetl(PACKFILE *f) throw (ReadError);
extern void my_pack_putc(int c, PACKFILE* f) throw (WriteError);
extern int my_pack_getc(PACKFILE* f) throw (ReadError);
extern bool readMilestones(bool* ms, int num, PACKFILE* f);
extern bool WriteMilestones(bool* ms, int num, PACKFILE* f);
extern char* readString(PACKFILE* f) throw (ReadError);
extern void writeString(char* s, PACKFILE* f) throw (WriteError);
extern void readStats(struct PlayerStats* stats, PACKFILE* f) throw (ReadError);
extern void writeStats(struct PlayerStats* stats, PACKFILE* f) throw (WriteError);
extern void readItem(struct Item* item, PACKFILE* f) throw (ReadError);
extern void writeItem(struct Item* item, PACKFILE* f) throw (WriteError);
extern void saveGame(char* filename) throw (WriteError);
extern void loadGame(char* filename) throw (ReadError);

#endif
