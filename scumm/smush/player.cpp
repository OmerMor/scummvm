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
#include "common/file.h"
#include "common/util.h"
#include "common/engine.h" // for debug, warning, error
#include "scumm/scumm.h"
#include "sound/mixer.h"

#include "player.h"

#include "mixer.h"
#include "renderer.h"
#include "frenderer.h"
#include "channel.h"
#include "chunk_type.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int WAIT = 100;

const int32 MAX_STRINGS = 200;

class StringResource {
private:
	struct {
		int32 id;
		char *string;
	} _strings[MAX_STRINGS];
	int32 _nbStrings;
	int32 _lastId;
	char *_lastString;
public:
	StringResource() : _nbStrings(0), _lastId(-1) {};
	~StringResource() {
		for(int32 i = 0; i < _nbStrings; i++) {
			delete []_strings[i].string;
		}
	}

	bool init(char *buffer, int32 length) {
#ifdef DEBUG
		debug(9, "parsing string resources...");
#endif
		char *def_start = strchr(buffer, '#');
		while(def_start != NULL) {
			char *def_end = strchr(def_start, '\n');
			assert(def_end != NULL);
			char *id_end = def_end;
			while(id_end >= def_start && !isdigit(*(id_end-1))) { 
				id_end--;
			}
			assert(id_end > def_start);
			char *id_start = id_end;
			while(isdigit(*(id_start - 1))) {
				id_start--;
			}
			char idstring[32];
			memcpy(idstring, id_start, id_end - id_start);
			idstring[id_end - id_start] = 0;
			int32 id = atoi(idstring);
			char *data_start = def_end;

			while(*data_start == '\n' || *data_start == '\r') {
				data_start++;
			}
			char *data_end = data_start;

			while(1) {
				if(data_end[-2] == '\r' && data_end[1] == '\n' && data_end[-1] == '\n' && data_end[0] == '\r') {
					break;
				}
				data_end++;
				if(data_end >= buffer + length) {
					data_end = buffer + length;
					break;
				}
			}

			data_end -= 2;
			assert(data_end > data_start);
			char *value = new char[data_end - data_start + 1];
			assert(value);
			memcpy(value, data_start, data_end - data_start);
			value[data_end - data_start] = 0;
			char *line_start = value;
			char *line_end;

			while ((line_end = strchr(line_start, '\n'))) {
				line_start = line_end+1;
				if (line_start[0] == '/' && line_start[1] == '/') {
					line_start += 2;
					if	(line_end[-1] == '\r')
						line_end[-1] = ' ';
					else
						*line_end++ = ' ';
					memmove(line_end, line_start, strlen(line_start)+1);
				}
			}
#ifdef DEBUG
			debug(9, "Inserting (%s)%d == \"%s\"", idstring, id, value);
#endif				
			_strings[_nbStrings].id = id;
			_strings[_nbStrings].string = value;
			_nbStrings ++;
			def_start = strchr(data_end + 2, '#');
		}
		return true;
	}

	const char *get(int32 id) {
		if(id == _lastId) {
			return _lastString;
		}
		for(int i = 0; i < _nbStrings; i++) {
			if(_strings[i].id == id) {
				_lastId = id;
				_lastString = _strings[i].string;
				return _strings[i].string;
			}
		}
		warning("invalid string id : %d", id);
		_lastId = -1;
		_lastString = "unknown string";
		return _lastString;
	}
};

void SmushPlayer::show(const char *p) {
	if(strcmp(p, "subtitles") == 0) {
		_subtitles = true;
	} else if(strcmp(p, "bgmusic") == 0) {
		_bgmusic = true;
	} else if(strcmp(p, "voices") == 0) {
		_voices = true;
	} else {
		int id = atoi(p);
		if(id < 0 || id > 36) {
			error("invalid parameter to show");
		}
		_skips[id] = true;
	}
}

