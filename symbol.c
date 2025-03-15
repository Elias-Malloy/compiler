#include "symbol.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TOMBSTONE UINT32_MAX

bool createSymbolTable(SymbolTable *symtab) {
	if (symtab == NULL) return false;
	if (symtab->symbolCapacity == 0) {
		symtab->symbolCapacity = 512;
	}
	symtab->symbols = malloc(symtab->symbolCapacity * sizeof(Symbol));
	if (symtab->symbols == NULL) {
		printf("Symbol allocation failed\n");
		return false;
	}
	if (symtab->tableSize == 0) {
		symtab->tableSize = 1024;
	}
	symtab->lookup = calloc(symtab->tableSize, sizeof(uint32));
	if (symtab->lookup == NULL) {
		printf("lookup allocation failed\n");
		return false;
	}

	if (symtab->stringTableSize == 0) {
		symtab->stringTableSize = 1024;
	}
	symtab->stringTable = malloc(symtab->stringTableSize);
	if (symtab->stringTable == NULL) {
		printf("stringTable allocation failed\n");
		return false;
	}
	
	symtab->symbolCount = 1; // sentinal 0
	symtab->stringTableTop = 0;
	return true;
}

void freeSymbolTable(SymbolTable *symtab) {
	if (symtab == NULL) return;
	if (symtab->symbols) free(symtab->symbols);
	if (symtab->lookup) free(symtab->lookup);
	if (symtab->stringTable) free(symtab->stringTable);
}

uint32 lookupSymbolIndex(SymbolTable *symtab, uint8 *name) {
	uint32 ind = hashsdbm(name) % symtab->tableSize;
	uint32 end = symtab->tableSize;
	for (; ind < end; ind++) { // linear probing
		if (symtab->lookup[ind] == TOMBSTONE) continue; // skip past tomb stones
		uint8 *existingName = getSymbolName(symtab, ind);
		if (strcmp(existingName, name) == 0) {
			return symtab->lookup[ind];
		}
	}
	return 0; // zero implies the symbol is not defined
}

uint32 addSymbol(SymbolTable *symtab, uint8 *name, SymbolType type, uint32 dataIndex) {
	uint32 symbolIndex = lookupSymbolIndex(symtab, name);
	if (symbolIndex != 0) { // already entry for name
		uint8 *existingName = getSymbolName(symtab, symbolIndex);
		if (strcmp(existingName, name) == 0) {
			return 1;
		}
		// this is the weirdo case where two strings hashed to the same thing	
		
	}
	
	return 0;
}

uint8 *getSymbolName(SymbolTable *symtab, uint32 symbolIndex) {
	Symbol *sym = &symtab->symbols[symbolIndex];
	if (sym->hasShortName)
		return sym->name;
	return &symtab->stringTable[sym->nameIndex];
}

// source http://www.cse.yorku.ca/~oz/hash.html
uint32 hashsdbm(uint8 *str) {
	uint32 hash = 0;
	uint32 ch;
	while (ch = *str++)
		hash = ch + (hash << 6) + (hash << 16) - hash;

	return hash;
}

uint32 printSymbolTable(SymbolTable *symtab) {
	printf("===SYMBOL TABLE===\n");
	printf("Lookup:\n");
	for (uint32 i = 0; i < symtab->tableSize; i++) {
		uint32 symbolIndex = symtab->lookup[i];
		if (symbolIndex == 0) continue; // ignore the empty entries
		if (symbolIndex == TOMBSTONE) {
			printf("%u: TOMBSTONE\n", i);
		} else if (symbolIndex >= symtab->symbolCount) {
			printf("%u: INVALID (%u)\n", i, symbolIndex);
		} else {
			printf("%u: symbols[%u] = %s\n", i, symbolIndex, getSymbolName(symtab, symbolIndex));
		}
	}
}
