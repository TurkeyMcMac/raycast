#include "draw_frame.h"
#include "read_map.h"
#include <curses.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define FOV 0.80
#define N_RAYS 120
#define MOVEMENT 0.05
#define ROTATION 0.02

int main(void)
{
	struct draw_info info = {
		.fov = FOV,
		.n_rays = N_RAYS,
		.vanish_dist = 10.0,
		.height = 40
	};
	FILE *mapfile;
	struct vec pos, dpos;
	struct map map;
	const char *err;
	if (!(mapfile = fopen("example", "r"))) {
		err = strerror(errno);
		goto error;
	}
	if ((err = read_map(&map, &pos, mapfile))) goto error;
	dpos.x = MOVEMENT;
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
			vec_rotate(&dpos, -ROTATION);
			continue;
		case 's':
			pos.x -= dpos.x;
			pos.y -= dpos.y;
			break;
		case 'd':
			vec_rotate(&dpos, +ROTATION);
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
