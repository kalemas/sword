/******************************************************************************
 *
 * $Id: thmlrtf.h,v 1.8 2003/07/26 23:10:55 chrislit Exp $
 *
 * Copyright 1998 CrossWire Bible Society (http://www.crosswire.org)
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

#ifndef THMLRTF_H
#define THMLRTF_H

#include <swbasicfilter.h>

SWORD_NAMESPACE_START

/** this filter converts ThML text to RTF text
 */
class SWDLLEXPORT ThMLRTF : public SWBasicFilter {
protected:
	virtual bool handleToken(SWBuf &buf, const char *token, DualStringMap &userData);
	virtual char processText(SWBuf &text, const SWKey *key = 0, const SWModule *module = 0);
public:
	ThMLRTF();
};

SWORD_NAMESPACE_END
#endif
