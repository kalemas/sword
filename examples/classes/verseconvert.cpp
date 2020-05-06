/******************************************************************************
 *
 *  verseconvert.cpp -	This example shows how to convert a verse reference
 *  from one versification to another.  This is a very simplistic usage.
 *  For a complete example, see sword/examples/tasks/parallelbibles.cpp
 *
 * $Id: verseposition.cpp 2980 2013-09-14 21:51:47Z scribe $
 *
 * Copyright 2020 CrossWire Bible Society (http://www.crosswire.org)
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
#include <swmodule.h>
#include <versekey.h>


using namespace sword;
using namespace std;


int main(int argc, char **argv) {

	if (argc < 3) {
		cerr << "\nUsage: " << *argv << " <key> <moduleNameFrom> <moduleNameTo>\n" << endl;
		exit(-1);
	}

	const char *modNameFrom = argv[2];
	const char *modNameTo = argv[3];

	SWMgr library;
        SWModule *modFrom = library.getModule(modNameFrom);
        if (!modFrom) {
                cerr << "Can't find module: " << modNameFrom << endl;
                return -1;
        }
        SWModule *modTo = library.getModule(modNameTo);
        if (!modTo) {
                cerr << "Can't find module: " << modNameTo << endl;
                return -1;
        }

	modFrom->setKey(argv[1]);
	modTo->setKey(modFrom->getKey());

	cout	<< "\n"
		<< modFrom->getKeyText()
		<< " (" << modFrom->getName() << ") => "
		<< modTo->getKey()->getRangeText()
		<< " (" << modTo->getName() << ")\n" << endl;

        return 0;
}
