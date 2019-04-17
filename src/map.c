#include "map.h"
#include <stddef.h>

char *mget(struct map *map, int x, int y)
{
	return x >= 0 && x < map->width && y >= 0 &&  y < map->height ?
		&map->tiles[y * map->width + x] : NULL;
}

const char *cmget(const struct map *map, int x, int y)
{
//	printf("(%d, %d)\n", x, y);
	return mget((struct map *)map, x, y);
}
