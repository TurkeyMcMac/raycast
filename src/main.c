#include "draw_frame.h"
#include "options.h"
#include "read_map.h"
#include <curses.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	struct draw_info info;
	double trans, turn;
	char *map_path;
	FILE *mapfile;
	struct vec pos, dpos;
	struct map map;
	const char *err;
	options(&info, &trans, &turn, &map_path, argc, argv);
	if (!(mapfile = fopen(map_path, "r"))) {
		err = strerror(errno);
		goto error;
	}
	if ((err = read_map(&map, &pos, mapfile))) goto error;
	dpos.x = trans;
	dpos.y = 0.0;
	initscr();
	for (;;) {
		struct vec oldpos = pos;
		const char *here;
		draw_frame(&info, &map, &pos, &dpos);
		refresh();
		switch (getch()) {
		case 'w':
			pos.x += dpos.x;
			pos.y += dpos.y;
			break;
		case 'a':
			vec_rotate(&dpos, -turn);
			continue;
		case 's':
			pos.x -= dpos.x;
			pos.y -= dpos.y;
			break;
		case 'd':
			vec_rotate(&dpos, +turn);
			continue;
		case 'q':
			goto end;
		default:
			continue;
		}
		here = cmget(&map, pos.x, pos.y);
		if (!here || *here != ' ') {
			pos = oldpos;
		}
	}
end:
	endwin();
	exit(0);

error:
	fprintf(stderr, "Error: %s\n", err);
	exit(EXIT_FAILURE);
}
