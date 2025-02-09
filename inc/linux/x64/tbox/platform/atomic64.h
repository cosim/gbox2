/*!The Treasure Box Library
 * 
 * TBox is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * TBox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with TBox; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2009 - 2012, ruki All rights reserved.
 *
 * @author		ruki
 * @file		atomic64.h
 * @ingroup 	platform
 *
 */
#ifndef TB_PLATFORM_ATOMIC64_H
#define TB_PLATFORM_ATOMIC64_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "atomic.h"

#if !TB_CPU_BIT64
# 	if defined(TB_COMPILER_IS_GCC) \
		&& TB_COMPILER_VERSION_BE(4, 1)
# 		include "compiler/gcc/atomic64.h"
# 	elif defined(TB_CONFIG_OS_WINDOWS)
# 		include "windows/atomic64.h"
# 	endif
#endif

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

#if TB_CPU_BIT64

# 	define tb_atomic64_get(a) 					tb_atomic_get(a)
# 	define tb_atomic64_set(a, v) 				tb_atomic_set(a, v)
# 	define tb_atomic64_set0(a) 					tb_atomic_set0(a)
# 	define tb_atomic64_pset(a, p, v) 			tb_atomic_pset(a, p, v)
# 	define tb_atomic64_fetch_and_set0(a) 		tb_atomic_fetch_and_set0(a)
# 	define tb_atomic64_fetch_and_set(a, v) 		tb_atomic_fetch_and_set(a, v)
# 	define tb_atomic64_fetch_and_pset(a, p, v) 	tb_atomic_fetch_and_pset(a, p, v)

# 	define tb_atomic64_fetch_and_inc(a) 		tb_atomic_fetch_and_inc(a)
# 	define tb_atomic64_fetch_and_dec(a) 		tb_atomic_fetch_and_dec(a)
# 	define tb_atomic64_fetch_and_add(a, v) 		tb_atomic_fetch_and_add(a, v)
# 	define tb_atomic64_fetch_and_sub(a, v) 		tb_atomic_fetch_and_sub(a, v)
# 	define tb_atomic64_fetch_and_or(a, v) 		tb_atomic_fetch_and_or(a, v)
# 	define tb_atomic64_fetch_and_xor(a, v) 		tb_atomic_fetch_and_xor(a, v)
# 	define tb_atomic64_fetch_and_and(a, v) 		tb_atomic_fetch_and_and(a, v)

# 	define tb_atomic64_inc_and_fetch(a) 		tb_atomic_inc_and_fetch(a)
# 	define tb_atomic64_dec_and_fetch(a) 		tb_atomic_dec_and_fetch(a)
# 	define tb_atomic64_add_and_fetch(a, v) 		tb_atomic_add_and_fetch(a, v)
# 	define tb_atomic64_sub_and_fetch(a, v) 		tb_atomic_sub_and_fetch(a, v)
# 	define tb_atomic64_or_and_fetch(a, v) 		tb_atomic_or_and_fetch(a, v)
# 	define tb_atomic64_xor_and_fetch(a, v) 		tb_atomic_xor_and_fetch(a, v)
# 	define tb_atomic64_and_and_fetch(a, v) 		tb_atomic_and_and_fetch(a, v)

#endif

#ifndef tb_atomic64_get
# 	define tb_atomic64_get(a) 					tb_atomic64_get_generic(a)
#endif

#ifndef tb_atomic64_set
# 	define tb_atomic64_set(a, v) 				tb_atomic64_set_generic(a, v)
#endif

#ifndef tb_atomic64_set0
# 	define tb_atomic64_set0(a) 					tb_atomic64_set0_generic(a)
#endif

#ifndef tb_atomic64_pset
# 	define tb_atomic64_pset(a, p, v) 			tb_atomic64_pset_generic(a, p, v)
#endif

#ifndef tb_atomic64_fetch_and_set0
# 	define tb_atomic64_fetch_and_set0(a) 		tb_atomic64_fetch_and_set0_generic(a)
#endif

#ifndef tb_atomic64_fetch_and_set
# 	define tb_atomic64_fetch_and_set(a, v) 		tb_atomic64_fetch_and_set_generic(a, v)
#endif

#ifndef tb_atomic64_fetch_and_pset
# 	define tb_atomic64_fetch_and_pset(a, p, v) 	tb_atomic64_fetch_and_pset_generic(a, p, v)
#endif

