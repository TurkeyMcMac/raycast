#include "vec.h"
#include <math.h>

void vec_rotate(struct vec *vec, double rads)
{
	double x = vec->x;
	double s = sin(rads), c = cos(rads);
	vec->x = x * c - vec->y * s;
	vec->y = x * s + vec->y * c;
}

double vec_len(const struct vec *vec)
{
	return sqrt(vec->x * vec->x + vec->y * vec->y);
}
