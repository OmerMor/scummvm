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

#ifndef TITANIC_TREE_ITEM_H
#define TITANIC_TREE_ITEM_H

#include "titanic/core/message_target.h"

namespace Titanic {

class CGameManager;
class CDontSaveFileItem;
class CNamedItem;

class CTreeItem: public CMessageTarget {
private:
	CTreeItem *_parent;
	CTreeItem *_nextSibling;
	CTreeItem *_priorSibling;
	CTreeItem *_firstChild;
	int _field14;
public:
	CLASSDEF
	CTreeItem();

	/**
	 * Save the data for the class to file
	 */
	virtual void save(SimpleFile *file, int indent) const;

	/**
	 * Load the data for the class from file
	 */
	virtual void load(SimpleFile *file);

	/**
	 * Get the game manager for the project
	 */
	virtual CGameManager *getGameManager() const;

	/**
	 * Returns true if the item is a file item
	 */
	virtual bool isFileItem() const;

	/**
	 * Returns true if the item is a room item
	 */
	virtual bool isRoomItem() const;

	/**
	 * Returns true if the item is a node item
	 */
	virtual bool isNodeItem() const;

	/**
	 * Returns true if the item is a view item
	 */
	virtual bool isViewItem() const;

	/**
	 * Returns true if the item is a link item
	 */
	virtual bool isLinkItem() const;

	/**
	 * Returns true if the item is a named item
	 */
	virtual bool isNamedItem() const;

	/**
	 * Returns true if the item is a game object
	 */
	virtual bool isGameObject() const;

	/**
	 * Returns true if the item is a game object desc item
	 */
	virtual bool isGameObjectDescItem() const;

	/**
	 * Gets the name of the item, if any
	 */
	virtual const CString getName() const { return CString(); }

	/**
	 * Compares the name of the item to a passed name
	 */
	virtual int compareTo(const CString &name, int maxLen) const { return false; }

	/**
	 * Get the parent for the given item
	 */
	CTreeItem *getParent() const { return _parent; }

	/**
	 * Jumps up through the parents to find the sub-root item
	 */
	CTreeItem *getRoot() const;

	/**
	 * Get the next sibling
	 */
	CTreeItem *getNextSibling() const { return _nextSibling; }

	/**
	 * Get the prior sibling
	 */
	CTreeItem *getPriorSibling() const { return _priorSibling; }

	/**
	 * Get the last sibling of this sibling
	 */
	CTreeItem *getLastSibling();

	/**
	 * Get the first child of the item, if any
	 */
	CTreeItem *getFirstChild() const { return _firstChild; }

	/**
	 * Get the last child of the item, if any
	 */
	CTreeItem *getLastChild() const;

	/**
	 * Given all the recursive children of the tree item, gives the next
	 * item in sequence to the passed starting item
	 */
	CTreeItem *scan(CTreeItem *item) const;

	/**
	 * Find the first child item that is of a given type
	 */
	CTreeItem *findChildInstanceOf(ClassDef *classDef) const;

	/**
	 * Find the next sibling item that is of the given type
	 */
	CTreeItem *findNextInstanceOf(ClassDef *classDef, CTreeItem *startItem) const;

	/**
	 * Adds the item under another tree item
	 */
	void addUnder(CTreeItem *newParent);

	/**
	 * Sets the parent for the item
	 */
	void setParent(CTreeItem *newParent);

	/**
	 * Adds the item as a sibling of another item
	 */
	void addSibling(CTreeItem *item);

	/**
	 * Destroys both the item as well as any of it's children
	 */
	void destroyAll();

	/**
	 * Destroys all tree items around the given one
	 */
	int destroyOthers();

	/**
	 * Detach the tree item from any other associated tree items
	 */
	void detach();

	/**
	 * Finds a tree item by name
	 */
	CNamedItem *findByName(const CString &name, int maxLen = 0);
};

} // End of namespace Titanic

#endif /* TITANIC_TREE_ITEM_H */
