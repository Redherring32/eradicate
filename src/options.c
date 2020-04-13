#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "options.h"
#include "treestor.h"

#define DEF_XRES	320
#define DEF_YRES	240
#define DEF_BPP		16
#define DEF_VOL		255
#define DEF_JS_MIN	0
#define DEF_JS_MAX	0

struct options opt = {
	DEF_XRES, DEF_YRES, DEF_BPP,
	DEF_VOL, DEF_VOL, DEF_VOL,
	{ DEF_JS_MIN, DEF_JS_MAX, DEF_JS_MIN, DEF_JS_MAX }
};

int load_options(const char *fname)
{
	struct ts_node *cfg;

	if(!(cfg = ts_load(fname))) {
		return -1;
	}
	printf("loaded config: %s\n", fname);

	opt.xres = ts_lookup_int(cfg, "options.gfx.xres", DEF_XRES);
	opt.yres = ts_lookup_int(cfg, "options.gfx.yres", DEF_YRES);
	opt.bpp = ts_lookup_int(cfg, "options.gfx.bpp", DEF_BPP);

	opt.vol_master = ts_lookup_int(cfg, "options.audio.master", DEF_VOL);
	opt.vol_mus = ts_lookup_int(cfg, "options.audio.music", DEF_VOL);
	opt.vol_sfx = ts_lookup_int(cfg, "options.audio.sfx", DEF_VOL);

	opt.jscal.xmin = ts_lookup_int(cfg, "options.joy.xmin", DEF_JS_MIN);
	opt.jscal.xmax = ts_lookup_int(cfg, "options.joy.xmax", DEF_JS_MAX);
	opt.jscal.ymin = ts_lookup_int(cfg, "options.joy.ymin", DEF_JS_MIN);
	opt.jscal.ymax = ts_lookup_int(cfg, "options.joy.ymax", DEF_JS_MAX);

	ts_free_tree(cfg);
	return 0;
}

#define WROPT(lvl, fmt, val, defval) \
	do { \
		int i; \
		for(i=0; i<lvl; i++) fputc('\t', fp); \
		if((val) == (defval)) fputc('#', fp); \
		fprintf(fp, fmt "\n", val); \
	} while(0)

int save_options(const char *fname)
{
	FILE *fp;

	printf("writing config: %s\n", fname);

	if(!(fp = fopen(fname, "wb"))) {
		fprintf(stderr, "failed to save options (%s): %s\n", fname, strerror(errno));
	}
	fprintf(fp, "options {\n");
	fprintf(fp, "\tgfx {\n");
	WROPT(2, "xres = %d", opt.xres, DEF_XRES);
	WROPT(2, "yres = %d", opt.yres, DEF_YRES);
	WROPT(2, "bpp = %d", opt.bpp, DEF_BPP);
	fprintf(fp, "\t}\n");

	fprintf(fp, "\taudio {\n");
	WROPT(2, "master = %d", opt.vol_master, DEF_VOL);
	WROPT(2, "music = %d", opt.vol_mus, DEF_VOL);
	WROPT(2, "sfx = %d", opt.vol_sfx, DEF_VOL);
	fprintf(fp, "\t}\n");

	fprintf(fp, "\tjoy {\n");
	WROPT(2, "xmin = %d", opt.jscal.xmin, DEF_JS_MIN);
	WROPT(2, "xmax = %d", opt.jscal.xmax, DEF_JS_MAX);
	WROPT(2, "ymin = %d", opt.jscal.ymin, DEF_JS_MIN);
	WROPT(2, "ymax = %d", opt.jscal.ymax, DEF_JS_MAX);
	fprintf(fp, "\t}\n");

	fprintf(fp, "}\n");
	fprintf(fp, "# vi:ts=4 sts=4 sw=4 noexpandtab:\n");

	fclose(fp);
	return 0;
}
