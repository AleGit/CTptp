//  Created by Alexander Maringele on 14.03.16.
//  Copyright © 2016 Alexander Maringele. All rights reserved.

#import "PrlcParser.h"
#import <sys/sysctl.h>

prlc_store* prlcParsingStore = NULL;
prlc_tree_node* prlcParsingRoot = NULL;

// total size of file in bytes
int file_size(FILE *file) {
	int size = 0;

	if (file != NULL) {

	fseek(file, 0L, SEEK_END);
	size = ftell(file);
	rewind(file);
	}
	
	return size;
}

int prlc_parse_path (const char* path) {
	if (path == NULL) {
		fprintf(stderr,"prlc_parse_path(NULL)\n");
		return -1;
	}
	
	FILE *file = fopen(path,"r");

	int size = file_size(file);

	if (file == NULL) {
		// file not found
		fprintf(stderr,"prlc_parse_path(%s) file could not be oppened.\n", path);
		return -1; 
	}

	if (size == 0) {
		// file is empty
		fprintf(stderr,"prlc_parse_path(%s) file is empty.\n", path);
		return -1; 
	}
	
	prlc_in = file;
	prlc_restart(file);
	prlc_lineno = 1;

	prlcParsingStore = prlcCreateStore(size);
	prlcParsingRoot = prlcStoreNodeFile (prlcParsingStore,path,NULL);

	int code = prlc_parse ();

	fclose(file);

	return -1;
}




