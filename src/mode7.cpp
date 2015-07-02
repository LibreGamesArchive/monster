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

Mode7Params mode7Params = {
	itofix(10),
	1,
	itofix(512), itofix(512)
};

void mode_7(BITMAP *bmp, BITMAP *tile, fixed angle,
	fixed cx, fixed cy, Mode7Params& params)
{
    // current screen position
    int screen_x, screen_y;

    // the distance and horizontal scale of the line we are drawing
    fixed distance, horizontal_scale;

    // masks to make sure we don't read pixels outside the tile
    int mask_x = (tile->w - 1);
    int mask_y = (tile->h - 1);

    // step for points in space between two pixels on a horizontal line
    fixed line_dx, line_dy;

    // current space position
    fixed space_x, space_y;

    for (screen_y = 0; screen_y < bmp->h; screen_y++)
    {
        // first calculate the distance of the line we are drawing
        distance = fmul (params.space_z, params.scale_y) /
            (screen_y + params.horizon);
        // then calculate the horizontal scale, or the distance between
        // space points on this horizontal line
        horizontal_scale = fdiv (distance, params.scale_x);

        // calculate the dx and dy of points in space when we step
        // through all points on this line
        line_dx = fmul (-fsin(angle), horizontal_scale);
        line_dy = fmul (fcos(angle), horizontal_scale);

        // calculate the starting position
        space_x = cx + fmul (distance, fcos(angle)) - bmp->w/2 * line_dx;
        space_y = cy + fmul (distance, fsin(angle)) - bmp->w/2 * line_dy;

        // go through all points in this screen line
        for (screen_x = 0; screen_x < bmp->w; screen_x++)
        {
            // get a pixel from the tile and put it on the screen
            putpixel (bmp, screen_x, screen_y,
                getpixel (tile,
                    fixtoi (space_x) & mask_x,
                    fixtoi (space_y) & mask_y));
            // advance to the next position in space
            space_x += line_dx;
            space_y += line_dy;
        }
    }
}
