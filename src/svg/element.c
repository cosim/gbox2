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
 * @file		element.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "element.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */
// the svg element entry type
typedef struct __g2_svg_element_entry_t
{
	// the element type
	tb_size_t 				type;

	// the element name
	tb_char_t const* 		name;

	// the initialiser
	g2_svg_element_t* 		(*init)(tb_handle_t reader);

}g2_svg_element_entry_t;

/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

// the entries
static g2_svg_element_entry_t 	g_element_entries[] = 
{
	{G2_SVG_ELEMENT_TYPE_NONE, 				"none", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_A, 				"a", 					g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_ANIMATE, 			"animate", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_ANIMATECOLOR, 		"animateColor", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_ANIMATEMOTION, 	"animateMotion", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_ANIMATETRANSFORM, 	"animateTransform", 	g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_CIRCLE, 			"circle", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_CLIPPATH, 			"clipPath", 			g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_DEFS, 				"defs", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_DESC, 				"desc", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_ELLIPSE, 			"ellipse", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FECOLORMATRIX, 	"feColorMatrix", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FEGAUSSIANBLUR, 	"feGaussianBlur", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FEMERGE, 			"feMerge", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FEMERGENODE, 		"feMergeNode", 			g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FILTER, 			"filter", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_G, 				"g", 					g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_GLYPH, 			"glyph", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_IMAGE, 			"image", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_LINE, 				"line", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_LINEARGRADIENT, 	"linearGradient", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_MASK, 				"mask", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_METADATA, 			"metadata", 			g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_PATH, 				"path", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_POLYGON, 			"polygon", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_POLYLINE, 			"polyline", 			g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_RADIALGRADIENT, 	"radialGradient", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_RECT, 				"rect", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_SCRIPT, 			"script", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_SVG, 				"svg", 					g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_STOP, 				"stop", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_SYMBOL, 			"symbol", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_TEXT, 				"text", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_TITLE, 			"title", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_TSPAN, 			"tspan", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_USE, 				"use", 					g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_VIDEO, 			"video", 				g2_svg_element_init_none 				}
};

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
g2_svg_element_t* g2_svg_element_init(tb_handle_t reader)
{
	// the element name
	tb_char_t const* name = tb_xml_reader_element(reader);
	tb_assert_and_check_return_val(name, TB_NULL);

	// FIXME: use binary search
	tb_size_t i = 0;
	tb_size_t n = tb_arrayn(g_element_entries);
	for (i = 1; i < n; i++)
		if (g_element_entries[i].init && !tb_stricmp(g_element_entries[i].name, name)) 
		{
			// init
			g2_svg_element_t* element = g_element_entries[i].init(reader);
			if (element) element->type = g_element_entries[i].type;
			return element;
		}

	// none
	return g2_svg_element_init_none(reader);
}
g2_svg_element_t* g2_svg_element_init_none(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_t* element = tb_malloc0(sizeof(g2_svg_element_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->type = G2_SVG_ELEMENT_TYPE_NONE;

	// ok
	return element;
}

tb_void_t g2_svg_element_exit(g2_svg_element_t* element)
{
	if (element)
	{
		// free childs
		if (element->head)
		{
			g2_svg_element_t* save = TB_NULL;
			g2_svg_element_t* next = element->head;
			while (next)
			{
				// save
				save = next->next;
				
				// exit
				g2_svg_element_exit(element);

				// next
				next = save;
			}
		}

		// exit it
		if (element->exit) element->exit(element);
	
		// free it
		tb_free(element);
	}
}
tb_void_t g2_svg_element_insert_next(g2_svg_element_t* element, g2_svg_element_t* next)
{
	// check
	tb_assert_and_check_return(element && next);

	// init
	next->parent = element->parent;
	next->next = element->next;

	// next
	element->next = next;
}
tb_void_t g2_svg_element_remove_next(g2_svg_element_t* element)
{
	// check
	tb_assert_and_check_return(element);

	// next
	g2_svg_element_t* next = element->next;

	// save
	g2_svg_element_t* save = next? next->next : TB_NULL;

	// exit
	if (next) g2_svg_element_exit(next);

	// next
	element->next = save;
}
tb_void_t g2_svg_element_append_head(g2_svg_element_t* element, g2_svg_element_t* child)
{
	// check
	tb_assert_and_check_return(element && child);

	// init
	child->parent = element;

	// append
	if (element->head) 
	{
		child->next = element->head;
		element->head = child;
	}
	else
	{
		tb_assert(!element->tail);
		element->tail = element->head = child;
	}
}
tb_void_t g2_svg_element_append_tail(g2_svg_element_t* element, g2_svg_element_t* child)
{
	// check
	tb_assert_and_check_return(element && child);

	// init
	child->parent = element;
	child->next = TB_NULL;

	// append
	if (element->tail) 
	{
		element->tail->next = child;
		element->tail = child;
	}
	else
	{
		tb_assert(!element->head);
		element->tail = element->head = child;
	}
}
#ifdef G2_DEBUG
tb_void_t g2_svg_element_dump(g2_svg_element_t* element)
{
	tb_assert_and_check_return(element);

	// the element name
	tb_char_t const* name = element->type < tb_arrayn(g_element_entries)? g_element_entries[element->type].name : TB_NULL;

	// the element level
	tb_size_t 			level = 0;
	g2_svg_element_t* 	parent = element->parent;
	for (; parent; parent = parent->parent) level++;

	// format
	tb_size_t 			ntabs = level;
	while (ntabs--) tb_printf("\t");

	// walk
	if (element->head)
	{
		// enter element
		tb_printf("<%s>\n", name);

		// dump childs
		g2_svg_element_t* next = element->head;
		while (next)
		{
			// dump
			g2_svg_element_dump(next);

			// next
			next = next->next;
		}

		// format
		ntabs = level;
		while (ntabs--) tb_printf("\t");

		// leave element
		tb_printf("</%s>\n", name);
	}
	// empty element
	else tb_printf("<%s/>\n", name);
}
#endif
