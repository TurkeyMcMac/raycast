#ifndef DRAW_FRAME_H_
#define DRAW_FRAME_H_

#include "map.h"
#include "vec.h"

struct draw_info {
	double fov;
	int n_rays;
	double wall_half;
	int height;
};

void draw_frame(const struct draw_info *info,
	const struct map *map,
	const struct vec *pos,
	const struct vec *dposp);

#endif /* DRAW_FRAME_H_ */
