/* ScummVM - Scumm Interpreter
 * Copyright (C) 2002-2003 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 *
 */

#include <stdafx.h>
#include "codec1.h"

Codec1Decoder::~Codec1Decoder() {
}

bool Codec1Decoder::decode(byte *dst, const byte *src, int) {
	byte val;
	int32 size_line;
	int32 code, length;
	int32 h, height = getRect().height();

	for(h = 0; h < height; h++) {
		size_line = READ_LE_UINT16(src); // size of compressed line !
		src += 2;
#ifdef DEBUG_CODEC1
		debug(7, "codec1 : h == %d, size_line == %d", h, size_line);
#endif
		while(size_line > 0) {
			code = *src++;
			size_line--;
			length = (code >> 1) + 1;
#ifdef DEBUG_CODEC1
			debug(7, "codec1 : length == %d", length);
#endif
			if(code & 1) {
				val = *src++;
				size_line--;
				if (val)
					memset(dst, val, length);
				dst += length;
#ifdef DEBUG_CODEC1
			debug(7, "codec1 : blitting %d times %d", length, val);
#endif
			} else {
				size_line -= length;
#ifdef DEBUG_CODEC1
				debug(7, "codec1 : blitting %d entries", length);
#endif
				while(length--) {
					val = *src++;
					if (val)
						*dst = val;
					dst++;
				}
			}
		}
	}
	return true;
}
