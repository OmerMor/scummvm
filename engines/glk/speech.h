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

#ifndef GLK_SPEECH_H
#define GLK_SPEECH_H

#include "common/events.h"
#include "glk/glk_types.h"
#include "common/singleton.h"

#if defined(USE_TTS)
#include "common/text-to-speech.h"
#include "common/ustr.h"
#endif

namespace Glk {

class Speech;

class SpeechManager {
public:
	static SpeechManager* getSpeechManagerInstance();
	void releaseSpeechManagerInstance();

	void flushSpeech(Speech *);
	void purgeSpeech(Speech *);
	void addSpeech(const uint32 *buf, size_t len, Speech *);

private:
	SpeechManager();
	~SpeechManager();

	static SpeechManager *_instance;
	int _refCount;

#if defined(USE_TTS)
	Common::U32String _speechBuffer;
	Common::TextToSpeechManager *_ttsMan;
	Common::TextToSpeechManager::Action _nextSpeechAction;
	Speech *_lastSpeechSource;
#endif
};


class Speech {
private:
	SpeechManager *_speechManager;

protected:
	Speech();
	~Speech();

	void gli_initialize_tts(void);

	void gli_tts_flush(void);

	void gli_tts_purge(void);

	void gli_tts_speak(const uint32 *buf, size_t len);

	void gli_free_tts(void);
};

} // End of namespace Glk

#endif