void SmushPlayer::hide(const char *p) {
	if(strcmp(p, "subtitles") == 0) {
		_subtitles = false;
	} else if(strcmp(p, "bgmusic") == 0) {
		_bgmusic = false;
	} else if(strcmp(p, "voices") == 0) {
		_voices = false;
	} else {
		int32 id = atoi(p);
		if(id < 0 || id > 36) {
			error("invalid parameter to hide");
		}
		_skips[id] = false;
	}
}

SmushPlayer::SmushPlayer(Renderer * renderer, bool wait, bool sound) :
	_version(-1),
	_secondaryVersion(0),
	_soundFrequency(0),
	_nbframes(0),
	_mixer(0),
	_renderer(renderer),
	_strings(0),
	_frameSize(-1, -1),
	_frame(0),
	_outputSound(sound),
	_wait(wait),
	_alreadyInit(false),
	_codec37Called(false),
	_skipNext(false),
	_subtitles(true),
	_bgmusic(true),
	_voices(true),
	_curBuffer(0),
	_IACTchannel(-1),
	_IACTpos(0),
	_storeFrame(false),
	_frameBuffer(NULL) {
	_fr[0] = _fr[1] = _fr[2] = _fr[3] = _fr[4] = 0;
	assert(_renderer != 0);
}

SmushPlayer::~SmushPlayer() {
	clean();
}

void SmushPlayer::updatePalette(void) { 
	_renderer->setPalette(_pal); 
}

void SmushPlayer::clean() {
	if(_strings) 
		delete _strings;
	if(_fr[0]) delete _fr[0];
	if(_fr[1]) delete _fr[1];
	if(_fr[2]) delete _fr[2];
	if(_fr[3]) delete _fr[3];
	if(_fr[4]) delete _fr[4];

	if (_frameBuffer != NULL) {
		free(_frameBuffer);
	}
}

void SmushPlayer::checkBlock(const Chunk &b, Chunk::type type_expected, uint32 min_size) {
	if(type_expected != b.getType()) {
		error("Chunk type is different from expected : %d != %d", b.getType(), type_expected);
	}
	if(min_size > b.getSize()) {
		error( "Chunk size is inferior than minimum required size : %d < %d", b.getSize(), min_size);
	}
}

void SmushPlayer::handleSoundBuffer(int32 track_id, int32 index, int32 max_frames, int32 flags, int32 vol, int32 bal, Chunk &b, int32 size) {
	debug(6, "smush_player::handleSoundBuffer(%d)", track_id);
	if(!_voices && (flags & 128) == 128) {
		return;
	}
	if(!_bgmusic && (flags & 64) == 64) {
		return;
	}
	_Channel *c = _mixer->findChannel(track_id);
	if(c == 0) {
		c = new SaudChannel(track_id, _soundFrequency);
		_mixer->addChannel(c);
	}
	if(index == 0) {
		c->setParameters(max_frames, flags, vol, bal);
	}	else {
		c->checkParameters(index, max_frames, flags, vol, bal);
	}
	c->appendData(b, size);
}

void SmushPlayer::handleSoundFrame(Chunk &b) {
	checkBlock(b, TYPE_PSAD);
	debug(6, "SmushPlayer::handleSoundFrame()");
	if(!_outputSound) {
		return;
	}
	int32 track_id = b.getWord();
	int32 index = b.getWord();
	int32 max_frames = b.getWord();
	int32 flags = b.getWord();
	int32 vol = b.getByte();
	int32 bal = b.getChar();
#ifdef DEBUG
	if(index == 0) {
		debug(5, "track_id == %d, max_frames == %d, %d, %d, %d", track_id, max_frames, flags, vol, bal);
	}
#endif
	int32 size = b.getSize() - 10;
	handleSoundBuffer(track_id, index, max_frames, flags, vol, bal, b, size);
}

void SmushPlayer::handleSkip(Chunk &b) {
	checkBlock(b, TYPE_SKIP, 4);
	int32 code = b.getDword();
	debug(6, "SmushPlayer::handleSkip(%d)", code);
	if(code >= 0 && code < 37)
		_skipNext = _skips[code];
	else
		_skipNext = true;
}

