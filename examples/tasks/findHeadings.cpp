/******************************************************************************
 *
 *  findHeadings.cpp -	this example shows how to locate and retrieve headings
 *  			from a Bible
 *
 * $Id$
 *
 * Copyright 2021 CrossWire Bible Society (http://www.crosswire.org)
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
#include <listkey.h>

using namespace sword;
using namespace std;


int main(int argc, char **argv) {

	SWBuf moduleName = argc > 1 ? argv[1] : "NASB";
	SWBuf verseRange = argc > 2 ? argv[2] : "Matt-John";

	SWMgr library(new MarkupFilterMgr(FMT_XHTML));
	library.setGlobalOption("Headings", "On");

        SWModule *module = library.getModule(moduleName);
	if (!module) return cerr << "\nCouldn't find module: " << moduleName << "\n\n", -1;

	SWKey *key = module->getKey();
	VerseKey *verseKey = SWDYNAMIC_CAST(VerseKey, key);
	ListKey scope = verseKey->parseVerseList(verseRange, *verseKey, true);

	ListKey results = module->search("/Heading", SWModule::SEARCHTYPE_ENTRYATTR, 0, &scope);

	for (results = TOP; !results.popError(); results++) {
		module->setKey(results);
		module->renderText();

		// get both Preverse and Interverse Headings and just merge them into the same map
		AttributeValue headings = module->getEntryAttributes()["Heading"]["Preverse"];
		AttributeValue interverseHeadings = module->getEntryAttributes()["Heading"]["Interverse"];
		headings.insert(interverseHeadings.begin(), interverseHeadings.end());

		for (AttributeValue::const_iterator it = headings.begin(); it != headings.end(); ++it) {
			cout << it->second.c_str() << " (" << module->getKeyText() << ")\n";
		}
	}
	cout << "\n";
        return 0;
}
