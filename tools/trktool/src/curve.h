#ifndef CURVE_H_
#define CURVE_H_

#include "cgmath.h"

enum curve_eval_mode {
	CURVE_CLAMP,
	CURVE_REPEAT,
	CURVE_EXTRAP
};

struct curve_cp {
	cgm_vec3 pos, t0, t1;
};

struct curve {
	struct curve_cp *cp;
	int num_cp;
	enum curve_eval_mode mode;
};

struct curve *load_curve(const char *fname);
void free_curve(struct curve *c);

void curve_bounds(struct curve *c, cgm_vec3 *bbmin, cgm_vec3 *bbmax);

int curve_segment(struct curve *c, float t, float *seg_t);
void eval_curve(struct curve *c, float t, cgm_vec3 *ret);
void eval_tangent(struct curve *c, float t, cgm_vec3 *ret);

#endif	/* CURVE_H_ */