void SmushPlayer::handleStore(Chunk &b) {
	checkBlock(b, TYPE_STOR, 4);
	_storeFrame = true;
	debug(6, "SmushPlayer::handleStore()");
}

void SmushPlayer::handleFetch(Chunk &b) {
	checkBlock(b, TYPE_FTCH, 6);
	debug(6, "SmushPlayer::handleFetch()");

	if(_curBuffer == NULL) {
		_curBuffer = _renderer->lockFrame(_frame);
	}

	if (_frameBuffer != NULL) {
		memcpy(_curBuffer, _frameBuffer, _frameSize.getX() * _frameSize.getY());
	}
}

void SmushPlayer::handleImuseBuffer(int32 track_id, int32 index, int32 nbframes, int32 size, int32 unk1, int32 track_flags, Chunk &b, int32 bsize) {
	int32 track = (track_flags << 16) | track_id;

	_Channel *c = _mixer->findChannel(track);
	if(c == 0) {
		c = new ImuseChannel(track, _soundFrequency);
		_mixer->addChannel(c);
	}
	if(index == 0)
		c->setParameters(nbframes, size, track_flags, unk1);
	else
		c->checkParameters(index, nbframes, size, track_flags, unk1);
	c->appendData(b, bsize);
}

void SmushPlayer::handleImuseAction8(Chunk &b, int32 flags, int32 unknown, int32 track_flags) {
	assert(flags == 46 && unknown == 0);
	int32 track_id = b.getWord();
	int32 index = b.getWord();
	int32 nbframes = b.getWord();
	int32 size = b.getDword();
	int32 bsize = b.getSize() - 18;
	if (g_scumm->_gameId != GID_CMI) {
		handleImuseBuffer(track_id, index, nbframes, size, unknown, track_flags, b, bsize);
	} else {
		byte output_data[4096];
		byte *src = (byte *)malloc(bsize);
		b.read(src, bsize);
		byte *d_src = src;
		byte value;

		do {
			if (bsize == 0)
				break;
			if (_IACTpos >= 2) {
				int32 len = READ_BE_UINT16(_IACToutput) + 2;
				len -= _IACTpos;
				if (len > bsize) {
					memcpy(_IACToutput + _IACTpos, d_src, bsize);
					_IACTpos += bsize;
					bsize = 0;
				} else {
					memcpy(_IACToutput + _IACTpos, d_src, len);
					byte *dst = output_data;
					byte *d_src2 = _IACToutput;
					d_src2 += 2;
					int32 count = 1024;
					byte variable1 = *d_src2++;
					byte variable2 = variable1 >> 4;
					variable1 &= 0x0f;
					do {
						value = *(d_src2++);
						if (value == 0x80) {
							*dst++ = *d_src2++;
							*dst++ = *d_src2++;
						} else {
							int16 val = (int8)value << variable2;
							*dst++ = val>> 8;
							*dst++ = (byte)(val);
						}
						value = *(d_src2++);
						if (value == 0x80) {
							*dst++ = *d_src2++;
							*dst++ = *d_src2++;
						} else {
							int16 val = (int8)value << variable1;
							*dst++ = val>> 8;
							*dst++ = (byte)(val);
						}
					} while (--count);

					if (_IACTchannel == -1) {
						_IACTchannel = g_scumm->_mixer->playStream(NULL, -1, output_data, 0x1000, 22050,
															SoundMixer::FLAG_STEREO | SoundMixer::FLAG_16BITS, -1, 200000);
					} else {
						g_scumm->_mixer->append(_IACTchannel, output_data, 0x1000, 22050,
															SoundMixer::FLAG_STEREO | SoundMixer::FLAG_16BITS);
					}

					bsize -= len;
					d_src += len;
					_IACTpos = 0;
				}
			} else {
				if (bsize == 1) {
					if (_IACTpos != 0) {
						*(_IACToutput + 1) = *d_src++;
						_IACTpos = 2;
						bsize--;
						continue;
					}
					bsize = 0;
					*(_IACToutput + 0) = *d_src;
					_IACTpos = 1;
					continue;
				} else if (_IACTpos == 0) {
					*(_IACToutput + 0) = *d_src++;
					bsize--;
				}
				*(_IACToutput + 1) = *d_src++;
				_IACTpos = 2;
				bsize--;
			}	
		} while (bsize != 0);
	
		free(src);
	}
}

