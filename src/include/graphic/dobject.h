#ifndef __GRAPHIC_DOBJECT_H__
#define __GRAPHIC_DOBJECT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <list.h>
#include <graphic/matrix.h>

struct stage_t;
struct dobject_t;

enum dobject_type_t {
	DOBJECT_TYPE_CONTAINER,
	DOBJECT_TYPE_NODE,
};

enum alignment_t {
	XALIGN_NONE				= 0,
	XALIGN_LEFT				= 1,
	XALIGN_TOP				= 2,
	XALIGN_RIGHT			= 3,
	XALIGN_BOTTOM			= 4,
	XALIGN_LEFT_TOP			= 5,
	XALIGN_RIGHT_TOP		= 6,
	XALIGN_LEFT_BOTTOM		= 7,
	XALIGN_RIGHT_BOTTOM		= 8,
	XALIGN_LEFT_CENTER		= 9,
	XALIGN_TOP_CENTER		= 10,
	XALIGN_RIGHT_CENTER		= 11,
	XALIGN_BOTTOM_CENTER	= 12,
	XALIGN_HORIZONTAL_CENTER	= 13,
	XALIGN_VERTICAL_CENTER	= 14,
	XALIGN_CENTER			= 15,
	XALIGN_LEFT_FILL		= 16,
	XALIGN_TOP_FILL			= 17,
	XALIGN_RIGHT_FILL		= 18,
	XALIGN_BOTTOM_FILL		= 19,
	XALIGN_HORIZONTAL_FILL	= 20,
	XALIGN_VERTICAL_FILL	= 21,
	XALIGN_CENTER_FILL		= 22,
};

enum draw_type_t {
	DRAW_TYPE_NONE			= 0,
	DRAW_TYPE_TEXTURE		= 1,
};
typedef void (*dobject_draw_t)(struct dobject_t * o, struct stage_t * s);

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
	enum draw_type_t dtype;
	void * priv;
};

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

static inline struct matrix_t * dobject_local_matrix(struct dobject_t * o)
{
	struct matrix_t * m = &o->local_matrix;
	if(o->mflag & MFLAG_LOCAL_MATRIX)
	{
		matrix_init_identity(m);
		if(o->mflag & MFLAG_TRANSLATE)
			matrix_translate(m, o->x, o->y);
		if(o->mflag & MFLAG_ROTATE)
			matrix_rotate(m, o->rotation);
		if(o->mflag & MFLAG_ANCHOR)
			matrix_translate(m, -o->anchorx * o->width * o->scalex, -o->anchory * o->height * o->scaley);
		if(o->mflag & MFLAG_SCALE)
			matrix_scale(m, o->scalex, o->scaley);
		o->mflag &= ~(MFLAG_LOCAL_MATRIX);
	}
	return m;
}

static inline struct matrix_t * dobject_global_matrix(struct dobject_t * o)
{
	struct dobject_t * t = o;
	struct matrix_t m;

	matrix_init_identity(&m);
	while((o->parent != o))
	{
		matrix_multiply(&m, &m, dobject_local_matrix(o));
		o = o->parent;
	}
	memcpy(&t->global_matrix, &m, sizeof(struct matrix_t));
	return &t->global_matrix;
}

static inline void dobject_bounds(struct dobject_t * o, double * x1, double * y1, double * x2, double * y2)
{
	struct matrix_t * m = dobject_global_matrix(o);
	*x1 = 0;
	*y1 = 0;
	*x2 = o->width;
	*y2 = o->height;
	matrix_transform_bounds(m, x1, y1, x2, y2);
}

static inline void dobject_global_to_local(struct dobject_t * o, double * x, double * y)
{
	struct matrix_t m;

	memcpy(&m, dobject_global_matrix(o), sizeof(struct matrix_t));
	matrix_invert(&m);
	matrix_transform_point(&m, x, y);
}

static inline void dobject_local_to_global(struct dobject_t * o, double * x, double * y)
{
	struct matrix_t * m = dobject_global_matrix(o);
	matrix_transform_point(m, x, y);
}

static inline int dobject_hit_test_point(struct dobject_t * o, double x, double y)
{
	dobject_global_to_local(o, &x, &y);
	return ((x >= 0) && (y >= 0) && (x <= o->width) && (y <= o->height)) ? 1 : 0;
}

bool_t dobject_init(struct dobject_t * o, enum dobject_type_t type, dobject_draw_t draw, enum draw_type_t dtype, void * priv);
bool_t dobject_add(struct dobject_t * parent, struct dobject_t * o);
bool_t dobject_remove(struct dobject_t * parent, struct dobject_t * o);
bool_t dobject_remove_self(struct dobject_t * o);

#ifdef __cplusplus
}
#endif

#endif /* __GRAPHIC_DOBJECT_H__ */
