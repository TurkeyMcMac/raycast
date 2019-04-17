#include "cast_ray.h"
#include <math.h>

char cast_ray(const struct map *map,
	const struct vec *posp,
	const struct vec *dposp,
	double *len)
{
	struct vec pos, dpos;	
	const char *tile;
	pos = *posp;
	dpos = *dposp;
	while ((tile = cmget(map, pos.x, pos.y))) {
		struct vec tonext = {INFINITY, INFINITY};
		if (*tile != ' ') {
			pos.x -= posp->x;
			pos.y -= posp->y;
			*len = vec_len(&pos);
			return *tile;
		}
		if (dpos.x < 0.0) {
			tonext.x = -fmod(pos.x, 1.0);
		} else if (dpos.x > 0.0) {
			tonext.x = 1.0 - fmod(pos.x, 1.0);
		}
		if (dpos.y < 0.0) {
			tonext.y = -fmod(pos.y, 1.0);
		} else if (dpos.y > 0.0) {
			tonext.y = 1.0 - fmod(pos.y, 1.0);
		}
		if (tonext.x / dpos.x < tonext.y / dpos.y) {
			pos.x += tonext.x + copysign(0.001, dpos.x);
			pos.y += tonext.x / dpos.x * dpos.y;
		} else {
			pos.y += tonext.y + copysign(0.001, dpos.y);
			pos.x += tonext.y / dpos.y * dpos.x;
		}
	}
	*len = INFINITY;
	return ' ';
}