void SmushPlayer::handleImuseAction(Chunk &b) {
	checkBlock(b, TYPE_IACT, 8);
	debug(6, "SmushPlayer::handleImuseAction()");
	if(!_outputSound) {
		return;
	}
	int32 code = b.getWord();
	int32 flags = b.getWord();
	int32 unknown = b.getShort();
	int32 track_flags = b.getWord();
#ifdef DEBUG
	debug(5, "handleImuseAction(%d, %d, %d, %d)", code, flags, unknown, track_flags);
#endif
	switch(code) {
		case 8:
			handleImuseAction8(b, flags, unknown, track_flags);
			break;
#ifdef DEBUG
		default: {
				debug(9, "%5.5d %d %8.8d %4.4d", track_flags, flags, unknown);
			}
#endif
	}
}

void SmushPlayer::handleTextResource(Chunk &b) {
	int32 pos_x = b.getShort();
	int32 pos_y = b.getShort();
	int32 flags = b.getShort();
	int32 left = b.getShort();
	int32 top = b.getShort();
	int32 width = b.getShort();
	/*int32 height =*/ b.getShort();
	/*int32 unk2 =*/ b.getWord();

	const char *str;
	char *string = NULL;
	char *string2 = NULL;
	if (b.getType() == TYPE_TEXT) {
		string = (char*)malloc(b.getSize() - 16);
		str = string;
		b.read(string, b.getSize() - 16);
	} else {
		int32 string_id = b.getWord();
#ifdef DEBUG
		debug(6, "SmushPlayer::handleTextResource(%d)", string_id);
#endif
		if(!_strings)
			return;
		str = _strings->get(string_id);
	}

	// if subtitles disabled and bit 3 is set, then do not draw
	if((!_subtitles) && ((flags & 8) == 8))
		return;

	FontRenderer *fr = _fr[0];
	int32 color = 15;
	while(*str == '/') {
		str++; // For Full Throttle text resources
	}

	if (g_scumm->_gameId == GID_CMI) {
		g_scumm->translateText((byte *)str - 1, g_scumm->_transText);
		while(*str++ != '/');
		string2 = (char*)g_scumm->_transText;

		// If string2 contains formatting information there probably
		// wasn't any translation for it in the language.tab file. In
		// that case, pretend there is no string2.
		if (string2[0] == '^')
			string2[0] = 0;
	}

	while(str[0] == '^') {
		switch(str[1]) {
		case 'f':
			{
				int id = str[3] - '0';
				str += 4;
				fr = _fr[id]; 
			}
			break;
		case 'c':
			{
				color = str[4] - '0' + 10 *(str[3] - '0');
				str += 5;
			}
			break;
		default:
			error("invalid escape code in text string");
		}
	}
	assert(fr != 0);
	fr->setColor(color);
	if(!_curBuffer) {
		_curBuffer = _renderer->lockFrame(_frame);
	}

	if (g_scumm->_gameId != GID_CMI) {
		string2 = (char *)str;
	}
	if (g_scumm->_gameId == GID_CMI) {
		if (string2[0] == 0) {
			string2 = (char *)str;
		}
	}

	// flags:
	// bit 0 - center				1
	// bit 1 - not used			2
	// bit 2 - ???					4
	// bit 3 - wrap around	8
	switch (flags) {
		case 0: 
			fr->drawStringAbsolute(string2, _curBuffer, _frameSize, pos_x, pos_y);
			break;
		case 1:
			fr->drawStringCentered(string2, _curBuffer, _frameSize, MAX(pos_y, top), left, width, pos_x);
			break;
		case 4:
			fr->drawStringAbsolute(string2, _curBuffer, _frameSize, pos_x, pos_y);
			break;
		case 5:
			fr->drawStringCentered(string2, _curBuffer, _frameSize, MAX(pos_y, top), left, width, pos_x);
			break;
		case 8:
			fr->drawStringWrap(string2, _curBuffer, _frameSize, pos_x, MAX(pos_y, top), width);
			break;
		case 9:
			fr->drawStringCentered(string2, _curBuffer, _frameSize, MAX(pos_y, top), left, width, pos_x);
			break;
		case 12:
			fr->drawStringWrap(string2, _curBuffer, _frameSize, pos_x, MAX(pos_y, top), width);
			break;
		case 13:
			fr->drawStringWrapCentered(string2, _curBuffer, _frameSize, pos_x, MAX(pos_y, top), width);
			break;
		default:
			warning("SmushPlayer::handleTextResource. Not handled flags: %d\n", flags);
	}

	if (string != NULL) {
		free (string);
	}
}

