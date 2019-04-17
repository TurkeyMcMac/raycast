#ifndef VEC_H_
#define VEC_H_

struct vec {
	double x, y;
};

void vec_rotate(struct vec *vec, double rads);

double vec_len(const struct vec *vec);

#endif /* VEC_H_ */
