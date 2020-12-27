<!---
 license: Licensed to the Apache Software Foundation (ASF) under one
         or more contributor license agreements.  See the NOTICE file
         distributed with this work for additional information
         regarding copyright ownership.  The ASF licenses this file
         to you under the Apache License, Version 2.0 (the
         "License"); you may not use this file except in compliance
         with the License.  You may obtain a copy of the License at

           http://www.apache.org/licenses/LICENSE-2.0

         Unless required by applicable law or agreed to in writing,
         software distributed under the License is distributed on an
         "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
         KIND, either express or implied.  See the License for the
         specific language governing permissions and limitations
         under the License.
-->

# org.crosswire.sword.cordova.SWORD

This plugin defines a global 'SWORD' object, which provides access to CrossWire's SWORD engine.
Although the object is in the global scope, it is not available until after the `deviceready` event.

### Supported Platforms

- Android
- iOS
- other platforms should work from source, but binaries are only included for those listed above

### Quick Example

	var moduleName = 'KJV';
	var verse = 'Jn.3.16';

	SWORD.mgr.getModuleByName(moduleName, function(module) {
		module.setKeyText(verse, function() {
			module.getRenderText(function(entryText) {
				console.log(verse + ': ' + entryText + '(' + moduleName + ')');
			});
		});
	});


## Installation

	cordova plugin add cordova-plugin-crosswire-sword


## Defines and statics
	SWORD.CATEGORY_BIBLES
	SWORD.CATEGORY_COMMENTARIES
	SWORD.CATEGORY_LEXDICTS
	SWORD.CATEGORY_GENBOOKS
	SWORD.CATEGORY_DAILYDEVOS
	SWORD.osisOT - array of OSIS OT Books
	SWORD.osisNT - array of OSIS NT Books


## Properties
	SWORD.available - if SWORD is available for use
	SWORD.version - SWORD C++ version
	SWORD.installMgr - access to SWORD's InstallMgr (an instance of class InstallMgr described below)
	SWORD.mgr - access to SWORD's module library manager SWMgr (an instance of class SWMgr described below)
	SWORD.httpUtils - access to general http requests methods provided by SWORD's C++ transport agent (see HTTPUtils described below)


## Class Properties and Methods

### InstallMgr
	InstallMgr.setUserDisclaimerConfirmed
	InstallMgr.syncConfig
	InstallMgr.getRemoteSources
	InstallMgr.refreshRemoteSource
	InstallMgr.getRemoteModInfoList
	InstallMgr.getRemoteModuleByName
	InstallMgr.remoteInstallModule
	InstallMgr.uninstallModule


### SWModule
	SWModule.SEARCHTYPE_REGEX
	SWModule.SEARCHTYPE_PHRASE
	SWModule.SEARCHTYPE_MULTIWORD
	SWModule.SEARCHTYPE_ENTRYATTR
	SWModule.SEARCHTYPE_LUCENE

	SWModule.SEARCHOPTION_ICASE

	SWModule.name
	SWModule.description
	SWModule.category
	SWModule.direction
	SWModule.language
	SWModule.font
	SWModule.shortCopyright
	SWModule.shortPromo
	SWModule.cipherKey
	SWModule.remoteSourceName

	SWModule.setKeyText
	SWModule.search
	SWModule.terminateSearch
	SWModule.getKeyText
	SWModule.getRenderText
	SWModule.getStripText
	SWModule.getRawEntry
	SWModule.shareVerse
	SWModule.getRenderChapter
	SWModule.getRenderHeader
	SWModule.getKeyChildren
	SWModule.getVerseKey
	SWModule.getConfigEntry
	SWModule.popError
	SWModule.getEntryAttribute
	SWModule.next
	SWModule.previous
	SWModule.begin
	SWModule.getBookNames
	SWModule.parseKeyList
	SWModule.setRawEntry

### SWMgr
	SWMgr.getModInfoList
	SWMgr.getModuleByName
	SWMgr.getExtraConfigSections
	SWMgr.getExtraConfigKeys
	SWMgr.getExtraConfigValue
	SWMgr.setExtraConfigValue
	SWMgr.addExtraConfig
	SWMgr.startBibleSync
	SWMgr.stopBibleSync
	SWMgr.sendBibleSyncMessage
	SWMgr.setJavascript
	SWMgr.getAvailableLocales
	SWMgr.setDefaultLocale
	SWMgr.translate
	SWMgr.setGlobalOption
	SWMgr.getPrefixPath

### HTTPUtils
	HTTPUtils.METHOD_GET
	HTTPUtils.METHOD_POST

	HTTPUtils.makeRequest

