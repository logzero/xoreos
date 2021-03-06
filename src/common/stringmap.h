/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names can be
 * found in the AUTHORS file distributed with this source
 * distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
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
 *
 * The Infinity, Aurora, Odyssey, Eclipse and Lycium engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 */

/** @file common/stringmap.h
 *  A map to quickly match strings from a list.
 */

#ifndef COMMON_STRWORDMAP_H
#define COMMON_STRWORDMAP_H

#include <map>

#include <boost/unordered/unordered_map.hpp>

#include "common/ustring.h"

namespace Common {

typedef std::map<UString, UString> StringMap;
typedef std::map<UString, UString, UString::iless> StringIMap;

typedef boost::unordered_map<UString, UString, hashUStringCaseSensitive> StringHashMap;
typedef boost::unordered_map<UString, UString, hashUStringCaseInsensitive> StringHashIMap;

/** A map to quickly match strings from a list. */
class StringListMap {
public:
	/** Build a string map to match a list of strings against. */
	StringListMap(const char **strings, int count, bool onlyFirstWord = false);

	/** Match a string against the map.
	 *
	 *  @param  str The string to match against.
	 *  @param  match If != 0, the position after the match will be stored here.
	 *  @return The index of the matched string in the original list, or -1 if not found.
	 */
	int find(const char *str, const char **match) const;

	/** Match a string against the map.
	 *
	 *  @param  str The string to match against.
	 *  @param  match If != 0, the position after the match will be stored here.
	 *  @return The index of the matched string in the original list, or -1 if not found.
	 */
	int find(const UString &str, const char **match) const;

private:
	bool _onlyFirstWord;

	typedef boost::unordered_map<UString, int, hashUStringCaseInsensitive> StrMap;

	StrMap _map;

};

} // End of namespace Common

#endif // COMMON_STRWORDMAP_H
