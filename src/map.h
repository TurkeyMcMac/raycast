#ifndef MAP_H_
#define MAP_H_

#include "vec.h"

struct map {
	int width, height;
	char *tiles;
};

char *mget(struct map *map, int x, int y);

const char *cmget(const struct map *map, int x, int y);

char *mpos(struct map *map, const struct vec *pos);

const char *cmpos(const struct map *map, const struct vec *pos);

#endif /* MAP_H_ */