void SmushPlayer::readPalette(Palette &out, Chunk &in) {
	byte buffer[768];
	in.read(buffer, 768);
	out = Palette(buffer);
}

void SmushPlayer::handleDeltaPalette(Chunk &b) {
	checkBlock(b, TYPE_XPAL);
	debug(6, "SmushPlayer::handleDeltaPalette()");
	if(b.getSize() == 768 * 3 + 4) {
		int32 unk1, num;
		unk1 = b.getWord();
		num = b.getWord();
		for(int32 i = 0; i < 768; i++) {
			_deltaPal[i] = b.getWord();
		}
		readPalette(_pal, b);
		updatePalette();
	} else if(b.getSize() == 6) {
		int32 unk1, num, unk2;
		unk1 = b.getWord();
		num = b.getWord();
		unk2 = b.getWord();
		for(int32 i = 0; i < 256; i++) {
			_pal[i].delta(_deltaPal + 3 * i);
		}
		updatePalette();
	} else {
		error("wrong size for DeltaPalette");
	}
}

void SmushPlayer::handleNewPalette(Chunk &b) {
	checkBlock(b, TYPE_NPAL, 768);
	debug(6, "SmushPlayer::handleNewPalette()");
	readPalette(_pal, b);
	updatePalette();
}

void SmushPlayer::decodeCodec(Chunk &src, const Rect &r, Decoder &codec) {
	assert(_curBuffer);

	int32 chunk_size = src.getSize() - 14;
	byte *chunk_buffer = (byte *)malloc(chunk_size);
	assert(chunk_buffer);
	src.read(chunk_buffer, chunk_size);
	codec.decode((byte *)_curBuffer, chunk_buffer, chunk_size);
	free(chunk_buffer);

	if (_storeFrame == true) {
		if (_frameBuffer == NULL) {
			_frameBuffer = (byte *)malloc(_frameSize.getX() * _frameSize.getY());
		}
		memcpy(_frameBuffer, _curBuffer, _frameSize.getX() * _frameSize.getY());
		_storeFrame = false;
	}
}

void SmushPlayer::initSize(const Rect &r, bool always, bool transparent) {
	if(_codec37Called) _alreadyInit = true;

	if(!_alreadyInit || _frameSize.getX() < r.right() || _frameSize.getY() < r.bottom() || always) {
		if(_curBuffer) {
			_renderer->unlockFrame();
			_curBuffer = 0;
		}
		_frameSize = r.bottomRight();
		_renderer->initFrame(_frameSize);
	}

	if(_curBuffer) {
		_renderer->unlockFrame();
		_curBuffer = 0;
	}

	_curBuffer = _renderer->lockFrame(_frame);
	if(!_alreadyInit && transparent) {
		memset(_curBuffer, 0, _frameSize.getX() * _frameSize.getY());
	}

	_codec1.initSize(_frameSize, r);
	_codec37.initSize(_frameSize, r);
	_codec47.initSize(_frameSize, r);
	_codec44.initSize(_frameSize, r);
	_alreadyInit = true;
}

