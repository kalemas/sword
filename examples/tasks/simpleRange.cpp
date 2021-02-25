/******************************************************************************
 *
 *  simpleRange.cpp -	this example shows how to display Bible text specified
 *  by a verse range
 *
 * $Id: $
 *
 * Copyright 2013-2014 CrossWire Bible Society (http://www.crosswire.org)
 *	CrossWire Bible Society
 *	P. O. Box 2528
 *	Tempe, AZ  85280-2528
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 */

#include <iostream>
#include <swmgr.h>
#include <markupfiltmgr.h>
#include <swmodule.h>
#include <versekey.h>

using namespace sword;
using namespace std;


int main(int argc, char **argv) {

	SWBuf moduleName = argc > 1 ? argv[1] : "KJV";
	SWBuf verseRange = argc > 2 ? argv[2] : "jn.2.19-3.2";

	SWMgr library(new MarkupFilterMgr(FMT_XHTML));
        SWModule *module = library.getModule(moduleName);

	if (!module) return cerr << "\nCouldn't find module: " << moduleName << "\n\n", -1;

	VerseKey *parser = (VerseKey *)module->getKey();
	ListKey range = parser->parseVerseList(verseRange, *parser, true);

	cout << "\n" << module->getDescription() << " -- " << range.getRangeText();
	cout << "\n-------------------\n";
	cout << "<style>\n" << module->getRenderHeader() << "\n</style>\n\n";
	for (range = TOP; !range.popError(); range++) {
		module->setKey(range);
		SWBuf key = module->getKey()->getText();
		SWBuf entry = module->renderText();
		cout << key << ": " << entry << "\n";
	}
	cout << "\n";
        return 0;
}
