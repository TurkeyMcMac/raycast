#include "draw_frame.h"
#include "cast_ray.h"
#include <curses.h>

void draw_frame(const struct draw_info *info,
	const struct map *map,
	const struct vec *pos,
	const struct vec *dposp)
{
	clear();
	for (int i = 0; i < info->n_rays; ++i) {
		double len;
		char wall;
		int y, padding;
		struct vec dpos = *dposp;
		vec_rotate(&dpos, info->fov * ((double)i / info->n_rays - 0.5));
		wall = cast_ray(map, pos, &dpos, &len);
		if (len > info->vanish_dist) continue;
		padding = len / info->vanish_dist * info->height;
		for (y = 0; y < padding; ++y) {
			mvaddch(y, i, ' ');
		}
		for (; y < info->height - padding; ++y) {
			mvaddch(y, i, wall);
		}
	}
}