void SmushPlayer::handleFrameObject(Chunk &b) {
	checkBlock(b, TYPE_FOBJ, 14);
	if(_skipNext) {
		_skipNext = false;
		return;
	}
	int codec = b.getWord();
	debug(6, "SmushPlayer::handleFrameObject(%d)", codec);
	uint16 left = b.getWord();
	uint16 top = b.getWord();
	uint16 width = b.getWord();
	uint16 height = b.getWord();
	Rect r(left, top, left + width, top + height);
	uint16 data[2];
	data[1] = b.getWord();
	data[0] = b.getWord();
#ifdef DEBUG
	debug(5, "Frame pos : %d, %d", left, top);
	debug(5, "Frame size : %dx%d", width, height);
	debug(5, "Codec : %d", codec);
#endif
	switch (codec) {
	case 3:
	case 1:
		initSize(r, false, true);
		decodeCodec(b, r, _codec1);
		break;
	case 37:
		initSize(r, true, false);
		decodeCodec(b, r, _codec37);
		_codec37Called = true;
		break;
	case 47:
		initSize(r, true, false);
		decodeCodec(b, r, _codec47);
		_codec37Called = true;
		break;
	case 21:
	case 44:
		initSize(r, true, true);
		decodeCodec(b, r, _codec44);
		break;
	default:
		error("Invalid codec for frame object : %d", (int32)codec);
	}
}

void SmushPlayer::handleFrame(Chunk &b) {
	checkBlock(b, TYPE_FRME);
	debug(6, "SmushPlayer::handleFrame(%d)", _frame);
	_alreadyInit = false;
	_skipNext = false;

	while(!b.eof()) {
		Chunk *sub = b.subBlock();
		if(sub->getSize() & 1) b.seek(1);
		switch(sub->getType()) {
			case TYPE_NPAL:
				handleNewPalette(*sub);
				break;
			case TYPE_FOBJ:
				handleFrameObject(*sub);
				break;
			case TYPE_PSAD:
				handleSoundFrame(*sub);
				break;
			case TYPE_TRES:
				handleTextResource(*sub);
				break;
			case TYPE_XPAL:
				handleDeltaPalette(*sub);
				break;
			case TYPE_IACT:
				handleImuseAction(*sub);
				break;
			case TYPE_STOR:
				handleStore(*sub);
				break;
			case TYPE_FTCH:
				handleFetch(*sub);
				break;
			case TYPE_SKIP:
				handleSkip(*sub);
				break;
			case TYPE_TEXT:
				handleTextResource(*sub);
				break;
			default:
				error("Unknown frame subChunk found : %s, %d", Chunk::ChunkString(sub->getType()), sub->getSize());
		}
		delete sub;
	}
	if(_curBuffer) {
		_renderer->unlockFrame();
		_curBuffer = 0;
	}
	if(_outputSound)
		_mixer->handleFrame();
#ifdef DEBUG
	debug(5, "===================END OF FRAME========================");
#endif
	_renderer->flipFrame();
	if(_wait)
		_renderer->wait(WAIT);
	_frame++;
}

void SmushPlayer::handleAnimHeader(Chunk &b) {
	checkBlock(b, TYPE_AHDR, 774);
	debug(6, "SmushPlayer::handleAnimHeader()");
	_version = b.getWord();
	_nbframes = b.getWord();
	b.getWord();
	_renderer->startDecode(_fname, _version, _nbframes);
	readPalette(_pal, b);
	updatePalette();
	if(_version == 2) {
		_secondaryVersion = b.getDword();
		b.getDword();
		if(_secondaryVersion != 10 && _secondaryVersion != 0 && _secondaryVersion != 12 && _secondaryVersion != 15 && _secondaryVersion != 14) {
			error("Wrong secondary version number for SMUSH animation");
		}
	} else if(_version > 2) {
		error("Wrong primary version number for SMUSH animation");
	}
	if(_outputSound) {
		_soundFrequency = 22050;
		_mixer = _renderer->getMixer();
		if(_mixer) {
			_mixer->init();
		} else {
			_outputSound = false;
		}
	}
}

