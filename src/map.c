#include "map.h"
#include <math.h>
#include <stddef.h>

char *mget(struct map *map, int x, int y)
{
	return x >= 0 && x < map->width && y >= 0 &&  y < map->height ?
		&map->tiles[y * map->width + x] : NULL;
}

const char *cmget(const struct map *map, int x, int y)
{
	return mget((struct map *)map, x, y);
}

char *mpos(struct map *map, const struct vec *pos)
{
	return mget(map, floor(pos->x), floor(pos->y));
}

const char *cmpos(const struct map *map, const struct vec *pos)
{
	return mpos((struct map *)map, pos);
}
