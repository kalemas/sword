#include <stdio.h>
#include <stdlib.h>

#include <swordminflat.h>

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "\nusage: %s <modname> <\"keyText\">\n"
							 "\tExample: %s KJV \"James 1:19-30,34\"\n\n", argv[0], argv[0]);
		exit(-1);
	}


	SWHANDLE mgr = org_crosswire_sword_SWMgr_new();

	SWHANDLE module = org_crosswire_sword_SWMgr_getModuleByName(mgr, argv[1]);

	if (!module) {
		fprintf(stderr, "Could not find module [%s].  Available modules:\n", argv[1]);
		const struct org_crosswire_sword_ModInfo *modInfos = org_crosswire_sword_SWMgr_getModInfoList(mgr);
		while (modInfos && modInfos->name) {
			fprintf(stderr, "[%s]\t - %s\n", modInfos->name, modInfos->description);
			++modInfos;
		}
		org_crosswire_sword_SWMgr_delete(mgr);
		exit(-1);
	}

	const char **results = org_crosswire_sword_SWModule_parseKeyList(module, argv[2]);

	printf("==========================\n");
	printf("Parsing: %s\n", argv[2]);
	printf("==========================\n");
	while (results && *results) {
		printf("%s\n", *results);
		++results;
	}
	printf("==========================\n");

	org_crosswire_sword_SWMgr_delete(mgr);

	return 0;
}
