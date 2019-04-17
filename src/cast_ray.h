#ifndef CAST_RAY_H_
#define CAST_RAY_H_

#include "map.h"
#include "vec.h"

char cast_ray(const struct map *map,
	const struct vec *pos,
	const struct vec *dpos,
	double *len);

#endif /* CAST_RAY_H_ */
