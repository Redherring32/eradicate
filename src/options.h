#ifndef OPTIONS_H_
#define OPTIONS_H_

struct joystick {
	int xmin, xmax;
	int ymin, ymax;
};

struct options {
	int xres, yres, bpp;
	int vol_master, vol_mus, vol_sfx;
	struct joystick jscal;
};

extern struct options opt;

int load_options(const char *fname);
int save_options(const char *fname);

#endif	/* OPTIONS_H_ */
