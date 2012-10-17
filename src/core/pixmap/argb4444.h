/*!The Graphic 2D Box Library
 * 
 * GBox2 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * GBox2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with GBox2; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2009 - 2012, ruki All rights reserved.
 *
 * @author		ruki
 * @file		argb4444.h
 *
 */
#ifndef G2_CORE_PIXMAP_ARGB4444_H
#define G2_CORE_PIXMAP_ARGB4444_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "rgb16.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */

/* the alpha blend 
 *
 * c: 
 * 0000 0000 0000 0000 aaaa rrrr gggg bbbb
 *
 * c | c << 12:
 * 0000 aaaa rrrr gggg aaaa rrrr gggg bbbb
 *
 * 0x0f0f0f0f:
 * 0000 1111 0000 1111 0000 1111 0000 1111
 *
 * d = (c | c << 12) & 0x0f0f0f0f:
 * 0000 aaaa 0000 gggg 0000 rrrr 0000 bbbb
 *
 * (d & 0xffff) | (d >> 12):
 * 0000 0000 0000 0000 aaaa rrrr gggg bbbb
 *
 * (s * a + d * (32 - a)) >> 5 => ((s - d) * a) >> 5 + d
 */
static __tb_inline__ tb_uint16_t g2_pixmap_argb4444_blend(tb_uint32_t d, tb_uint32_t s, tb_byte_t a)
{
	// FIXME: s - d? overflow?
	s = (s | (s << 12)) & 0x0f0f0f0f;
	d = (d | (d << 12)) & 0x0f0f0f0f;
	d = ((((s - d) * a) >> 5) + d) & 0x0f0f0f0f;
	return (tb_uint16_t)((d & 0xffff) | (d >> 12));
}
static __tb_inline__ tb_uint16_t g2_pixmap_argb4444_blend2(tb_uint32_t d, tb_uint32_t s, tb_byte_t a)
{
	d = (d | (d << 12)) & 0x0f0f0f0f;
	d = ((((s - d) * a) >> 5) + d) & 0x0f0f0f0f;
	return (tb_uint16_t)((d & 0xffff) | (d >> 12));
}

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static __tb_inline__ g2_pixel_t g2_pixmap_argb4444_pixel(g2_color_t color)
{
	return G2_ARGB_4444(color.a, color.r, color.g, color.b);
}
static __tb_inline__ g2_color_t g2_pixmap_argb4444_color(g2_pixel_t pixel)
{
	g2_color_t color;
	color.a = G2_ARGB_4444_A(pixel);
	color.r = G2_ARGB_4444_R(pixel);
	color.g = G2_ARGB_4444_G(pixel);
	color.b = G2_ARGB_4444_B(pixel);
	return color;
}
static __tb_inline__ tb_void_t g2_pixmap_argb4444_pixel_set_la(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u16_le(data, g2_pixmap_argb4444_blend(g2_bits_get_u16_le(data), pixel, alpha >> 3));
}
static __tb_inline__ tb_void_t g2_pixmap_argb4444_pixel_set_ba(tb_pointer_t data, g2_pixel_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u16_be(data, g2_pixmap_argb4444_blend(g2_bits_get_u16_be(data), pixel, alpha >> 3));
}
static __tb_inline__ tb_void_t g2_pixmap_argb4444_pixel_cpy_la(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u16_le(data, g2_pixmap_argb4444_blend(g2_bits_get_u16_le(data), g2_bits_get_u16_le(pixel), alpha >> 3));
}
static __tb_inline__ tb_void_t g2_pixmap_argb4444_pixel_cpy_ba(tb_pointer_t data, tb_cpointer_t pixel, tb_byte_t alpha)
{
	g2_bits_set_u16_be(data, g2_pixmap_argb4444_blend(g2_bits_get_u16_be(data), g2_bits_get_u16_be(pixel), alpha >> 3));
}
static __tb_inline__ g2_color_t g2_pixmap_argb4444_color_get_l(tb_cpointer_t data)
{
	return g2_pixmap_argb4444_color(g2_bits_get_u16_le(data));
}
static __tb_inline__ g2_color_t g2_pixmap_argb4444_color_get_b(tb_cpointer_t data)
{
	return g2_pixmap_argb4444_color(g2_bits_get_u16_be(data));
}
static __tb_inline__ tb_void_t g2_pixmap_argb4444_color_set_lo(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u16_le(data, g2_pixmap_argb4444_pixel(color));
}
static __tb_inline__ tb_void_t g2_pixmap_argb4444_color_set_bo(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u16_be(data, g2_pixmap_argb4444_pixel(color));
}
static __tb_inline__ tb_void_t g2_pixmap_argb4444_color_set_la(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u16_le(data, g2_pixmap_argb4444_blend(g2_bits_get_u16_le(data), g2_pixmap_argb4444_pixel(color), color.a >> 3));
}
static __tb_inline__ tb_void_t g2_pixmap_argb4444_color_set_ba(tb_pointer_t data, g2_color_t color)
{
	g2_bits_set_u16_be(data, g2_pixmap_argb4444_blend(g2_bits_get_u16_be(data), g2_pixmap_argb4444_pixel(color), color.a >> 3));
}
static __tb_inline__ tb_void_t g2_pixmap_argb4444_pixels_set_la(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_size_t 		l = count & 0x3; count -= l; alpha >>= 3;
	tb_uint16_t* 	p = (tb_uint16_t*)data;
	tb_uint16_t* 	e = p + count;
	tb_uint32_t 	s = (pixel | (pixel << 16)) & 0x0f0f0f0f;
	while (p < e)
	{
		g2_bits_set_u16_le(&p[0], g2_pixmap_argb4444_blend2(g2_bits_get_u16_le(&p[0]), s, alpha));
		g2_bits_set_u16_le(&p[1], g2_pixmap_argb4444_blend2(g2_bits_get_u16_le(&p[1]), s, alpha));
		g2_bits_set_u16_le(&p[2], g2_pixmap_argb4444_blend2(g2_bits_get_u16_le(&p[2]), s, alpha));
		g2_bits_set_u16_le(&p[3], g2_pixmap_argb4444_blend2(g2_bits_get_u16_le(&p[3]), s, alpha));
		p += 4;
	}
	while (l--)
	{
		g2_bits_set_u16_le(&p[0], g2_pixmap_argb4444_blend2(g2_bits_get_u16_le(&p[0]), s, alpha));
		p++;
	}
}
static __tb_inline__ tb_void_t g2_pixmap_argb4444_pixels_set_ba(tb_pointer_t data, g2_pixel_t pixel, tb_size_t count, tb_byte_t alpha)
{
	tb_size_t 		l = count & 0x3; count -= l; alpha >>= 3;
	tb_uint16_t* 	p = (tb_uint16_t*)data;
	tb_uint16_t* 	e = p + count;
	tb_uint32_t 	s = (pixel | (pixel << 16)) & 0x0f0f0f0f;
	while (p < e)
	{
		g2_bits_set_u16_be(&p[0], g2_pixmap_argb4444_blend2(g2_bits_get_u16_be(&p[0]), s, alpha));
		g2_bits_set_u16_be(&p[1], g2_pixmap_argb4444_blend2(g2_bits_get_u16_be(&p[1]), s, alpha));
		g2_bits_set_u16_be(&p[2], g2_pixmap_argb4444_blend2(g2_bits_get_u16_be(&p[2]), s, alpha));
		g2_bits_set_u16_be(&p[3], g2_pixmap_argb4444_blend2(g2_bits_get_u16_be(&p[3]), s, alpha));
		p += 4;
	}
	while (l--)
	{
		g2_bits_set_u16_be(&p[0], g2_pixmap_argb4444_blend2(g2_bits_get_u16_be(&p[0]), s, alpha));
		p++;
	}
}

