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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

/*
 * This file is based on WME Lite.
 * http://dead-code.org/redir.php?target=wmelite
 * Copyright (c) 2011 Jan Nedoma
 */

#include "engines/wintermute/dcgf.h"
#include "engines/wintermute/Base/BGame.h"
#include "engines/wintermute/Base/file/BSaveThumbFile.h"
#include "engines/wintermute/PlatformSDL.h"

namespace WinterMute {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
CBSaveThumbFile::CBSaveThumbFile(CBGame *inGame): CBFile(inGame) {
	_data = NULL;
}


//////////////////////////////////////////////////////////////////////////
CBSaveThumbFile::~CBSaveThumbFile() {
	close();
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSaveThumbFile::open(const Common::String &filename) {
	close();

	if (scumm_strnicmp(filename.c_str(), "savegame:", 9) != 0) return E_FAIL;

	char *tempFilename = new char[strlen(filename.c_str()) - 8];
	strcpy(tempFilename, filename.c_str() + 9);
	for (int i = 0; i < strlen(tempFilename); i++) {
		if (tempFilename[i] < '0' || tempFilename[i] > '9') {
			tempFilename[i] = '\0';
			break;
		}
	}

	// get slot number from name
	int slot = atoi(tempFilename);
	delete [] tempFilename;

	char slotFilename[MAX_PATH + 1];
	Game->GetSaveSlotFilename(slot, slotFilename);
	CBPersistMgr *pm = new CBPersistMgr(Game);
	if (!pm) return E_FAIL;

	Game->_dEBUG_AbsolutePathWarning = false;
	if (FAILED(pm->initLoad(slotFilename))) {
		Game->_dEBUG_AbsolutePathWarning = true;
		delete pm;
		return E_FAIL;
	}
	Game->_dEBUG_AbsolutePathWarning = true;

	HRESULT res;

	if (pm->_thumbnailDataSize != 0) {
		_data = new byte[pm->_thumbnailDataSize];
		memcpy(_data, pm->_thumbnailData, pm->_thumbnailDataSize);
		_size = pm->_thumbnailDataSize;
		res = S_OK;
	} else res = E_FAIL;
	delete pm;

	return res;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSaveThumbFile::close() {
	delete[] _data;
	_data = NULL;

	_pos = 0;
	_size = 0;

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSaveThumbFile::read(void *buffer, uint32 size) {
	if (!_data || _pos + size > _size) return E_FAIL;

	memcpy(buffer, (byte *)_data + _pos, size);
	_pos += size;

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSaveThumbFile::seek(uint32 pos, TSeek origin) {
	if (!_data) return E_FAIL;

	uint32 newPos = 0;

	switch (origin) {
	case SEEK_TO_BEGIN:
		newPos = pos;
		break;
	case SEEK_TO_END:
		newPos = _size + pos;
		break;
	case SEEK_TO_CURRENT:
		newPos = _pos + pos;
		break;
	}

	if (newPos > _size) return E_FAIL;
	else _pos = newPos;

	return S_OK;
}

} // end of namespace WinterMute
