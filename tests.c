#include "tests.h"

#include "parser.h"
#include "symbol.h"
#include "tree.h"

#include <assert.h>
#include <stdio.h>

bool testCompileTree(void) {
	bool passed = true;

	SymbolTable symtab = { 0 };
	if (createSymbolTable(&symtab) == false) {
		passed = false; // kind of unfair for a failed allocation
		goto end;
	}


end:
	freeSymbolTable(&symtab);
	printf("compile tree tests...");
	if (passed) {
		printf("PASSED\n");
	} else {
		printf("FAILED\n");
	}
}
