/*
 * kernel/graphic/stage.c
 *
 * Copyright(c) 2007-2018 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <xboot.h>
#include <framebuffer/framebuffer.h>
#include <graphic/stage.h>

struct stage_t * stage_alloc(const char * path, const char * fb)
{
	struct framebuffer_t * fbdev = fb ? search_framebuffer(fb) : search_first_framebuffer();
	struct stage_t * s;

	if(!fbdev)
		return NULL;

	if(!is_absolute_path(path))
		return NULL;

	s = malloc(sizeof(struct stage_t));
	if(!s)
		return NULL;

	s->xfs = xfs_alloc(path);
	s->fb = fbdev;
	s->cs = cairo_xboot_surface_create(s->fb, NULL);
	s->cr = cairo_create(s->cs);
	dobject_init(&s->o, DOBJECT_TYPE_CONTAINER, NULL, NULL);
	dobject_set_size(&s->o, framebuffer_get_width(s->fb), framebuffer_get_height(s->fb));

	return s;
}

void stage_free(struct stage_t * s)
{
	if(!s)
		return;

	xfs_free(s->xfs);
	cairo_destroy(s->cr);
	cairo_surface_destroy(s->cs);
	dobject_remove_self(&s->o);

	free(s);
}