/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

static g2_pixmap_t const g_pixmap_lo_argb4444 =
{ 	
	"argb4444"
, 	16
, 	2
, 	G2_PIXFMT_ARGB4444 | G2_PIXFMT_LENDIAN
, 	g2_pixmap_argb4444_pixel
, 	g2_pixmap_argb4444_color
,	g2_pixmap_rgb16_pixel_get_l
,	g2_pixmap_rgb16_pixel_set_lo
, 	g2_pixmap_rgb16_pixel_cpy_o
,	g2_pixmap_argb4444_color_get_l
,	g2_pixmap_argb4444_color_set_lo
, 	g2_pixmap_rgb16_pixels_set_lo
};

static g2_pixmap_t const g_pixmap_bo_argb4444 =
{ 	
	"argb4444"
, 	16
, 	2
, 	G2_PIXFMT_ARGB4444 | G2_PIXFMT_BENDIAN
, 	g2_pixmap_argb4444_pixel
, 	g2_pixmap_argb4444_color
,	g2_pixmap_rgb16_pixel_get_b
,	g2_pixmap_rgb16_pixel_set_bo
, 	g2_pixmap_rgb16_pixel_cpy_o
,	g2_pixmap_argb4444_color_get_b
,	g2_pixmap_argb4444_color_set_bo
, 	g2_pixmap_rgb16_pixels_set_bo
};

static g2_pixmap_t const g_pixmap_la_argb4444 =
{ 	
	"argb4444"
, 	16
, 	2
, 	G2_PIXFMT_ARGB4444 | G2_PIXFMT_LENDIAN
, 	g2_pixmap_argb4444_pixel
, 	g2_pixmap_argb4444_color
,	g2_pixmap_rgb16_pixel_get_l
,	g2_pixmap_argb4444_pixel_set_la
, 	g2_pixmap_argb4444_pixel_cpy_la
,	g2_pixmap_argb4444_color_get_l
,	g2_pixmap_argb4444_color_set_la
, 	g2_pixmap_argb4444_pixels_set_la
};

static g2_pixmap_t const g_pixmap_ba_argb4444 =
{ 	
	"argb4444"
, 	16
, 	2
, 	G2_PIXFMT_ARGB4444 | G2_PIXFMT_BENDIAN
, 	g2_pixmap_argb4444_pixel
, 	g2_pixmap_argb4444_color
,	g2_pixmap_rgb16_pixel_get_b
,	g2_pixmap_argb4444_pixel_set_ba
, 	g2_pixmap_argb4444_pixel_cpy_ba
,	g2_pixmap_argb4444_color_get_b
,	g2_pixmap_argb4444_color_set_ba
, 	g2_pixmap_argb4444_pixels_set_ba
};


#endif

