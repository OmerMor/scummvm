/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef CHEWY_CURSOR_H
#define CHEWY_CURSOR_H

#include "chewy/chewy.h"

namespace Chewy {

class SpriteResource;
class Font;

class Cursor {
public:
	Cursor(ChewyEngine *vm);
	virtual ~Cursor();

	void setCursor(uint num, bool newCursor = true);
	void showCursor();
	void hideCursor();
	void animateCursor();
	void nextCursor();

private:
	ChewyEngine *_vm;

	uint _curCursor;
	uint _curCursorFrame;
	SpriteResource *_cursorSprites;
};

} // End of namespace Chewy

#endif
