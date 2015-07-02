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
#include <cstring>
#include <allegro.h>

#include "io.h"

int main(int argc, char** argv)
{
	if (argc < 5) {
		printf("Usage: mkanimset <out.anims> <name> <numanims> <file.anim ...>\n");
		return 1;
	}

	int numAnims = atoi(argv[3]);

	if (numAnims < 1) {
		printf("Error: numframes < 1.\n");
		return 1;
	}
	if (argc < (4 + numAnims)) {
		printf("Error: too few arguments.\n");
		return 1;
	}

	allegro_init();

	PACKFILE* f = pack_fopen(argv[1], "wp");
	if (!f) {
		printf("Error: couldn't open %s for writing.\n", argv[1]);
		return 1;
	}

	iputl(strlen(argv[2]), f);
	for (int i = 0; i < strlen(argv[2]); i++)
		pack_putc(argv[2][i], f);

	iputl(numAnims, f);

	for (int i = 0; i < numAnims; i++) {
		PACKFILE* in = pack_fopen(argv[4+i], "rp");
		int c;
		while ((c = pack_getc(in)) != EOF)
			pack_putc(c, f);
		pack_fclose(in);
	}

	pack_fclose(f);

	return 0;
}
END_OF_MAIN()
