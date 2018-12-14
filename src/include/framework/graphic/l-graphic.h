#ifndef __FRAMEWORK_L_GRAPHIC_H__
#define __FRAMEWORK_L_GRAPHIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <cairo.h>
#include <framework/luahelper.h>

#define	MT_DOBJECT		"__mt_dobject__"
#define	MT_TEXTURE		"__mt_texture__"

struct ltexture_t {
	cairo_surface_t * surface;
};

int luaopen_dobject(lua_State * L);
int luaopen_texture(lua_State * L);

#ifdef __cplusplus
}
#endif

#endif /* __FRAMEWORK_L_GRAPHIC_H__ */
