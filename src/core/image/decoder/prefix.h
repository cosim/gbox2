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
 * @file		prefix.h
 *
 */
#ifndef G2_CORE_IMAGE_DECODER_PREFIX_H
#define G2_CORE_IMAGE_DECODER_PREFIX_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "../prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the image decoder type
typedef struct __g2_image_decoder_t
{
	// the image type
	tb_size_t 		type;

	// the stream
	tb_gstream_t* 	gst;

	// the pixfmt
	tb_size_t 		pixfmt;

	// the width
	tb_size_t 		width;

	// the height
	tb_size_t 		height;

	// done
	tb_handle_t 	(*done)(struct __g2_image_decoder_t* decoder);

	// free
	tb_void_t 		(*free)(struct __g2_image_decoder_t* decoder);

}g2_image_decoder_t;

#endif


