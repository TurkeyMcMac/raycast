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
  -f <FOV>                set the field of view in degrees. Defaults to 60.\n\
  -W <width>              set the screen width in characters. Defaults to the\n\
                          width of the terminal.\n\
  -H <height>             set the screen height in characters. Defaults to\n\
                          the height of the terminal.\n\
  -V <vanishing-distance> Set the vanishing distance in tiles. Defaults to 9.\n\
  -m <movement-rate>      Set the forward/backward movement per tick. The\n\
                          default is 0.05.\n\
  -r <rotation-rate>      Set the turn amount in degrees per tick. Defaults\n\
                          to 0.02.\n\
  -M <map-file-path>      Set the map to load and explore. This is required.\n\
  -h                      Print this help information and exit.\n\
  -v                      Print version information and exit.\n\
Controls: Use WASD to move forward and backward and to turn. Press q to quit.\n"
	;
	static const char version_fmt[] = "%s version 0.2.0\n";
	static const char optstring[] = 
		"f:" // FOV
		"W:" // screen width
		"H:" // screen height
		"V:" // vanishing distance
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
	draw->vanish_dist = 9.0;
	*trans = 0.05;
	*turn = 0.02;
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
		case 'V':
			draw->vanish_dist = atof(optarg);
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
