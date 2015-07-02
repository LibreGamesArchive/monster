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

#include <cstdio>

#include <allegro.h>

#include "monster.h"

int main(int argc, char** argv)
{
	if (argc < 6) {
		printf("Usage: mkanim <out.anim> <name> <numframes> <bmpfile> <delay ...>\n");
		return 1;
	}

	int numFrames = atoi(argv[3]);

	if (numFrames < 1) {
		printf("Error: numframes < 1.\n");
		return 1;
	}
	if (argc < (5 + numFrames)) {
		printf("Error: Too few arguments.\n");
		return 1;
	}

	allegro_init();
	set_color_depth(32);

	BITMAP* bmp = load_bitmap(argv[4], 0);
	int width = bmp->w / numFrames;

	BITMAP** bmps = new BITMAP*[numFrames];
	int* delays = new int[numFrames];

	for (int i = 0; i < numFrames; i++) {
		bmps[i] = create_bitmap(width, bmp->h);
		blit(bmp, bmps[i], i*width, 0, 0, 0, width, bmp->h);
		delays[i] = atoi(argv[5+i]);
	}

	Animation* a = new Animation(argv[2], numFrames, bmps, delays);
	PACKFILE* f = pack_fopen(argv[1], "wp");
	a->save(f);
	pack_fclose(f);
	delete a;

	return 0;
}
END_OF_MAIN()
