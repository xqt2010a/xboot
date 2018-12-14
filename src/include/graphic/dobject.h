#ifndef __GRAPHIC_DOBJECT_H__
#define __GRAPHIC_DOBJECT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <list.h>
#include <graphic/matrix.h>

struct dobject_t;
struct stage_t;

typedef void (*dobject_draw_t)(struct dobject_t * o, struct stage_t * s);

enum dobject_type_t {
	DOBJECT_TYPE_CONTAINER,
	DOBJECT_TYPE_NODE,
};

enum alignment_t {
	ALIGN_NONE				= 0,
	ALIGN_LEFT				= 1,
	ALIGN_TOP				= 2,
	ALIGN_RIGHT				= 3,
	ALIGN_BOTTOM			= 4,
	ALIGN_LEFT_TOP			= 5,
	ALIGN_RIGHT_TOP			= 6,
	ALIGN_LEFT_BOTTOM		= 7,
	ALIGN_RIGHT_BOTTOM		= 8,
	ALIGN_LEFT_CENTER		= 9,
	ALIGN_TOP_CENTER		= 10,
	ALIGN_RIGHT_CENTER		= 11,
	ALIGN_BOTTOM_CENTER		= 12,
	ALIGN_HORIZONTAL_CENTER	= 13,
	ALIGN_VERTICAL_CENTER	= 14,
	ALIGN_CENTER			= 15,
	ALIGN_LEFT_FILL			= 16,
	ALIGN_TOP_FILL			= 17,
	ALIGN_RIGHT_FILL		= 18,
	ALIGN_BOTTOM_FILL		= 19,
	ALIGN_HORIZONTAL_FILL	= 20,
	ALIGN_VERTICAL_FILL		= 21,
	ALIGN_CENTER_FILL		= 22,
};

enum {
	MFLAG_TRANSLATE		= (0x1 << 0),
	MFLAG_ROTATE		= (0x1 << 1),
	MFLAG_SCALE			= (0x1 << 2),
	MFLAG_ANCHOR		= (0x1 << 3),
	MFLAG_LOCAL_MATRIX	= (0x1 << 4),
};

struct dobject_t
{
	enum dobject_type_t type;
	struct dobject_t * parent;
	struct list_head entry;
	struct list_head children;

	double width, height;
	double x, y;
	double rotation;
	double scalex, scaley;
	double anchorx, anchory;
	double alpha;
	enum alignment_t alignment;
	int visible;
	int touchable;
	int mflag;
	struct matrix_t local_matrix;
	struct matrix_t global_matrix;

	void (*draw)(struct dobject_t * o, struct stage_t * s);
	void * priv;
};

bool_t dobject_init(struct dobject_t * o, enum dobject_type_t type, dobject_draw_t draw, void * priv);
bool_t dobject_add(struct dobject_t * parent, struct dobject_t * o);
bool_t dobject_remove(struct dobject_t * parent, struct dobject_t * o);
bool_t dobject_remove_self(struct dobject_t * o);
bool_t dobject_to_front(struct dobject_t * o);
bool_t dobject_to_back(struct dobject_t * o);

static inline void dobject_set_width(struct dobject_t * o, double w)
{
	o->width = w;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

static inline void dobject_set_height(struct dobject_t * o, double h)
{
	o->height = h;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

static inline void dobject_set_size(struct dobject_t * o, double w, double h)
{
	o->width = w;
	o->height = h;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

static inline void dobject_set_x(struct dobject_t * o, double x)
{
	o->x = x;
	if((o->x != 0.0) || (o->y != 0.0))
		o->mflag |= MFLAG_TRANSLATE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

static inline void dobject_set_y(struct dobject_t * o, double y)
{
	o->y = y;
	if((o->x != 0.0) || (o->y != 0.0))
		o->mflag |= MFLAG_TRANSLATE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

static inline void dobject_set_position(struct dobject_t * o, double x, double y)
{
	o->x = x;
	o->y = y;
	if((o->x != 0.0) || (o->y != 0.0))
		o->mflag |= MFLAG_TRANSLATE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

static inline void dobject_set_rotation(struct dobject_t * o, double r)
{
	o->rotation = r * (M_PI / 180.0);
	while(o->rotation < 0)
		o->rotation = o->rotation + (M_PI * 2);
	while(o->rotation > (M_PI * 2))
		o->rotation = o->rotation - (M_PI * 2);
	if(o->rotation != 0.0)
		o->mflag |= MFLAG_ROTATE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

static inline void dobject_set_scale_x(struct dobject_t * o, double x)
{
	o->scalex = x;
	if((o->scalex != 1.0) || (o->scaley != 1.0))
		o->mflag |= MFLAG_SCALE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

static inline void dobject_set_scale_y(struct dobject_t * o, double y)
{
	o->scaley = y;
	if((o->scalex != 1.0) || (o->scaley != 1.0))
		o->mflag |= MFLAG_SCALE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

static inline void dobject_set_scale(struct dobject_t * o, double x, double y)
{
	o->scalex = x;
	o->scaley = y;
	if((o->scalex != 1.0) || (o->scaley != 1.0))
		o->mflag |= MFLAG_SCALE;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

static inline void dobject_set_archor_x(struct dobject_t * o, double x)
{
	o->anchorx = x;
	if((o->anchorx != 0.0) || (o->anchory != 0.0))
		o->mflag |= MFLAG_ANCHOR;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

static inline void dobject_set_archor_y(struct dobject_t * o, double y)
{
	o->anchory = y;
	if((o->anchorx != 0.0) || (o->anchory != 0.0))
		o->mflag |= MFLAG_ANCHOR;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

static inline void dobject_set_archor(struct dobject_t * o, double x, double y)
{
	o->anchorx = x;
	o->anchory = y;
	if((o->anchorx != 0.0) || (o->anchory != 0.0))
		o->mflag |= MFLAG_ANCHOR;
	o->mflag |= MFLAG_LOCAL_MATRIX;
}

static inline void dobject_set_alpha(struct dobject_t * o, double alpha)
{
	o->alpha = alpha;
}

static inline void dobject_set_alignment(struct dobject_t * o, enum alignment_t align)
{
	o->alignment = align;
}

static inline void dobject_set_visible(struct dobject_t * o, int visible)
{
	o->visible = visible ? 1 : 0;
}

static inline void dobject_set_touchable(struct dobject_t * o, int touchable)
{
	o->touchable = touchable ? 1 : 0;
}

struct matrix_t * dobject_local_matrix(struct dobject_t * o);
struct matrix_t * dobject_global_matrix(struct dobject_t * o);
void dobject_bounds(struct dobject_t * o, double * x1, double * y1, double * x2, double * y2);
void dobject_global_to_local(struct dobject_t * o, double * x, double * y);
void dobject_local_to_global(struct dobject_t * o, double * x, double * y);
int dobject_hit_test_point(struct dobject_t * o, double x, double y);

#ifdef __cplusplus
}
#endif

#endif /* __GRAPHIC_DOBJECT_H__ */