#ifndef tb_atomic64_fetch_and_inc
# 	define tb_atomic64_fetch_and_inc(a) 		tb_atomic64_fetch_and_inc_generic(a)
#endif

#ifndef tb_atomic64_fetch_and_dec
# 	define tb_atomic64_fetch_and_dec(a) 		tb_atomic64_fetch_and_dec_generic(a)
#endif

#ifndef tb_atomic64_fetch_and_add
# 	define tb_atomic64_fetch_and_add(a, v) 		tb_atomic64_fetch_and_add_generic(a, v)
#endif

#ifndef tb_atomic64_fetch_and_sub
# 	define tb_atomic64_fetch_and_sub(a, v) 		tb_atomic64_fetch_and_sub_generic(a, v)
#endif

#ifndef tb_atomic64_fetch_and_or
# 	define tb_atomic64_fetch_and_or(a, v) 		tb_atomic64_fetch_and_or_generic(a, v)
#endif

#ifndef tb_atomic64_fetch_and_xor
# 	define tb_atomic64_fetch_and_xor(a, v) 		tb_atomic64_fetch_and_xor_generic(a, v)
#endif

#ifndef tb_atomic64_fetch_and_and
# 	define tb_atomic64_fetch_and_and(a, v) 		tb_atomic64_fetch_and_and_generic(a, v)
#endif

#ifndef tb_atomic64_inc_and_fetch
# 	define tb_atomic64_inc_and_fetch(a) 		tb_atomic64_inc_and_fetch_generic(a)
#endif

#ifndef tb_atomic64_dec_and_fetch
# 	define tb_atomic64_dec_and_fetch(a) 		tb_atomic64_dec_and_fetch_generic(a)
#endif

#ifndef tb_atomic64_add_and_fetch
# 	define tb_atomic64_add_and_fetch(a, v) 		tb_atomic64_add_and_fetch_generic(a, v)
#endif

#ifndef tb_atomic64_sub_and_fetch
# 	define tb_atomic64_sub_and_fetch(a, v) 		tb_atomic64_sub_and_fetch_generic(a, v)
#endif

#ifndef tb_atomic64_or_and_fetch
# 	define tb_atomic64_or_and_fetch(a, v) 		tb_atomic64_or_and_fetch_generic(a, v)
#endif

#ifndef tb_atomic64_xor_and_fetch
# 	define tb_atomic64_xor_and_fetch(a, v) 		tb_atomic64_xor_and_fetch_generic(a, v)
#endif

#ifndef tb_atomic64_and_and_fetch
# 	define tb_atomic64_and_and_fetch(a, v) 		tb_atomic64_and_and_fetch_generic(a, v)
#endif


/* ///////////////////////////////////////////////////////////////////////
 * get & set
 */
static __tb_inline__ tb_hize_t tb_atomic64_get_generic(tb_atomic64_t* a)
{
	tb_trace_nosafe();
	tb_assert(a);
	return *a;
}
static __tb_inline__ tb_void_t tb_atomic64_set_generic(tb_atomic64_t* a, tb_hize_t v)
{
	tb_trace_nosafe();
	tb_assert(a);
	*a = v;
}
static __tb_inline__ tb_void_t tb_atomic64_set0_generic(tb_atomic64_t* a)
{
	tb_trace_nosafe();
	tb_assert(a);
	*a = 0;
}
static __tb_inline__ tb_void_t tb_atomic64_pset_generic(tb_atomic64_t* a, tb_hize_t p, tb_hize_t v)
{
	tb_trace_nosafe();
	tb_assert(a);
	if (*a == p) *a = v;
}
static __tb_inline__ tb_hize_t tb_atomic64_fetch_and_set0_generic(tb_atomic64_t* a)
{
	tb_trace_nosafe();
	tb_assert(a);

	tb_hize_t o = *a;
	*a = 0;
	return o;
}
static __tb_inline__ tb_hize_t tb_atomic64_fetch_and_set_generic(tb_atomic64_t* a, tb_hize_t v)
{
	tb_trace_nosafe();
	tb_assert(a);

	tb_hize_t o = *a;
	*a = v;
	return o;
}
static __tb_inline__ tb_hize_t tb_atomic64_fetch_and_pset_generic(tb_atomic64_t* a, tb_hize_t p, tb_hize_t v)
{
	tb_trace_nosafe();
	tb_assert(a);

	tb_hize_t o = *a;
	if (o == p) *a = v;
	return o;
}

