/* ////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "demo.h"

/* ////////////////////////////////////////////////////////////////////////
 * globals
 */
static g2_svg_element_t* g_svg = TB_NULL;

/* ////////////////////////////////////////////////////////////////////////
 * events
 */
static tb_void_t g2_demo_move(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_drag(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_wheeldown(tb_int_t x, tb_int_t y)
{	
}
static tb_void_t g2_demo_wheelup(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_lclickdown(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_lclickup(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_rclickdown(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_rclickup(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_key(tb_int_t key)
{
}

/* ////////////////////////////////////////////////////////////////////////
 * implemention
 */
static tb_bool_t g2_demo_init(tb_int_t argc, tb_char_t** argv)
{
	// check
	tb_assert_and_check_return_val(argv[1], TB_FALSE);

	// load svg
	tb_gstream_t* gst = tb_gstream_init_from_url(argv[1]);
	if (gst && tb_gstream_bopen(gst))
	{
		// init reader & writer
		tb_handle_t reader = g2_svg_reader_init(gst);
		if (reader)
		{
			// load
			g_svg = g2_svg_reader_load(reader);
			
			// exit reader
			g2_svg_reader_exit(reader);
		}
	
		// exit stream
		tb_gstream_exit(gst);
	}

	// ok?
	return g_svg? TB_TRUE : TB_FALSE;
}
static tb_void_t g2_demo_exit()
{
	if (g_svg) g2_svg_element_exit(g_svg);
	g_svg = TB_NULL;
}
static tb_void_t g2_demo_size(tb_int_t w, tb_int_t h)
{
}
static tb_void_t g2_demo_render()
{
	// size
	g2_float_t w = ((g2_svg_element_svg_t const*)g_svg)->width;
	g2_float_t h = ((g2_svg_element_svg_t const*)g_svg)->height;
	if (g2_ez(w)) w = ((g2_svg_element_svg_t const*)g_svg)->viewbox.w;
	if (g2_ez(h)) h = ((g2_svg_element_svg_t const*)g_svg)->viewbox.h;
	tb_assert_and_check_return(g2_nz(w) && g2_nz(h));

	// rect
	g2_rect_t rect;
	if (g_bm) rect = g2_rect_imake(-100, -100, 200, 200);
	else rect = g2_rect_imake(g_x0 - g_dx, g_y0 - g_dy, g_dx << 1, g_dy << 1);

	// save 
	g2_save(g_painter, G2_SAVE_MODE_MATRIX_CLIP);

	// clip
	g2_clip_rect(g_painter, G2_CLIP_MODE_REPLACE, &rect);

	// matrix
	g2_translate(g_painter, rect.x, rect.y);
//	g2_scale(g_painter, rect.w / w, rect.h / h);
//	g2_scale(g_painter, rect.w / 500, rect.h / 500);
	
	// draw
	g2_draw_svg(g_painter, g_svg);

	// load
	g2_load(g_painter);
}