static StringResource *getStrings(const char *file, const char *directory, bool is_encoded) {
	debug(7, "trying to read text ressources from %s", file);
	File theFile;

	theFile.open(file, directory);
	if (!theFile.isOpen()) {
		return 0;
	}
	int32 length = theFile.size();
	char *filebuffer = new char [length + 1];
	assert(filebuffer);
	theFile.read(filebuffer, length);
	filebuffer[length] = 0;

	if(is_encoded) {
		static const int32 ETRS_HEADER_LENGTH = 16;
		assert(length > ETRS_HEADER_LENGTH);
		Chunk::type type = READ_BE_UINT32(filebuffer);

		if(type != TYPE_ETRS) {
			delete [] filebuffer;
			return getStrings(file, directory, false);
		}

		char *old = filebuffer;
		filebuffer = new char[length - ETRS_HEADER_LENGTH + 1];
		for(int32 i = ETRS_HEADER_LENGTH; i < length; i++) {
			filebuffer[i - ETRS_HEADER_LENGTH] = old[i] ^ 0xCC;
		}
		filebuffer[length - ETRS_HEADER_LENGTH] = '\0';
		delete []old;
		length -= ETRS_HEADER_LENGTH;
	}
	StringResource *sr = new StringResource;
	assert(sr);
	sr->init(filebuffer, length);
	delete []filebuffer;
	return sr;
}

bool SmushPlayer::readString(const char *file, const char *directory, bool &ft) {
	const char *i = strrchr(file, '.');
	if(i == NULL) {
		error("invalid filename : %s", file);
	}
	char fname[260];
	memcpy(fname, file, i - file);
	strcpy(fname + (i - file), ".trs");
	if((_strings = getStrings(fname, directory, false)) != 0) {
		ft = true;
		return true;
	}

	if((_strings = getStrings("digtxt.trs", directory, true)) != 0) {
		ft = false;
		return true;
	}
	return false;
}

static FontRenderer *loadFont(const char *file, const char *directory, bool original = false) {
#ifdef DEBUG
	debug(5, "loading font from \"%s\"", file);
#endif
	FontRenderer *fr = new FontRenderer(original);
	SmushPlayer p(fr, false, false);
	p.play(file, directory);
	return fr;
}

bool SmushPlayer::play(const char *file, const char *directory) {
#ifdef DEBUG
	debug(5, "start of animation : %s", file);
#endif	
	clean();
	
	if(_wait) {
		bool isFullthrottle = false;
		if(!readString(file, directory, isFullthrottle)) {
#ifdef DEBUG
			debug(2, "unable to read text information for \"%s\"", file);
#endif	
		}
		if((_strings) || (g_scumm->_gameId == GID_CMI)) {
			if(isFullthrottle) {
				_fr[0] = loadFont("scummfnt.nut", directory, true);
				_fr[2] = loadFont("titlfnt.nut", directory, true);
			} else {
				for(int i = 0; i < 4; i++) {
					char file_font[11];
					sprintf((char *)&file_font, "font%d.nut", i);
					_fr[i] = loadFont(file_font, directory, i != 0);
				}
			}
		}
		if(g_scumm->_gameId == GID_CMI) {
			for(int i = 0; i < 5; i++) {
				char file_font[11];
				sprintf((char *)&file_font, "font%d.nut", i);
				_fr[i] = loadFont(file_font, directory, false);
			}
		}
	}

	File test;
	test.open(file, directory);
	if (!test.isOpen()) {
		warning("Missing smush file %s", file);
		return true;
	}
	test.close();

	FileChunk base = FileChunk(file, directory);

	checkBlock(base, TYPE_ANIM); 

	while(!base.eof()) {
		Chunk *sub = base.subBlock();
		switch(sub->getType()) {
			case TYPE_AHDR:
				handleAnimHeader(*sub);
				break;
			case TYPE_FRME:
				handleFrame(*sub);
				break;
			default:
				error("Unknown Chunk found : %d, %d", sub->getType(), sub->getSize());
		}
		delete sub;
		if(_renderer->prematureClose()) {
			break;
		}
	}
#ifdef DEBUG
	debug(5, "end of animation");
#endif	
	if(_outputSound) {
		_mixer->stop();
	}
	return true;
}