/* ///////////////////////////////////////////////////////////////////////
 * fetch and ...
 */
static __tb_inline__ tb_hong_t tb_atomic64_fetch_and_inc_generic(tb_atomic64_t* a)
{
	tb_trace_nosafe();
	tb_assert(a);

	tb_hong_t __tb_volatile__* pa = (tb_hong_t __tb_volatile__*)a;
	return *pa++;
}
static __tb_inline__ tb_hong_t tb_atomic64_fetch_and_dec_generic(tb_atomic64_t* a)
{
	tb_trace_nosafe();
	tb_assert(a);

	tb_hong_t __tb_volatile__* pa = (tb_hong_t __tb_volatile__*)a;
	return *pa--;
}
static __tb_inline__ tb_hong_t tb_atomic64_fetch_and_add_generic(tb_atomic64_t* a, tb_hong_t v)
{
	tb_trace_nosafe();
	tb_assert(a);

	tb_hong_t o = *((tb_hong_t*)a);
	*((tb_hong_t*)a) += v;
	return o;
}
static __tb_inline__ tb_hong_t tb_atomic64_fetch_and_sub_generic(tb_atomic64_t* a, tb_hong_t v)
{
	tb_trace_nosafe();
	tb_assert(a);

	tb_hong_t o = *((tb_hong_t*)a);
	*((tb_hong_t*)a) -= v;
	return o;
}
static __tb_inline__ tb_hize_t tb_atomic64_fetch_and_xor_generic(tb_atomic64_t* a, tb_hize_t v)
{
	tb_trace_nosafe();
	tb_assert(a);

	tb_hize_t o = *a;
	*a ^= v;
	return o;
}
static __tb_inline__ tb_hize_t tb_atomic64_fetch_and_and_generic(tb_atomic64_t* a, tb_hize_t v)
{
	tb_trace_nosafe();
	tb_assert(a);

	tb_hize_t o = *a;
	*a &= v;
	return o;
}
static __tb_inline__ tb_hize_t tb_atomic64_fetch_and_or_generic(tb_atomic64_t* a, tb_hize_t v)
{
	tb_trace_nosafe();
	tb_assert(a);

	tb_hize_t o = *a;
	*a |= v;
	return o;
}

/* ///////////////////////////////////////////////////////////////////////
 * ... and fetch
 */
static __tb_inline__ tb_hong_t tb_atomic64_inc_and_fetch_generic(tb_atomic64_t* a)
{
	tb_trace_nosafe();
	tb_assert(a);

	tb_hong_t __tb_volatile__* pa = (tb_hong_t __tb_volatile__*)a;
	return ++*pa;
}
static __tb_inline__ tb_hong_t tb_atomic64_dec_and_fetch_generic(tb_atomic64_t* a)
{
	tb_trace_nosafe();
	tb_assert(a);

	tb_hong_t __tb_volatile__* pa = (tb_hong_t __tb_volatile__*)a;
	return --*pa;
}
static __tb_inline__ tb_hong_t tb_atomic64_add_and_fetch_generic(tb_atomic64_t* a, tb_hong_t v)
{
	tb_trace_nosafe();
	tb_assert(a);

	*((tb_hong_t*)a) += v;
	return *((tb_hong_t*)a);
}
static __tb_inline__ tb_hong_t tb_atomic64_sub_and_fetch_generic(tb_atomic64_t* a, tb_hong_t v)
{
	tb_trace_nosafe();
	tb_assert(a);

	*((tb_hong_t*)a) -= v;
	return *((tb_hong_t*)a);
}
static __tb_inline__ tb_hize_t tb_atomic64_xor_and_fetch_generic(tb_atomic64_t* a, tb_hize_t v)
{
	tb_trace_nosafe();
	tb_assert(a);

	*((tb_hong_t*)a) ^= v;
	return *((tb_hong_t*)a);
}
static __tb_inline__ tb_hize_t tb_atomic64_and_and_fetch_generic(tb_atomic64_t* a, tb_hize_t v)
{
	tb_trace_nosafe();
	tb_assert(a);

	*((tb_hong_t*)a) &= v;
	return *((tb_hong_t*)a);
}
static __tb_inline__ tb_hize_t tb_atomic64_or_and_fetch_generic(tb_atomic64_t* a, tb_hize_t v)
{
	tb_trace_nosafe();
	tb_assert(a);

	*((tb_hong_t*)a) |= v;
	return *((tb_hong_t*)a);
}




#endif
