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

#ifndef ULTIMA_ULTIMA8_ENGINE_DEBUGGER_H
#define ULTIMA_ULTIMA8_ENGINE_DEBUGGER_H

#include "ultima/shared/engine/debugger.h"

namespace Ultima {
namespace Ultima8 {

class Ultima1Engine;

/**
 * Debugger base class
 */
class Debugger : public Shared::Debugger {
private:
	// Audio Process
	bool cmdListSFX(int argc, const char **argv);
	bool cmdStopSFX(int argc, const char **argv);
	bool cmdPlaySFX(int argc, const char **argv);

	// Game Map Gump
	bool cmdToggleHighlightItems(int argc, const char **argv);
	bool cmdDumpMap(int argc, const char **argvv);
	bool cmdIncrementSortOrder(int argc, const char **argv);
	bool cmdDecrementSortOrder(int argc, const char **argv);

	// HID Manager
	bool cmdBind(int argc, const char **argv);
	bool cmdUnbind(int argc, const char **argv);
	bool cmdListbinds(int argc, const char **argv);
	bool cmdSave(int argc, const char **argv);

	// Kernel
	bool cmdProcessTypes(int argc, const char **argv);
	bool cmdListProcesses(int argc, const char **argv);
	bool cmdProcessInfo(int argc, const char **argv);
	bool cmdToggleFrameByFrame(int argc, const char **argv);
	bool cmdAdvanceFrame(int argc, const char **argv);

	// Memory Manager
	bool cmdMemInfo(int argc, const char **argv);
	bool cmdTest(int argc, const char **argv);

	// Object Manager
	bool cmdObjectTypes(int argc, const char **argv);
	bool cmdObjectInfo(int argc, const char **argv);

	// Quick Avatar Mover Process
	bool cmdStartMoveUp(int argc, const char **argv);
	bool cmdStartMoveDown(int argc, const char **argv);
	bool cmdStartMoveLeft(int argc, const char **argv);
	bool cmdStartMoveRight(int argc, const char **argv);
	bool cmdStartAscend(int argc, const char **argv);
	bool cmdStartDescend(int argc, const char **argv);
	bool cmdStopMoveUp(int argc, const char **argv);
	bool cmdStopMoveDown(int argc, const char **argv);
	bool cmdStopMoveLeft(int argc, const char **argv);
	bool cmdStopMoveRight(int argc, const char **argv);
	bool cmdStopAscend(int argc, const char **argv);
	bool cmdStopDescend(int argc, const char **argv);
	bool cmdToggleQuarterSpeed(int argc, const char **argv);
	bool cmdToggleClipping(int argc, const char **argv);
public:
	Debugger();
    ~Debugger() override {}
};

} // End of namespace Ultima8
} // End of namespace Ultima

#endif
