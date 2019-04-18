#include "options.h"
#include <curses.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void options(struct draw_info *draw, double *trans, double *turn, char **map,
	int argc, char *argv[])
{
	static const char help_fmt[] = "\
Explore a grid of text in pseudo-3D.\n\
Usage: %s [options]\n\
Options:\n\
  -f <FOV>           Set the field of view in degrees. Defaults to 60.\n\
  -W <width>         Set the screen width in characters. Defaults to the\n\
                     width of the terminal.\n\
  -H <height>        Set the screen height in characters. Defaults to the\n\
                     height of the terminal.\n\
  -w <wall-half>     Set the point where walls take up half the height of the\n\
                     screen. Defaults to 6.\n\
  -m <movement-rate> Set the forward/backward movement per tick. The default\n\
                     is 0.2.\n\
  -r <rotation-rate> Set the turn amount in degrees per tick. Default is 4.5.\n\
  -M <map-file-path> Set the map to load and explore. This is required.\n\
  -h                 Print this help information and exit.\n\
  -v                 Print version information and exit.\n\
Controls: Use WASD to move forward and backward and to turn. Press q to quit.\n"
	;
	static const char version_fmt[] = "%s version 0.3.2\n";
	static const char optstring[] = 
		"f:" // FOV
		"W:" // screen width
		"H:" // screen height
		"w:" // wall half
		"m:" // translation rate
		"r:" // turn rate
		"M:" // map file path
		"h"  // help info
		"v"  // version info
	;
	int o;
	draw->fov = M_PI / 2.0;
	if (isatty(STDOUT_FILENO)) {
		initscr();
		draw->n_rays = COLS;
		draw->height = LINES;
		endwin();
	} else {
		draw->n_rays = 0;
		draw->height = 0;
	}
	draw->wall_half = 6.0;
	*trans = 0.2;
	*turn = 4.5 / 180.0 * M_PI;
	*map = NULL;
	while ((o = getopt(argc, argv, optstring)) != -1) {
		switch (o) {
		case 'f':
			draw->fov = atof(optarg) / 180.0 * M_PI;
			break;
		case 'W':
			draw->n_rays = atoi(optarg);
			break;
		case 'H':
			draw->height = atoi(optarg);
			break;
		case 'w':
			draw->wall_half = atof(optarg);
			break;
		case 'm':
			*trans = atof(optarg);
			break;
		case 'r':
			*turn = atof(optarg);
			break;
		case 'M':
			*map = optarg;
			break;
		case 'h':
			printf(help_fmt, argv[0]);
			exit(0);
		case 'v':
			printf(version_fmt, argv[0]);
			exit(0);
		default:
			fprintf(stderr, help_fmt, argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	if (!*map) {
		fprintf(stderr, "%s: No map file specified\n", argv[0]);
		exit(EXIT_FAILURE);
	}
}
