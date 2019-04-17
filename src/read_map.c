#include "read_map.h"
#include <stdlib.h>
#include <string.h>

static void expand(char **tiles, size_t len, size_t *cap)
{
	if (len > *cap) {
		*cap = len + len / 2;
		*tiles = realloc(*tiles, *cap);
	}
}

const char *read_map(struct map *map, struct vec *player_pos, FILE *from)
{
	int player_found = 0;
	size_t map_cap = 0;
	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;
	map->height = 0;
	map->width = -1;
	while ((linelen = getline(&line, &linecap, from)) > 0) {
		char *player;
		if (line[linelen - 1] == '\n') --linelen;
		if (map->width < 0) {
			map->width = linelen;
			map_cap = map->width * map->width;
			map->tiles = malloc(map_cap);
		} else if (map->width != linelen) {
			return "Inconsistent map row width";
		}
		player = strchr(line, 'P');
		if (player) {
			if (player_found) return "Duplicate player positions.";
			player_found = 1;
			player_pos->x = player - line;
			player_pos->y = map->height;
			*player = ' ';
		}
		++map->height;
		expand(&map->tiles, map->width * map->height, &map_cap);
		memcpy(mget(map, 0, map->height - 1), line, map->width);
	}
	free(line);
	if (linelen < 0 && !feof(from)) return "File reading error";
	if (!player_found) return "No player position in map";
	player_pos->x += 0.5;
	player_pos->y += 0.5;
	return NULL;
}
