/* eos - A reimplementation of BioWare's Aurora engine
 * Copyright (c) 2010-2011 Sven Hesse (DrMcCoy), Matthew Hoops (clone2727)
 *
 * The Infinity, Aurora, Odyssey and Eclipse engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 *
 * This file is part of eos and is distributed under the terms of
 * the GNU General Public Licence. See COPYING for more informations.
 */

/** @file common/readline.h
 *  A class providing (limited) readline-like capabilities.
 */

#ifndef COMMON_READLINE_H
#define COMMON_READLINE_H

#include <list>

#include "common/types.h"
#include "common/ustring.h"

#include "events/types.h"

namespace Common {

class ReadLine {
public:
	ReadLine(uint32 historySize);
	~ReadLine();

	void clearHistory();

	const Common::UString &getCurrentLine() const;
	uint32 getCursorPosition() const;
	bool getOverwrite() const;

	/** Process that given events.
	 *
	 *  Depends on unicode translation to be turned on.
	 *
	 *  @param event The event to process.
	 *  @param command When enter was pressed, the command
	 *                 to be executed will be stored here.
	 *  @return true if the event was handled.
	 */
	bool processEvent(Events::Event &event, Common::UString &command);

private:
	uint32 _historySizeMax;
	uint32 _historySizeCurrent;

	uint32 _cursorPosition;

	bool _overwrite;

	bool _notBrowsed;
	Common::UString _currentLine;
	Common::UString _currentLineBak;

	std::list<Common::UString> _history;
	std::list<Common::UString>::iterator _historyPosition;


	void addCurrentLineToHistory();

	void updateHistory();
	void browseUp();
	void browseDown();
};

} // End of namespace Common

#endif // COMMON_READLINE_H