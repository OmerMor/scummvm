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

#include "common/scummsys.h"

#include "common/config-manager.h"
#include "common/debug-channels.h"
#include "common/debug.h"
#include "common/events.h"
#include "common/file.h"
#include "common/random.h"
#include "common/fs.h"
#include "common/keyboard.h"
#include "common/substream.h"
#include "common/str.h"

#include "graphics/cursorman.h"
#include "graphics/surface.h"
#include "graphics/palette.h"
#include "graphics/pixelformat.h"

#include "engines/util.h"
#include "engines/advancedDetector.h"

#include "audio/audiostream.h"

#include "prince/prince.h"
#include "prince/font.h"
#include "prince/graphics.h"
#include "prince/script.h"
#include "prince/debugger.h"
#include "prince/object.h"
#include "prince/mob.h"
#include "prince/sound.h"
#include "prince/variatxt.h"
#include "prince/flags.h"
#include "prince/font.h"
#include "prince/mhwanh.h"
#include "prince/cursor.h"
#include "prince/archive.h"
#include "prince/hero.h"
#include "prince/resource.h"

namespace Prince {

void PrinceEngine::debugEngine(const char *s, ...) {
	char buf[STRINGBUFLEN];
	va_list va;

    va_start(va, s);
    vsnprintf(buf, STRINGBUFLEN, s, va);
    va_end(va);

	debug("Prince::Engine frame %08ld %s", _frameNr, buf);
}

PrinceEngine::PrinceEngine(OSystem *syst, const PrinceGameDescription *gameDesc) : 
	Engine(syst), _gameDescription(gameDesc), _graph(nullptr), _script(nullptr), _interpreter(nullptr), _flags(nullptr),
	_locationNr(0), _debugger(nullptr), _midiPlayer(nullptr),
	_cameraX(0), _newCameraX(0), _frameNr(0), _cursor1(nullptr), _cursor2(nullptr), _font(nullptr),
	_walizkaBmp(nullptr), _roomBmp(nullptr), _cursorNr(0) {

	// Debug/console setup
	DebugMan.addDebugChannel(DebugChannel::kScript, "script", "Prince Script debug channel");
	DebugMan.addDebugChannel(DebugChannel::kEngine, "engine", "Prince Engine debug channel");

	DebugMan.enableDebugChannel("script");

	memset(_voiceStream, 0, sizeof(_voiceStream));

	gDebugLevel = 10;
}

PrinceEngine::~PrinceEngine() {
	DebugMan.clearAllDebugChannels();

	delete _rnd;
	delete _debugger;
	delete _cursor1;
	delete _cursor2;
	delete _midiPlayer;
	delete _script;
	delete _flags;
	delete _interpreter;
	delete _font;
	delete _roomBmp;
	delete _walizkaBmp;
	delete _variaTxt;
	delete[] _talkTxt;
	delete _graph;
	delete _mainHero;
	delete _secondHero;

	for (uint32 i = 0; i < _objList.size(); ++i) {
		delete _objList[i];
	}
	_objList.clear();
}

GUI::Debugger *PrinceEngine::getDebugger() {
	return _debugger;
}

void PrinceEngine::init() {

	const Common::FSNode gameDataDir(ConfMan.get("path"));
	
	debugEngine("Adding all path: %s", gameDataDir.getPath().c_str());

	PtcArchive *all = new PtcArchive();
	if (!all->open("all/databank.ptc")) 
		error("Can't open all/databank.ptc");

	PtcArchive *voices = new PtcArchive();
	if (!voices->open("data/voices/databank.ptc"))
		error("Can't open data/voices/databank.ptc");

	PtcArchive *sound = new PtcArchive();
	if (!sound->open("sound/databank.ptc"))
		error("Can't open sound/databank.ptc");

	SearchMan.add("all", all);
	SearchMan.add("data/voices", voices);
	SearchMan.add("sound", sound);

	_graph = new GraphicsMan(this);

	_rnd = new Common::RandomSource("prince");
	_debugger = new Debugger(this);

	_midiPlayer = new MusicPlayer(this);
	 
	_font = new Font();
	Resource::loadResource(_font, "all/font1.raw");

	_walizkaBmp = new MhwanhDecoder();
	Resource::loadResource(_walizkaBmp, "all/walizka");

	_script = new Script();
	Resource::loadResource(_script, "all/skrypt.dat");

	_flags = new InterpreterFlags();
	_interpreter = new Interpreter(this, _script, _flags);

	_variaTxt = new VariaTxt();
	Resource::loadResource(_variaTxt, "all/variatxt.dat");
	
	_cursor1 = new Cursor();
	Resource::loadResource(_cursor1, "all/mouse1.cur");

	_cursor2 = new Cursor();
	Resource::loadResource(_cursor2, "all/mouse2.cur");

	Common::SeekableReadStream *talkTxtStream = SearchMan.createReadStreamForMember("all/talktxt.dat");
	if (!talkTxtStream) {
		error("Can't load talkTxtStream");
		return;
	}
	_talkTxtSize = talkTxtStream->size();
	_talkTxt = new byte[_talkTxtSize];
	talkTxtStream->read(_talkTxt, _talkTxtSize);

	delete talkTxtStream;

	_roomBmp = new Image::BitmapDecoder();

	_mainHero = new Hero();
	_secondHero = new Hero();

	_mainHero->loadAnimSet(0);
}

void PrinceEngine::showLogo() {
	MhwanhDecoder logo;
	if (Resource::loadResource(&logo, "logo.raw")) {
		_graph->setPalette(logo.getPalette());
		_graph->draw(0, 0, logo.getSurface());
		_graph->update();
		_system->delayMillis(700);
	}
}

Common::Error PrinceEngine::run() {

	init();

	showLogo();

	mainLoop();

	return Common::kNoError;
}

bool AnimListItem::loadFromStream(Common::SeekableReadStream &stream) {
	int32 pos = stream.pos();

	uint16 type = stream.readUint16LE();
	if (type == 0xFFFF) {
		return false;
	}
	_type = type;
	_fileNumber = stream.readUint16LE();
	_startPhase = stream.readUint16LE();
	_endPhase = stream.readUint16LE();
	_loopPhase = stream.readUint16LE();
	_x = stream.readSint16LE();
	_y = stream.readSint16LE();
	_loopType = stream.readUint16LE();
	_nextAnim = stream.readUint16LE();
	_flags = stream.readUint16LE();

	debug("AnimListItem type %d, fileNumber %d, x %d, y %d, flags %d", _type, _fileNumber, _x, _y, _flags);


	// 32 byte aligment
	stream.seek(pos + 32);

	return true;
}

bool PrinceEngine::loadLocation(uint16 locationNr) {
	_flicPlayer.close();

	memset(_textSlots, 0, sizeof(_textSlots));
	for(uint32 sampleId = 0; sampleId < MAX_SAMPLES; ++sampleId) {
		stopSample(sampleId);
	}

	debugEngine("PrinceEngine::loadLocation %d", locationNr);
	const Common::FSNode gameDataDir(ConfMan.get("path"));
	SearchMan.remove(Common::String::format("%02d", _locationNr));

	_locationNr = locationNr;
	_debugger->_locationNr = locationNr;
	_cameraX = 0;
	_newCameraX = 0;
	
	_flags->setFlagValue(Flags::CURRROOM, _locationNr);
	_interpreter->stopBg();

	changeCursor(0);

	const Common::String locationNrStr = Common::String::format("%02d", _locationNr);
	debugEngine("loadLocation %s", locationNrStr.c_str());

	PtcArchive *locationArchive = new PtcArchive();
	if (!locationArchive->open(locationNrStr + "/databank.ptc"))
		error("Can't open location %s", locationNrStr.c_str());

	SearchMan.add(locationNrStr, locationArchive);

	const char *musName = MusicPlayer::_musTable[MusicPlayer::_musRoomTable[locationNr]];
	_midiPlayer->loadMidi(musName);

	// load location background, replace old one
	Resource::loadResource(_roomBmp, "room");
	if (_roomBmp->getSurface()) {
		_sceneWidth = _roomBmp->getSurface()->w;
	}

	_mobList.clear();
	Resource::loadResource(_mobList, "mob.lst", false);

	for (uint32 i = 0; i < _objList.size(); ++i) {
		delete _objList[i];
	}
	_objList.clear();
	Resource::loadResource(_objList, "obj.lst", false);

	_animList.clear();
	Resource::loadResource(_animList, "anim.lst", false);

	return true;
}

void PrinceEngine::changeCursor(uint16 curId) {
	_debugger->_cursorNr = curId;

	const Graphics::Surface *curSurface = nullptr;

	uint16 hotspotX = 0;
	uint16 hotspotY = 0;

	switch(curId) {
		case 0:
			CursorMan.showMouse(false);
			return;
		case 1:
			curSurface = _cursor1->getSurface();
			break;
		case 2:
			curSurface = _cursor2->getSurface();
			hotspotX = curSurface->w >> 1;
			hotspotY = curSurface->h >> 1;
			break;
	}

	CursorMan.replaceCursorPalette(_roomBmp->getPalette(), 0, 255);
	CursorMan.replaceCursor(
		curSurface->getBasePtr(0, 0), 
		curSurface->w, curSurface->h, 
		hotspotX, hotspotY, 
		255, false,
		&curSurface->format
	);
	CursorMan.showMouse(true);
}

bool PrinceEngine::playNextFrame() {
	if (!_flicPlayer.isVideoLoaded())
		return false;

	const Graphics::Surface *s = _flicPlayer.decodeNextFrame();
	if (s) {
		_graph->drawTransparent(0, 0, s);
		_graph->change();
	} else if (_flicLooped) {
        _flicPlayer.rewind();
        playNextFrame();
    }

	return true;
}

void PrinceEngine::playSample(uint16 sampleId, uint16 loopType) {
	if (_voiceStream[sampleId]) {

		if (_mixer->isSoundIDActive(sampleId)) {
			return;
		}

		Audio::AudioStream *audioStream = Audio::makeWAVStream(_voiceStream[sampleId], DisposeAfterUse::YES);
		if (loopType) {
			audioStream = new Audio::LoopingAudioStream((Audio::RewindableAudioStream*)audioStream, 0, DisposeAfterUse::NO);
		}
		_mixer->playStream(Audio::Mixer::kSFXSoundType, &_soundHandle[sampleId], audioStream, sampleId);
	}
}

void PrinceEngine::stopSample(uint16 sampleId) {
	_mixer->stopID(sampleId);
	_voiceStream[sampleId] = nullptr;
}

bool PrinceEngine::loadSample(uint32 sampleSlot, const Common::String &streamName) {
	// FIXME: This is just a workaround streamName is a path 
	// SOUND\\SCIERKA1.WAV for now only last path component is used
	Common::String normalizedPath = lastPathComponent(streamName, '\\');

	debugEngine("loadSample slot %d, name %s", sampleSlot, normalizedPath.c_str());

	_mixer->stopID(sampleSlot);
	_voiceStream[sampleSlot] = nullptr;
	_voiceStream[sampleSlot] = SearchMan.createReadStreamForMember(normalizedPath);
	if (_voiceStream[sampleSlot] == nullptr) {
		error("Can't load sample %s to slot %d", normalizedPath.c_str(), sampleSlot);
	}
	return _voiceStream[sampleSlot] == nullptr;
}

bool PrinceEngine::loadVoice(uint32 slot, uint32 sampleSlot, const Common::String &streamName) {
	debugEngine("Loading wav %s slot %d", streamName.c_str(), slot);

	if (slot > MAXTEXTS) {
		error("Text slot bigger than MAXTEXTS %d", MAXTEXTS);
		return false;
	}

	_voiceStream[sampleSlot] = SearchMan.createReadStreamForMember(streamName);
	if (!_voiceStream[sampleSlot]) {
		error("Can't open %s", streamName.c_str());
		return false;
	}

	uint32 id = _voiceStream[sampleSlot]->readUint32LE();
	if (id != 0x46464952) {
		error("It's not RIFF file %s", streamName.c_str());
		return false;
	}

	_voiceStream[sampleSlot]->skip(0x20);
	id = _voiceStream[sampleSlot]->readUint32LE();
	if (id != 0x61746164) {
		error("No data section in %s id %04x", streamName.c_str(), id);
		return false;
	}

	id = _voiceStream[sampleSlot]->readUint32LE();
	debugEngine("SetVoice slot %d time %04x", slot, id); 
	id <<= 3;
	id /= 22050;
	id += 2;

	_textSlots[slot]._time = id;

	debugEngine("SetVoice slot %d time %04x", slot, id); 
	_voiceStream[sampleSlot]->seek(0);

	return true;
}

bool PrinceEngine::loadAnim(uint16 animNr, bool loop) {
	Common::String streamName = Common::String::format("AN%02d", animNr);
	Common::SeekableReadStream * flicStream = SearchMan.createReadStreamForMember(streamName);

	if (!flicStream) {
		error("Can't open %s", streamName.c_str());
		return false;
	}

	if (!_flicPlayer.loadStream(flicStream)) {
		error("Can't load flic stream %s", streamName.c_str());
	}

	debugEngine("%s loaded", streamName.c_str());
    _flicLooped = loop;
	_flicPlayer.start();
	playNextFrame();
	return true;
}

void PrinceEngine::scrollCameraLeft(int16 delta) {
    if (_newCameraX > 0) {
        if (_newCameraX < delta)
            _newCameraX = 0;
        else
            _newCameraX -= delta;
    }   
}

void PrinceEngine::scrollCameraRight(int16 delta) {
    if (_newCameraX != _sceneWidth - 640) {
        if (_sceneWidth - 640 < delta + _newCameraX)
            delta += (_sceneWidth - 640) - (delta + _newCameraX);
        _newCameraX += delta;
        debugEngine("PrinceEngine::scrollCameraRight() _newCameraX = %d; delta = %d", _newCameraX, delta);
    }   
}

void PrinceEngine::keyHandler(Common::Event event) {
	uint16 nChar = event.kbd.keycode;
	switch (nChar) {
	case Common::KEYCODE_d:
		if (event.kbd.hasFlags(Common::KBD_CTRL)) {
			getDebugger()->attach();
		}
		break;
	case Common::KEYCODE_LEFT:
		scrollCameraLeft(32);
		break;
	case Common::KEYCODE_RIGHT:
		scrollCameraRight(32);
		break;
	case Common::KEYCODE_ESCAPE:
		_flags->setFlagValue(Flags::ESCAPED2, 1);
		break;
	}
}

void PrinceEngine::hotspot() {
	Common::Point mousepos = _system->getEventManager()->getMousePos();
	Common::Point mousePosCamera(mousepos.x + _cameraX, mousepos.y);

	for (Common::Array<Mob>::const_iterator it = _mobList.begin()
		; it != _mobList.end() ; ++it) {
		const Mob& mob = *it;
		if (mob._visible)
			continue;
		if (mob._rect.contains(mousePosCamera)) {
			uint16 textW = 0;
			for (uint16 i = 0; i < mob._name.size(); ++i)
				textW += _font->getCharWidth(mob._name[i]);

			uint16 x = mousepos.x - textW/2;
			if (x > _graph->_frontScreen->w)
				x = 0;

			if (x + textW > _graph->_frontScreen->w)
				x = _graph->_frontScreen->w - textW;

			uint16 y = mousepos.y - _font->getFontHeight();
			if (y > _graph->_frontScreen->h)
				y = _font->getFontHeight() - 2;

			_font->drawString(
				_graph->_frontScreen, 
				mob._name, 
				x,
				y,
				_graph->_frontScreen->w,
				216
			);
			break;
		}
	}
}

void PrinceEngine::printAt(uint32 slot, uint8 color, const char *s, uint16 x, uint16 y) {

	debugC(1, DebugChannel::kEngine, "PrinceEngine::printAt slot %d, color %d, x %02d, y %02d, str %s", slot, color, x, y, s);

	Text &text = _textSlots[slot];
	text._str = s;
	text._x = x;
	text._y = y;
	text._color = color;
}

uint32 PrinceEngine::getTextWidth(const char *s) {
    uint16 textW = 0;
	while (*s) {
        textW += _font->getCharWidth(*s) + _font->getKerningOffset(0, 0);
		++s;
    }
    return textW;
}

void PrinceEngine::showTexts() {
	for (uint32 slot = 0; slot < MAXTEXTS; ++slot) {
		Text& text = _textSlots[slot];
		if (!text._str && !text._time)
			continue;

		Common::Array<Common::String> lines;
		_font->wordWrapText(text._str, _graph->_frontScreen->w, lines);

		for (uint8 i = 0; i < lines.size(); ++i) {
			_font->drawString(
				_graph->_frontScreen,
				lines[i],
				text._x - getTextWidth(lines[i].c_str())/2,
				text._y - (lines.size() - i) * (_font->getFontHeight()),
				_graph->_frontScreen->w,
				text._color
			);
		}

		--text._time;
		if (text._time == 0) {
			text._str = nullptr;
		}
	}
}

void PrinceEngine::drawScreen() {
	const Graphics::Surface *roomSurface = _roomBmp->getSurface();	
	if (roomSurface) {
		_graph->setPalette(_roomBmp->getPalette());
		const Graphics::Surface visiblePart = roomSurface->getSubArea(Common::Rect(_cameraX, 0, roomSurface->w, roomSurface->h));
		_graph->draw(0, 0, &visiblePart);
	}

	if (_mainHero->_visible) {
		const Graphics::Surface *mainHeroSurface = _mainHero->getSurface();

		if (mainHeroSurface) 
			_graph->drawTransparent(_mainHero->_middleX, _mainHero->_middleY, mainHeroSurface);
	}

	playNextFrame();

	//if (_objectList)
	//	  _graph->drawTransparent(_objectList->getSurface());

	hotspot();

	showTexts();

	getDebugger()->onFrame();

	_graph->update();
}

void PrinceEngine::mainLoop() {

	changeCursor(0);

	while (!shouldQuit()) {
		uint32 currentTime = _system->getMillis();

		Common::Event event;
		Common::EventManager *eventMan = _system->getEventManager();
		while (eventMan->pollEvent(event)) {
			switch (event.type) {
			case Common::EVENT_KEYDOWN:
				keyHandler(event);
				break;
			case Common::EVENT_KEYUP:
				break;
			case Common::EVENT_MOUSEMOVE:
				break;
			case Common::EVENT_LBUTTONDOWN:
			case Common::EVENT_RBUTTONDOWN:
				break;
			case Common::EVENT_LBUTTONUP:
			case Common::EVENT_RBUTTONUP:
				break;
			case Common::EVENT_QUIT:
				break;
			default:
				break;
			}
		}

		if (shouldQuit())
			return;

		// TODO: Update all structures, animations, naks, heros etc.

		_interpreter->step();

		drawScreen();

		// Calculate the frame delay based off a desired frame time
		int delay = 1000/15 - int32(_system->getMillis() - currentTime);
		// Ensure non-negative
		delay = delay < 0 ? 0 : delay;
		_system->delayMillis(delay);
		
		_cameraX = _newCameraX;
		++_frameNr;

		if (_debugger->_locationNr != _locationNr)
			loadLocation(_debugger->_locationNr);
		if (_debugger->_cursorNr != _cursorNr)
			changeCursor(_debugger->_cursorNr);
	}
}

} // End of namespace Prince

/* vim: set tabstop=4 expandtab!: */
