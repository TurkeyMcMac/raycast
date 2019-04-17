#ifndef READ_FILE_H_
#define READ_FILE_H_

#include "map.h"
#include "vec.h"
#include <stddef.h>
#include <stdio.h>

const char *read_map(struct map *map, struct vec *player_pos, FILE *from);

#endif /* READ_FILE_H_ */
