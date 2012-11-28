/* ////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "shape.c"

/* ////////////////////////////////////////////////////////////////////////
 * implemention
 */
static tb_bool_t g2_demo_shape_init(tb_int_t argc, tb_char_t** argv)
{
	// init mode
	g_mode = G2_STYLE_MODE_FILL_STOK;

	// ok
	return TB_TRUE;
}
static tb_void_t g2_demo_shape_exit()
{
}
static tb_void_t g2_demo_shape_render()
{
	if (g_bm) g2_draw_iellipse2(g_painter, 0, 0, 200, 100);
	else g2_draw_iellipse2(g_painter, g_x0, g_y0, g_dx, g_dy);
}
static tb_void_t g2_demo_shape_key(tb_int_t key)
{
}
