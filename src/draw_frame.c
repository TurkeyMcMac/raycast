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
		int y, padding, wall_height;
		struct vec dpos = *dposp;
		vec_rotate(&dpos, info->fov * ((double)i / info->n_rays - 0.5));
		wall = cast_ray(map, pos, &dpos, &len);
		wall_height = info->wall_half / len * info->height / 2; 
		if (wall_height < 0 || wall_height > info->height)
			wall_height = info->height;
		padding = (info->height - wall_height) / 2;
		for (y = 0; y < padding; ++y) {
			mvaddch(y, i, ' ');
		}
		for (; y < info->height - padding; ++y) {
			mvaddch(y, i, wall);
		}
	}
}
