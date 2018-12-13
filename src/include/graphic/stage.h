#ifndef __GRAPHIC_STAGE_H__
#define __GRAPHIC_STAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <cairo-xboot.h>
#include <xfs/xfs.h>
#include <framebuffer/framebuffer.h>
#include <graphic/dobject.h>

struct stage_t
{
	struct dobject_t o;
	struct xfs_context_t * xfs;
	struct framebuffer_t * fb;
	cairo_surface_t * cs;
	cairo_t * cr;
};

struct stage_t * stage_alloc(const char * path, const char * fb);
void stage_free(struct stage_t * s);

#ifdef __cplusplus
}
#endif

#endif /* __GRAPHIC_STAGE_H__ */
