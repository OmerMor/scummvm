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
 * $URL$
 * $Id$
 *
 */

#include "m4/m4.h"
#include "m4/mads_logic.h"
#include "m4/scene.h"

namespace M4 {

/*--------------------------------------------------------------------------*/

const char *MadsSceneLogic::formAnimName(char sepChar, int16 suffixNum) {
	return MADSResourceManager::getResourceName(sepChar, _sceneNumber, EXTTYPE_NONE, NULL, suffixNum);
}

void MadsSceneLogic::getSceneSpriteSet() {
	char prefix[100];

	// Room change sound
	_madsVm->_sound->playSound(5);

	// Set up sprite set prefix to use
	if ((_sceneNumber <= 103) || (_sceneNumber == 111)) {
		if (_madsVm->globals()->_globals[0] == SEX_FEMALE)
			strcpy(prefix, "ROX");
		else
			strcpy(prefix, "RXM");
	} else if (_sceneNumber <= 110) {
		strcpy(prefix, "RXSW");
		_madsVm->globals()->_globals[0] = SEX_UNKNOWN;
	} else if (_sceneNumber == 112)
		strcpy(prefix, "");

	_madsVm->globals()->playerSpriteChanged = true;
	_madsVm->scene()->loadPlayerSprites(prefix);

//	if ((_sceneNumber == 105) ((_sceneNumber == 109) && (word_84800 != 0)))
//		_madsVm->globals()->playerSpriteChanged = true;

	_vm->_palette->setEntry(16, 0x38, 0xFF, 0xFF);
	_vm->_palette->setEntry(17, 0x38, 0xb4, 0xb4);
}

void MadsSceneLogic::getAnimName() {
	const char *newName = MADSResourceManager::getAAName(
		((_sceneNumber <= 103) || (_sceneNumber > 111)) ? 0 : 1);
	strcpy(_madsVm->scene()->_aaName, newName);
}

/*--------------------------------------------------------------------------*/

uint16 MadsSceneLogic::loadSpriteSet(uint16 suffixNum, uint16 sepChar) {
	assert(sepChar < 256);
	const char *resName = formAnimName((char)sepChar, (int16)suffixNum);
	return _madsVm->scene()->loadSceneSpriteSet(resName);
}

uint16 MadsSceneLogic::startReversibleSpriteSequence(uint16 srcSpriteIdx, int v0, int numTicks, int triggerCountdown, int timeoutTicks, int extraTicks) {
	M4Sprite *spriteFrame = _madsVm->scene()->_spriteSlots.getSprite(srcSpriteIdx).getFrame(0);
	uint8 depth = _madsVm->_rails->getDepth(Common::Point(spriteFrame->x + (spriteFrame->width() / 2),
		spriteFrame->y + (spriteFrame->height() / 2)));

	return _madsVm->scene()->_sequenceList.add(srcSpriteIdx, v0, 1, triggerCountdown, timeoutTicks, extraTicks, numTicks, 0, 0, 
		-1, 100, depth - 1, 1, ANIMTYPE_REVERSIBLE, 0, 0);
}

uint16 MadsSceneLogic::startCycledSpriteSequence(uint16 srcSpriteIdx, int v0, int numTicks, int triggerCountdown, int timeoutTicks, int extraTicks) {
	M4Sprite *spriteFrame = _madsVm->scene()->_spriteSlots.getSprite(srcSpriteIdx).getFrame(0);
	uint8 depth = _madsVm->_rails->getDepth(Common::Point(spriteFrame->x + (spriteFrame->width() / 2),
		spriteFrame->y + (spriteFrame->height() / 2)));

	return _madsVm->scene()->_sequenceList.add(srcSpriteIdx, v0, 1, triggerCountdown, timeoutTicks, extraTicks, numTicks, 0, 0, 
		-1, 100, depth - 1, 1, ANIMTYPE_CYCLED, 0, 0);
}

uint16 MadsSceneLogic::startSpriteSequence3(uint16 srcSpriteIdx, int v0, int numTicks, int triggerCountdown, int timeoutTicks, int extraTicks) {
	M4Sprite *spriteFrame = _madsVm->scene()->_spriteSlots.getSprite(srcSpriteIdx).getFrame(0);
	uint8 depth = _madsVm->_rails->getDepth(Common::Point(spriteFrame->x + (spriteFrame->width() / 2),
		spriteFrame->y + (spriteFrame->height() / 2)));

	return _madsVm->scene()->_sequenceList.add(srcSpriteIdx, v0, 1, triggerCountdown, timeoutTicks, extraTicks, numTicks, 0, 0, 
		-1, 100, depth - 1, -1, ANIMTYPE_CYCLED, 0, 0);
}

void MadsSceneLogic::activateHotspot(int idx, bool active) {
	// TODO:
}

void MadsSceneLogic::lowRoomsEntrySound() {
	if (!_madsVm->globals()->_config.musicFlag) {
		_madsVm->_sound->playSound(2);
	} else {
		// Play different sounds for each of the rooms
		switch (_madsVm->globals()->sceneNumber) {
		case 101:
			_madsVm->_sound->playSound(11);
			break;
		case 102:
			_madsVm->_sound->playSound(12);
			break;
		case 103:
			_madsVm->_sound->playSound(3);
			_madsVm->_sound->playSound(25);
			break;
		case 104:
			_madsVm->_sound->playSound(10);
			break;
		case 105:
			if ((_madsVm->globals()->previousScene < 104) || (_madsVm->globals()->previousScene > 108))
				_madsVm->_sound->playSound(10);
			break;
		case 106:
			_madsVm->_sound->playSound(13);
			break;
		case 107:
			_madsVm->_sound->playSound(3);
			break;
		case 108:
			_madsVm->_sound->playSound(15);
			break;
		default:
			break;
		}
	}
}

/*--------------------------------------------------------------------------*/

/**
 * FIXME:
 * Currently I'm only working at providing manual implementation of the first Rex Nebular scene.
 * It will make more sense to convert the remaining game logic from the games into some
 * kind of bytecode scripts
 */

void MadsSceneLogic::selectScene(int sceneNum) {
	assert(sceneNum == 101);
	_sceneNumber = sceneNum;

	Common::set_to(&_spriteIndexes[0], &_spriteIndexes[50], 0);
}

void MadsSceneLogic::setupScene() {
	// FIXME: This is the hardcoded logic for Rex scene 101 only
	const char *animName = formAnimName('A', -1);
	warning("anim - %s", animName);

//	sub_1e754(animName, 3);

	if ((_sceneNumber >= 101) && (_sceneNumber <= 112))
		getSceneSpriteSet();

	getAnimName();
}

void MadsSceneLogic::enterScene() {
	for (int i = 1; i <= 7; ++i)
		_spriteIndexes[i - 1] = loadSpriteSet(i, 'x');
	_spriteIndexes[7] = loadSpriteSet(0xFFFF, 'm');
	_spriteIndexes[8] = loadSpriteSet(1, 'b');
	_spriteIndexes[9] = loadSpriteSet(2, 'b');
	_spriteIndexes[10] = loadSpriteSet(0, 'a');
	_spriteIndexes[11] = loadSpriteSet(1, 'a');
	_spriteIndexes[12] = loadSpriteSet(8, 'x');
	_spriteIndexes[13] = loadSpriteSet(0, 'x');

	_spriteIndexes[15] = startCycledSpriteSequence(_spriteIndexes[0], 0, 5, 0, 0, 25);

	_spriteIndexes[16] = startCycledSpriteSequence(_spriteIndexes[1], 0, 4, 0, 1, 0);
	_spriteIndexes[17] = startCycledSpriteSequence(_spriteIndexes[2], 0, 4, 0, 1, 0);

//	_madsVm->scene()->_sequenceList.addSubEntry(_spriteIndexes[17], SM_FRAME_INDEX, 7, 70);

	_spriteIndexes[18] = startReversibleSpriteSequence(_spriteIndexes[3], 0, 10, 0, 0, 60);
	_spriteIndexes[19] = startCycledSpriteSequence(_spriteIndexes[4], 0, 5, 0, 1, 0);
	_spriteIndexes[20] = startCycledSpriteSequence(_spriteIndexes[5], 0, 10, 0, 2, 0);
	_spriteIndexes[21] = startCycledSpriteSequence(_spriteIndexes[6], 0, 6, 0, 0, 0);

	_spriteIndexes[23] = startCycledSpriteSequence(_spriteIndexes[8], 0, 6, 0, 10, 4);
	_spriteIndexes[24] = startCycledSpriteSequence(_spriteIndexes[9], 0, 6, 0, 32, 47);

	activateHotspot(0x137, false);		// SHIELD MODULATOR
	// shield_panel_opened = 0;

	if (_madsVm->globals()->previousScene != -1)
		_madsVm->globals()->_globals[10] = 0;
	if (_madsVm->globals()->previousScene != -2) {
		_madsVm->scene()->getSceneResources().playerPos = Common::Point(100, 152);
	}
	
	if ((_madsVm->globals()->previousScene == 112) || 
		((_madsVm->globals()->previousScene != -2) && (_spriteIndexes[29] != 0))) {
		// Returning from probe cutscene?
		_spriteIndexes[29] = -1;
		_madsVm->scene()->getSceneResources().playerPos = Common::Point(161, 123);
		_madsVm->scene()->getSceneResources().playerDir = 9;

		// TODO: Extra flags setting
		_spriteIndexes[25] = startCycledSpriteSequence(_spriteIndexes[10], 0, 3, 0, 0, 0);
		_madsVm->scene()->_sequenceList.setAnimRange(_spriteIndexes[25], 17, 17);
		activateHotspot(0x47, false);	// CHAIR
		/*timer_unk1 = */_madsVm->scene()->_dynamicHotspots.add(0x47, 0x13F /*SIT_IN*/, -1,
			Common::Rect(159, 84, 159+33, 84+36));
		
		//if (_madsVm->globals()->previousScene == 112)
		//	room101Check();
	} else {
		_spriteIndexes[26] = startCycledSpriteSequence(_spriteIndexes[11], 0, 6, 0, 0, 0);
	}

	_madsVm->globals()->loadQuoteSet(0x31, 0x32, 0x37, 0x38, 0x39, -1);

	if (_madsVm->globals()->_globals[10]) {
		// TODO: Load scene animation

		_madsVm->scene()->getSceneResources().playerPos = Common::Point(68, 140);
		_madsVm->scene()->getSceneResources().playerDir = 4;
		// TODO: Flags setting
	}

	lowRoomsEntrySound();
}

void MadsSceneLogic::doAction() {

}

void MadsSceneLogic::sceneStep() {
	// FIXME: Temporary code to display a message on-screen
	static bool tempBool = false;
	if (!tempBool) {
		tempBool = true;

		_madsVm->scene()->_kernelMessages.add(Common::Point(63, 100), 0x1110, 0, 0, 240, 
			_madsVm->globals()->getQuote(49));
	}
}

}
