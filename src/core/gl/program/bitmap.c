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
 * @file		bitmap.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"gl"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "bitmap.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_handle_t g2_gl_program_init_bitmap()
{
	// init
	tb_handle_t program = g2_gl_program_init();
	tb_assert_and_check_return_val(program, tb_null);

	// init type
	g2_gl_program_type_set(program, G2_GL_PROGRAM_TYPE_BITMAP);

	// the vertex shader
	tb_char_t const* vshader = 
		"precision mediump float; 															\n"
		" 																					\n"
		"attribute vec4 aColor; 															\n"
		"attribute vec4 aTexcoords; 														\n"
		"attribute vec4 aVertices; 															\n"
		" 																					\n"
		"varying vec4 vColors; 																\n"
		"varying vec4 vTexcoords; 															\n"
		"uniform mat4 uMatrixModel; 														\n"
		"uniform mat4 uMatrixProject; 														\n"
		"uniform mat4 uMatrixTexcoord; 														\n"
		" 																					\n"
		"void main() 																		\n"
		"{ 																					\n"
		" 	vColors = aColor; 																\n" 
		" 	vTexcoords = uMatrixTexcoord * aTexcoords; 										\n"  
		" 	gl_Position = uMatrixProject * uMatrixModel * aVertices;						\n"
		"} 																					\n";
	
	// the fragment shader
	tb_char_t const* fshader = 
		"precision mediump float; 															\n"
		" 																					\n"
		"varying vec4 vColors; 																\n"
		"varying vec4 vTexcoords; 															\n"
		"uniform sampler2D uSampler; 														\n"
		" 																					\n"
		"void main() 																		\n"
		"{ 																					\n"
		"   gl_FragColor = vColors * texture2D(uSampler, vec2(vTexcoords.x, vTexcoords.y)); \n"
		"} 																					\n";


	// load shader: vertex
	if (!g2_gl_program_load(program, vshader, G2_GL_VERTEX_SHADER)) goto fail;
	
	// load shader: fragment
	if (!g2_gl_program_load(program, fshader, G2_GL_FRAGMENT_SHADER)) goto fail;

	// make program
	if (!g2_gl_program_make(program)) goto fail;

	// init location
	g2_gl_program_location_set(program, G2_GL_PROGRAM_LOCATION_COLORS, g2_gl_program_attr(program, "aColor"));
	g2_gl_program_location_set(program, G2_GL_PROGRAM_LOCATION_VERTICES, g2_gl_program_attr(program, "aVertices"));
	g2_gl_program_location_set(program, G2_GL_PROGRAM_LOCATION_TEXCOORDS, g2_gl_program_attr(program, "aTexcoords"));
	g2_gl_program_location_set(program, G2_GL_PROGRAM_LOCATION_MATRIX_MODEL, g2_gl_program_unif(program, "uMatrixModel"));
	g2_gl_program_location_set(program, G2_GL_PROGRAM_LOCATION_MATRIX_PROJECT, g2_gl_program_unif(program, "uMatrixProject"));
	g2_gl_program_location_set(program, G2_GL_PROGRAM_LOCATION_MATRIX_TEXCOORD, g2_gl_program_unif(program, "uMatrixTexcoord"));

//	g2_gl_program_location_set(program, G2_GL_PROGRAM_LOCATION_SAMPLER, g2_gl_program_unif(program, "uSampler"));
//	g2_glUniform1i(g2_gl_program_location(program, G2_GL_PROGRAM_LOCATION_SAMPLER), 0);

	// ok
	return program;
fail:
	if (program) g2_gl_program_exit(program);
	return tb_null;
}

