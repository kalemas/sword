/******************************************************************************
 *
 * thmlstrongs -	SWFilter descendant to hide or show strongs number
 *			in a ThML module.
 */


#include <stdlib.h>
#include <thmlwordjs.h>
#include <swmodule.h>
#ifndef __GNUC__
#else
#include <unixstr.h>
#endif
#include <ctype.h>
#include <utilxml.h>
#include <versekey.h>

SWORD_NAMESPACE_START

const char oName[] = "Word Javascript";
const char oTip[] = "Toggles Word Javascript data";

const SWBuf choices[3] = {"Off", "On", ""};
const StringList oValues(&choices[0], &choices[2]);


ThMLWordJS::ThMLWordJS() : SWOptionFilter(oName, oTip, &oValues) {
	setOptionValue("Off");

     defaultGreekLex   = 0;
     defaultHebLex     = 0;
     defaultGreekParse = 0;
     defaultHebParse   = 0;
     mgr               = 0;
}


ThMLWordJS::~ThMLWordJS() {
}


char ThMLWordJS::processText(SWBuf &text, const SWKey *key, const SWModule *module) {
	if (option) {
		char token[2112]; // cheese.  Fix.
		int tokpos = 0;
		bool intoken = false;
		bool lastspace = false;
		int word = 1;
		char val[128];
		char *valto;
		char *ch;
		char wordstr[5];
		unsigned int textStart = 0, lastAppendLen = 0, textEnd = 0;
		char gh = 0;
		SWBuf tmp;
		bool newText = false;
		bool needWordOut = false;
		AttributeValue *wordAttrs = 0;
		

		const SWBuf orig = text;
		const char * from = orig.c_str();
		VerseKey *vkey = 0;
		if (key) {
			vkey = SWDYNAMIC_CAST(VerseKey, key);
		}

		for (text = ""; *from; from++) {
			if (*from == '<') {
				intoken = true;
				tokpos = 0;
				token[0] = 0;
				token[1] = 0;
				token[2] = 0;
				textEnd = text.length();
				continue;
			}
			if (*from == '>') {	// process tokens
				intoken = false;
				if (!strnicmp(token, "sync type=\"Strongs\" ", 20)) {	// Strongs
					valto = val;
					for (unsigned int i = 27; token[i] != '\"' && i < 150; i++)
						*valto++ = token[i];
					*valto = 0;
					if (atoi((!isdigit(*val))?val+1:val) < 5627) {
						// normal strongs number
						sprintf(wordstr, "%03d", word++);
						needWordOut = (word > 2);
						wordAttrs = &(module->getEntryAttributes()["Word"][wordstr]);
						(*wordAttrs)["Strongs"] = val;
	//printf("Adding: [\"Word\"][%s][\"Strongs\"] = %s\n", wordstr, val);
						tmp = "";
						tmp.append(text.c_str()+textStart, (int)(textEnd - textStart));
						(*wordAttrs)["Text"] = tmp;
						text.append("</span>");
						SWBuf ts;
						ts.appendFormatted("%d", textStart);
						(*wordAttrs)["TextStart"] = ts;
	//printf("Adding: [\"Word\"][%s][\"Text\"] = %s\n", wordstr, tmp.c_str());
						newText = true;
					}
					else {
						// verb morph
						(*wordAttrs)["Morph"] = val;
	//printf("Adding: [\"Word\"][%s][\"Morph\"] = %s\n", wordstr, val);
					}

				}
				if (!strncmp(token, "sync type=\"morph\"", 17)) {
					for (ch = token+17; *ch; ch++) {
						if (!strncmp(ch, "class=\"", 7)) {
							valto = val;
							for (unsigned int i = 7; ch[i] != '\"' && i < 127; i++)
								*valto++ = ch[i];
							*valto = 0;
							(*wordAttrs)["MorphClass"] = val;
	//printf("Adding: [\"Word\"][%s][\"MorphClass\"] = %s\n", wordstr, val);
						}
						if (!strncmp(ch, "value=\"", 7)) {
							valto = val;
							for (unsigned int i = 7; ch[i] != '\"' && i < 127; i++)
								*valto++ = ch[i];
							*valto = 0;
							(*wordAttrs)["Morph"] = val;
	//printf("Adding: [\"Word\"][%s][\"Morph\"] = %s\n", wordstr, val);
						}
					}
					newText = true;
				}
				// if not a strongs token, keep token in text
				text += '<';
				text += token;
				text += '>';
				if (needWordOut) {
					char wstr[10];
					sprintf(wstr, "%03d", word-2);
					AttributeValue *wAttrs = &(module->getEntryAttributes()["Word"][wstr]);
					needWordOut = false;
					SWBuf strong = (*wAttrs)["Strongs"];
					SWBuf morph = (*wAttrs)["Morph"];
					SWBuf morphClass = (*wAttrs)["MorphClass"];
					SWBuf wordText = (*wAttrs)["Text"];
					SWBuf textSt = (*wAttrs)["TextStart"];
					if (strong.size()) {
						char gh = 0;
						gh = isdigit(strong[0]) ? 0:strong[0];
						if (!gh) {
							if (vkey) {
								gh = vkey->Testament() ? 'H' : 'G';
							}
						}
						else strong << 1;

						SWModule *sLex = 0;
						SWModule *sMorph = 0;
						if (gh == 'G') {
							sLex = defaultGreekLex;
							sMorph = defaultGreekParse;
						}
						if (gh == 'H') {
							sLex = defaultHebLex;
							sMorph = defaultHebParse;
						}
						SWBuf lexName = "";
						if (sLex) {
							// we can pass the real lex name in, but we have some
							// aliases in the javascript to optimize bandwidth
							lexName = sLex->Name();
							if (lexName == "StrongsGreek")
								lexName = "G";
							if (lexName == "StrongsHebrew")
								lexName = "H";
						}
						SWBuf layer;
						if (vkey) {
							// optimize for bandwidth and use only the verse as the unique entry id
							layer.appendFormatted("%d", vkey->Verse());
						}
						else {
							layer = key->getText();
						}
						for (int i = 0; i < layer.size(); i++) {
							if ((!isdigit(layer[i])) && (!isalpha(layer[i]))) {
								layer[i] = '_';
							}
						}
						if (textSt.size()) {
							int textStr = atoi(textSt.c_str());
							textStr += lastAppendLen;
							SWBuf spanStart = "";



/*
							if (sMorph) {
								SWBuf popMorph = "<a onclick=\"";
								popMorph.appendFormatted("p(\'%s\',\'%s\','%s_%s','');\" >%s</a>", sMorph->Name(), morph.c_str(), layer.c_str(), wstr, morph.c_str());
								morph = popMorph;
							}
*/



							// 'p' = 'fillpop' to save bandwidth
							spanStart.appendFormatted("<span onclick=\"p(\'%s\',\'%s\','%s_%s','%s');\" >", lexName.c_str(), strong.c_str(), layer.c_str(), wstr, morph.c_str());
							text.insert(textStr, spanStart);
							lastAppendLen = spanStart.length();
						}
					}

				}
				if (newText) {
					textStart = text.length(); newText = false;
				}
				continue;
			}
			if (intoken) {
				if (tokpos < 2045)
					token[tokpos++] = *from;
					token[tokpos+2] = 0;
			}
			else	{
				text += *from;
				lastspace = (*from == ' ');
			}
		}

		char wstr[10];
		sprintf(wstr, "%03d", word-1);
		AttributeValue *wAttrs = &(module->getEntryAttributes()["Word"][wstr]);
		needWordOut = false;
		SWBuf strong = (*wAttrs)["Strongs"];
		SWBuf morph = (*wAttrs)["Morph"];
		SWBuf morphClass = (*wAttrs)["MorphClass"];
		SWBuf wordText = (*wAttrs)["Text"];
		SWBuf textSt = (*wAttrs)["TextStart"];
		if (strong.size()) {
			char gh = 0;
			gh = isdigit(strong[0]) ? 0:strong[0];
			if (!gh) {
				if (vkey) {
					gh = vkey->Testament() ? 'H' : 'G';
				}
			}
			else strong << 1;

			SWModule *sLex = 0;
			if (gh == 'G') {
				sLex = defaultGreekLex;
			}
			if (gh == 'H') {
				sLex = defaultHebLex;
			}
			SWBuf lexName = "";
			if (sLex) {
				// we can pass the real lex name in, but we have some
				// aliases in the javascript to optimize bandwidth
				lexName = sLex->Name();
				if (lexName == "StrongsGreek")
					lexName = "G";
				if (lexName == "StrongsHebrew")
					lexName = "H";
			}
			SWBuf layer;
			if (vkey) {
				// optimize for bandwidth and use only the verse as the unique entry id
				layer.appendFormatted("%d", vkey->Verse());
			}
			else {
				layer = key->getText();
			}
			for (int i = 0; i < layer.size(); i++) {
				if ((!isdigit(layer[i])) && (!isalpha(layer[i]))) {
					layer[i] = '_';
				}
			}
			if (textSt.size()) {
				int textStr = atoi(textSt.c_str());
				textStr += lastAppendLen;
				SWBuf spanStart = "";
				// 'p' = 'fillpop' to save bandwidth
				spanStart.appendFormatted("<span onclick=\"p(\'%s\', \'%s\', '%s_%s', '%s');\" >", lexName.c_str(), strong.c_str(), layer.c_str(), wstr, morph.c_str());
				text.insert(textStr, spanStart);
			}
		}
	}

	return 0;
}

SWORD_NAMESPACE_END
