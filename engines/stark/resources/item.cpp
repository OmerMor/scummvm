/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
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

#include "engines/stark/resources/item.h"

#include "engines/stark/formats/xrc.h"
#include "engines/stark/gfx/renderentry.h"
#include "engines/stark/movement/movement.h"

#include "engines/stark/resources/anim.h"
#include "engines/stark/resources/animhierarchy.h"
#include "engines/stark/resources/bonesmesh.h"
#include "engines/stark/resources/bookmark.h"
#include "engines/stark/resources/floor.h"
#include "engines/stark/resources/pattable.h"
#include "engines/stark/resources/textureset.h"

#include "engines/stark/services/global.h"
#include "engines/stark/services/services.h"
#include "engines/stark/services/stateprovider.h"
#include "engines/stark/services/userinterface.h"

namespace Stark {
namespace Resources {

Object *Item::construct(Object *parent, byte subType, uint16 index, const Common::String &name) {
	switch (subType) {
	case kItemGlobalTemplate:
		return new GlobalItemTemplate(parent, subType, index, name);
	case kItemInventory:
		return new InventoryItem(parent, subType, index, name);
	case kItemLevelTemplate:
		return new LevelItemTemplate(parent, subType, index, name);
	case kItemStaticProp:
	case kItemAnimatedProp:
		return new FloorPositionedImageItem(parent, subType, index, name);
	case kItemBackgroundElement:
	case kItemBackground:
		return new ImageItem(parent, subType, index, name);
	case kItemModel:
		return new ModelItem(parent, subType, index, name);
	default:
		error("Unknown item subtype %d", subType);
	}
}

Item::Item(Object *parent, byte subType, uint16 index, const Common::String &name) :
				Object(parent, subType, index, name),
				_enabled(true),
				_characterIndex(0),
				_movement(nullptr) {
	_type = TYPE;
}

Item::~Item() {
	delete _movement;
}

void Item::readData(Formats::XRCReadStream *stream) {
	_enabled = stream->readBool();
	_characterIndex = stream->readSint32LE();
}

void Item::onGameLoop() {
	Object::onGameLoop();

	if (_enabled && _movement) {
		_movement->onGameLoop();

		if (_movement->hasEnded()) {
			setMovement(nullptr);
		}
	}
}

bool Item::isEnabled() const {
	return _enabled;
}

void Item::setEnabled(bool enabled) {
	_enabled = enabled;
}

int32 Item::getCharacterIndex() const {
	return _characterIndex;
}

Gfx::RenderEntry *Item::getRenderEntry(const Common::Point &positionOffset) {
	return nullptr;
}

Item *Item::getSceneInstance() {
	return this;
}

Common::String Item::getHotspotTitle(uint32 hotspotIndex) const {
	PATTable *table = findChildWithOrder<PATTable>(hotspotIndex);
	if (table) {
		return table->getName();
	} else {
		return getName();
	}
}

void Item::setMovement(Movement *movement) {
	if (_movement && !_movement->hasEnded()) {
		_movement->stop();
	}

	delete _movement;
	_movement = movement;
}

void Item::printData() {
	debug("enabled: %d", _enabled);
	debug("character: %d", _characterIndex);
}

void Item::saveLoad(ResourceSerializer *serializer) {
	serializer->syncAsSint32LE(_enabled);
}

ItemVisual::~ItemVisual() {
	delete _renderEntry;
}

ItemVisual::ItemVisual(Object *parent, byte subType, uint16 index, const Common::String &name) :
				Item(parent, subType, index, name),
				_renderEntry(nullptr),
				_animHierarchy(nullptr),
				_currentAnimKind(-1),
				_clickable(true) {
	_renderEntry = new Gfx::RenderEntry(this, getName());
}

void ItemVisual::readData(Formats::XRCReadStream *stream) {
	Item::readData(stream);

	_clickable = stream->readBool();
}

void ItemVisual::onAllLoaded() {
	Item::onAllLoaded();

	_animHierarchy = findChild<AnimHierarchy>(false);

	_renderEntry->setClickable(_clickable);

	if (_subType != kItemModel) {
		setAnimKind(Anim::kActionUsagePassive);
	}

	if (!_enabled) {
		setEnabled(false);
	}
}

void ItemVisual::setEnabled(bool enabled) {
	Item::setEnabled(enabled);

	if (enabled) {
		_animHierarchy->selectItemAnim(this);
	} else {
		_animHierarchy->unselectItemAnim(this);
	}
}

void ItemVisual::setAnimKind(int32 usage) {
	bool animNeedsUpdate = usage != _currentAnimKind;

	_currentAnimKind = usage;
	if (animNeedsUpdate && _animHierarchy) {
		_animHierarchy->setItemAnim(this, usage);
	}
}

void ItemVisual::printData() {
	Item::printData();

	debug("clickable: %d", _clickable);
}

Anim *ItemVisual::getAnim() const {
	return _animHierarchy->getCurrentAnim();
}

Visual *ItemVisual::getVisual() {
	Anim *anim = getAnim();

	if (!anim) {
		return nullptr;
	}

	return anim->getVisual();
}

int ItemVisual::getHotspotIndexForPoint(const Common::Point &point) {
	// TODO: This breaks rather weirdly on subtype 6 and 10
	Anim *anim = getAnim();
	if (anim) {
		return anim->getPointHotspotIndex(point);
	}
	return -1;
}

bool ItemVisual::canPerformAction(uint32 action, uint32 hotspotIndex) {
	PATTable *table = findChildWithOrder<PATTable>(hotspotIndex);
	return table && table->canPerformAction(action);
}

bool ItemVisual::doAction(uint32 action, uint32 hotspotIndex) {
	PATTable *table = findChildWithOrder<PATTable>(hotspotIndex);
	if (table && table->canPerformAction(action)) {
		return table->runScriptForAction(action);
	}

	return false;
}

ItemTemplate::~ItemTemplate() {
}

ItemTemplate::ItemTemplate(Object *parent, byte subType, uint16 index, const Common::String &name) :
		Item(parent, subType, index, name),
		_meshIndex(-1),
		_textureNormalIndex(-1),
		_textureFaceIndex(-1),
		_animHierarchyIndex(-1),
		_referencedItem(nullptr),
		_instanciatedItem(nullptr) {
}

void ItemTemplate::onAllLoaded() {
	Item::onAllLoaded();

	BonesMesh *bonesMesh = findChild<BonesMesh>(false);
	if (bonesMesh) {
		_meshIndex = bonesMesh->getIndex();
	}

	TextureSet *textureNormal = findChildWithSubtype<TextureSet>(TextureSet::kTextureNormal, false);
	if (textureNormal) {
		_textureNormalIndex = textureNormal->getIndex();
	}

	TextureSet *textureFace = findChildWithSubtype<TextureSet>(TextureSet::kTextureFace, false);
	if (textureFace) {
		_textureFaceIndex = textureFace->getIndex();
	}
}

void ItemTemplate::setInstanciatedItem(Item *instance) {
	_instanciatedItem = instance;
}

Item *ItemTemplate::getSceneInstance() {
	if (_instanciatedItem) {
		return _instanciatedItem->getSceneInstance();
	}

	return nullptr;
}

Common::String ItemTemplate::getHotspotTitle(uint32 hotspotIndex) const {
	if (_referencedItem) {
		return _referencedItem->getHotspotTitle(hotspotIndex);
	}

	return Item::getHotspotTitle(hotspotIndex);
}

void ItemTemplate::setBonesMesh(int32 index) {
	_meshIndex = index;
}

void ItemTemplate::setTexture(int32 index, uint32 textureType) {
	if (textureType == TextureSet::kTextureNormal) {
		_textureNormalIndex = index;
	} else if (textureType == TextureSet::kTextureFace) {
		_textureFaceIndex = index;
	} else {
		error("Unknown texture type %d", textureType);
	}

	// Reset the animation to apply the changes
	ModelItem *sceneInstance = Resources::Object::cast<Resources::ModelItem>(getSceneInstance());
	sceneInstance->updateAnim();
}

GlobalItemTemplate::~GlobalItemTemplate() {
}

GlobalItemTemplate::GlobalItemTemplate(Object *parent, byte subType, uint16 index, const Common::String &name) :
		ItemTemplate(parent, subType, index, name) {
	_animHierarchyIndex = 0;
}

BonesMesh *GlobalItemTemplate::findBonesMesh() {
	if (_meshIndex == -1) {
		return nullptr;
	} else {
		return findChildWithIndex<BonesMesh>(_meshIndex);
	}
}

TextureSet *GlobalItemTemplate::findTextureSet(uint32 textureType) {
	if (textureType == TextureSet::kTextureNormal) {
		if (_textureNormalIndex == -1) {
			return nullptr;
		} else {
			return findChildWithIndex<TextureSet>(_textureNormalIndex);
		}
	} else if (textureType == TextureSet::kTextureFace) {
		if (_textureFaceIndex == -1) {
			return nullptr;
		} else {
			return findChildWithIndex<TextureSet>(_textureFaceIndex);
		}
	} else {
		error("Unknown texture type %d", textureType);
	}
}

AnimHierarchy *GlobalItemTemplate::findStockAnimHierarchy() {
	if (_animHierarchyIndex == -1) {
		return nullptr;
	} else {
		return findChildWithIndex<AnimHierarchy>(_animHierarchyIndex);
	}
}

InventoryItem::~InventoryItem() {
}

InventoryItem::InventoryItem(Object *parent, byte subType, uint16 index, const Common::String &name) :
		ItemVisual(parent, subType, index, name) {
}

Gfx::RenderEntry *InventoryItem::getRenderEntry(const Common::Point &positionOffset) {
	if (_enabled) {
		setAnimKind(Anim::kUIUsageInventory);

		Visual *visual = getVisual();

		_renderEntry->setVisual(visual);
		_renderEntry->setPosition(Common::Point());
	} else {
		_renderEntry->setVisual(nullptr);
	}

	return _renderEntry;
}

void InventoryItem::setEnabled(bool enabled) {
	Item::setEnabled(enabled);

	// Deselect the item in the inventory when removing it
	int16 selectedInventoryItem = StarkUserInterface->getSelectedInventoryItem();
	if (!enabled && selectedInventoryItem == getIndex()) {
		StarkUserInterface->selectInventoryItem(-1);
	}
}

Visual *InventoryItem::getActionVisual(bool active) const {
	if (active) {
		return _animHierarchy->getVisualForUsage(Anim::kActionUsageActive);
	} else {
		return _animHierarchy->getVisualForUsage(Anim::kActionUsagePassive);
	}
}

Visual *InventoryItem::getCursorVisual() const {
	Visual *visual = _animHierarchy->getVisualForUsage(Anim::kUIUsageUseCursorPassive);

	if (!visual) {
		visual = _animHierarchy->getVisualForUsage(Anim::kUIUsageUseCursorActive);
	}

	if (!visual) {
		visual = _animHierarchy->getVisualForUsage(Anim::kUIUsageInventory);
	}

	return visual;
}


LevelItemTemplate::~LevelItemTemplate() {
}

LevelItemTemplate::LevelItemTemplate(Object *parent, byte subType, uint16 index, const Common::String &name) :
		ItemTemplate(parent, subType, index, name) {
}

void LevelItemTemplate::readData(Formats::XRCReadStream *stream) {
	ItemTemplate::readData(stream);

	_reference = stream->readResourceReference();
}

void LevelItemTemplate::onAllLoaded() {
	ItemTemplate::onAllLoaded();

	_referencedItem = _reference.resolve<ItemTemplate>();
	if (_referencedItem) {
		_referencedItem->setInstanciatedItem(this);
	}
}

BonesMesh *LevelItemTemplate::findBonesMesh() {
	if (_meshIndex == -1) {
		return _referencedItem->findBonesMesh();
	} else {
		return findChildWithIndex<BonesMesh>(_meshIndex);
	}
}

TextureSet *LevelItemTemplate::findTextureSet(uint32 textureType) {
	if (textureType == TextureSet::kTextureNormal) {
		if (_textureNormalIndex == -1) {
			return _referencedItem->findTextureSet(textureType);
		} else {
			return findChildWithIndex<TextureSet>(_textureNormalIndex);
		}
	} else if (textureType == TextureSet::kTextureFace) {
		if (_textureFaceIndex == -1) {
			return _referencedItem->findTextureSet(textureType);
		} else {
			return findChildWithIndex<TextureSet>(_textureFaceIndex);
		}
	} else {
		error("Unknown texture type %d", textureType);
	}
}

AnimHierarchy *LevelItemTemplate::findStockAnimHierarchy() {
	if (_animHierarchyIndex == -1 && !_referencedItem) {
		_animHierarchyIndex = 0; // Prefer referenced anim to local
	}

	if (_animHierarchyIndex == -1) {
		return _referencedItem->findStockAnimHierarchy();
	} else {
		return findChildWithIndex<AnimHierarchy>(_animHierarchyIndex);
	}
}

ItemTemplate *LevelItemTemplate::getItemTemplate() const {
	return _referencedItem;
}

void LevelItemTemplate::printData() {
	ItemTemplate::printData();

	debug("reference: %s", _reference.describe().c_str());
}

FloorPositionedItem::~FloorPositionedItem() {
}

FloorPositionedItem::FloorPositionedItem(Object *parent, byte subType, uint16 index, const Common::String &name) :
		ItemVisual(parent, subType, index, name),
		_direction3D(0.0),
		_floorFaceIndex(-1) {
}

Math::Vector3d FloorPositionedItem::getPosition3D() const {
	return _position3D;
}

void FloorPositionedItem::setPosition3D(const Math::Vector3d &position) {
	_position3D = position;
}

int32 FloorPositionedItem::getFloorFaceIndex() const {
	return _floorFaceIndex;
}

void FloorPositionedItem::setFloorFaceIndex(int32 faceIndex) {
	_floorFaceIndex = faceIndex;
}

void FloorPositionedItem::placeOnBookmark(Bookmark *target) {
	Floor *floor = StarkGlobal->getCurrent()->getFloor();

	_position3D = target->getPosition();

	// Find the floor face index the item is on
	setFloorFaceIndex(floor->findFaceContainingPoint(_position3D));

	// Set the z coordinate using the floor height at that position
	if (_floorFaceIndex >= 0) {
		floor->computePointHeightInFace(_position3D, _floorFaceIndex);
	} else {
		warning("Item '%s' has been place out of the floor field", getName().c_str());
	}
}

void FloorPositionedItem::setDirection(uint direction) {
	_direction3D = direction;
}

float FloorPositionedItem::getSortKey() const {
	Floor *floor = StarkGlobal->getCurrent()->getFloor();

	if (_floorFaceIndex == -1) {
//		warning("Undefined floor face index for item '%s'", getName().c_str());
		return floor->getDistanceFromCamera(0);
	}

	return floor->getDistanceFromCamera(_floorFaceIndex);
}

FloorPositionedImageItem::~FloorPositionedImageItem() {
}

FloorPositionedImageItem::FloorPositionedImageItem(Object *parent, byte subType, uint16 index, const Common::String &name) :
		FloorPositionedItem(parent, subType, index, name) {
}

void FloorPositionedImageItem::readData(Formats::XRCReadStream *stream) {
	FloorPositionedItem::readData(stream);

	setFloorFaceIndex(stream->readSint32LE());
	_position = stream->readPoint();
}

Gfx::RenderEntry *FloorPositionedImageItem::getRenderEntry(const Common::Point &positionOffset) {
	if (_enabled) {
		Visual *visual = getVisual();
		_renderEntry->setVisual(visual);

		if (getAnim() && getAnim()->getSubType() == Anim::kAnimVideo) {
			// AnimVideos override the _position, but still need to move according to scroll-offsets
			_renderEntry->setPosition(positionOffset);
		} else {
			_renderEntry->setPosition(_position - positionOffset);
		}
		_renderEntry->setSortKey(getSortKey());
	} else {
		_renderEntry->setVisual(nullptr);
	}

	return _renderEntry;
}

void FloorPositionedImageItem::printData() {
	FloorPositionedItem::printData();

	debug("floorFaceIndex: %d", _floorFaceIndex);
	debug("position: x %d, y %d", _position.x, _position.y);
}

ImageItem::~ImageItem() {
}

ImageItem::ImageItem(Object *parent, byte subType, uint16 index, const Common::String &name) :
		ItemVisual(parent, subType, index, name) {
}

void ImageItem::readData(Formats::XRCReadStream *stream) {
	ItemVisual::readData(stream);

	_position = stream->readPoint();
	_reference = stream->readResourceReference();
}

Gfx::RenderEntry *ImageItem::getRenderEntry(const Common::Point &positionOffset) {
	if (_enabled) {
		Visual *visual = getVisual();
		_renderEntry->setVisual(visual);

		if (getAnim() && getAnim()->getSubType() == Anim::kAnimVideo) {
			// AnimVideos override the _position, but still need to move according to scroll-offsets
			_renderEntry->setPosition(positionOffset);
		} else {
			_renderEntry->setPosition(_position - positionOffset);
		}
	} else {
		_renderEntry->setVisual(nullptr);
	}

	return _renderEntry;
}

void ImageItem::printData() {
	ItemVisual::printData();

	debug("reference: %s", _reference.describe().c_str());
	debug("position: x %d, y %d", _position.x, _position.y);
}

ModelItem::~ModelItem() {
}

ModelItem::ModelItem(Object *parent, byte subType, uint16 index, const Common::String &name) :
		FloorPositionedItem(parent, subType, index, name),
		_meshIndex(-1),
		_textureNormalIndex(-1),
		_textureFaceIndex(-1),
		_referencedItem(nullptr) {
}

void ModelItem::readData(Formats::XRCReadStream *stream) {
	FloorPositionedItem::readData(stream);

	_reference = stream->readResourceReference();
}

void ModelItem::onAllLoaded() {
	FloorPositionedItem::onAllLoaded();

	BonesMesh *bonesMesh = findChild<BonesMesh>();
	if (bonesMesh) {
		_meshIndex = bonesMesh->getIndex();
	}

	TextureSet *textureNormal = findChildWithSubtype<TextureSet>(TextureSet::kTextureNormal);
	if (textureNormal) {
		_textureNormalIndex = textureNormal->getIndex();
	}

	TextureSet *textureFace = findChildWithSubtype<TextureSet>(TextureSet::kTextureFace);
	if (textureFace) {
		_textureFaceIndex = textureFace->getIndex();
	}

	_referencedItem = _reference.resolve<ItemTemplate>();
	if (_referencedItem) {
		_referencedItem->setInstanciatedItem(this);
	}
}

void ModelItem::onEnterLocation() {
	FloorPositionedItem::onEnterLocation();

	if (_referencedItem) {
		_animHierarchy = _referencedItem->findStockAnimHierarchy();
	}

	setAnimKind(Anim::kActorUsageIdle);
}

void ModelItem::setBonesMesh(int32 index) {
	_meshIndex = index;

	if (_meshIndex != -1) {
		updateAnim();
	}
}

BonesMesh *ModelItem::findBonesMesh() {
	// Prefer retrieving the mesh from the anim hierarchy
	BonesMesh *bonesMesh = _animHierarchy->findBonesMesh();

	// Otherwise, use a children mesh, or a referenced mesh
	if (!bonesMesh) {
		if (_meshIndex == -1) {
			bonesMesh = _referencedItem->findBonesMesh();
		} else {
			bonesMesh = findChildWithIndex<BonesMesh>(_meshIndex);
		}
	}

	return bonesMesh;
}

void ModelItem::setTexture(int32 index, uint32 textureType) {
	if (textureType == TextureSet::kTextureNormal) {
		_textureNormalIndex = index;
	} else if (textureType == TextureSet::kTextureFace) {
		_textureFaceIndex = index;
	} else {
		error("Unknown texture type %d", textureType);
	}
}

TextureSet *ModelItem::findTextureSet(uint32 textureType) {
	// Prefer retrieving the mesh from the anim hierarchy
	TextureSet *textureSet = _animHierarchy->findTextureSet(textureType);

	// Otherwise, use a children mesh, or a referenced mesh
	if (!textureSet) {
		if (textureType == TextureSet::kTextureNormal) {
			if (_textureNormalIndex == -1) {
				textureSet = _referencedItem->findTextureSet(textureType);
			} else {
				textureSet = findChildWithIndex<TextureSet>(_textureNormalIndex);
			}
		} else if (textureType == TextureSet::kTextureFace) {
			if (_textureFaceIndex == -1) {
				textureSet = _referencedItem->findTextureSet(textureType);
			} else {
				textureSet = findChildWithIndex<TextureSet>(_textureFaceIndex);
			}
		} else {
			error("Unknown texture type %d", textureType);
		}
	}

	return textureSet;
}

void ModelItem::updateAnim() {
	Anim *anim = getAnim();
	if (anim && anim->getSubType() == Anim::kAnimSkeleton) {
		anim->removeFromItem(this);
		anim->applyToItem(this);
	}
}

Gfx::RenderEntry *ModelItem::getRenderEntry(const Common::Point &positionOffset) {
	if (_enabled) {
		Visual *visual = getVisual();

		if (!visual) {
			_animHierarchy->selectItemAnim(this);
			visual = getVisual();
		}

		_renderEntry->setVisual(visual);
		_renderEntry->setPosition3D(_position3D, _direction3D);
		_renderEntry->setSortKey(getSortKey());
	} else {
		_renderEntry->setVisual(nullptr);
	}

	return _renderEntry;
}

Common::String ModelItem::getHotspotTitle(uint32 hotspotIndex) const {
	if (_referencedItem) {
		return _referencedItem->getHotspotTitle(hotspotIndex);
	}

	return Item::getHotspotTitle(hotspotIndex);
}

ItemTemplate *ModelItem::getItemTemplate() const {
	return _referencedItem;
}

void ModelItem::printData() {
	FloorPositionedItem::printData();

	debug("reference: %s", _reference.describe().c_str());
}

} // End of namespace Resources
} // End of namespace Stark
