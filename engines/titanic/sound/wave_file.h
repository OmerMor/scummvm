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

#ifndef TITANIC_WAVE_FILE_H
#define TITANIC_WAVE_FILE_H

#include "audio/audiostream.h"
#include "audio/mixer.h"
#include "titanic/support/string.h"

namespace Titanic {

class QSoundManager;

class CWaveFile {
public:
	QSoundManager *_owner;
	Audio::AudioStream *_stream;
	Audio::SoundHandle _soundHandle;
public:
	CWaveFile() : _owner(nullptr), _stream(nullptr) {}
	CWaveFile(QSoundManager *owner) : _owner(owner), _stream(nullptr) {}
	~CWaveFile();

	int fn1();

	/**
	 * Tries to load the specified wave file sound
	 */
	bool loadSound(const CString &name);

	/**
	 * Returns true if the wave file has data loaded
	 */
	bool isLoaded() const { return _stream != nullptr; }

	/**
	 * Return the frequency of the loaded wave file
	 */
	uint getFrequency() const;
};

} // End of namespace Titanic

#endif /* TITANIC_WAVE_FILE_H */
