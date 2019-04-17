#ifndef MAP_H_
#define MAP_H_

struct map {
	int width, height;
	char *tiles;
};

char *mget(struct map *map, int x, int y);

const char *cmget(const struct map *map, int x, int y);

#endif /* MAP_H_ */
