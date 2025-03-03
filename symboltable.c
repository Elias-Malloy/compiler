#include "symboltable.h"

#define TOMBSTONE UINT32_MAX

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

bool addSymbol(SymbolTable *symtab, uint8 *name, SymbolType type, uint32 dataIndex) {
	uint32 symbolIndex = lookupSymbolIndex(symtab, name);
	if (symbolIndex != 0) { // already entry for name
		uint8 *existingName = getSymbolName(symtab, symbolIndex);
		if (strcmp(existingName, name) == 0) {
			return SYMRES_DUPLICATE;
		}
		// this is the weirdo case where two strings hashed to the same thing	
		
	}
	
	return SYMRES_SUCCESS;
}

uint8 *getSymbolName(SymbolTable *symtab, uint32 symbolIndex) {
	Symbol *sym = &symtab->symbols[symbolIndex];
	if (sym->hasShortName)
		return sym->name;
	return symtab->stringTable[sym->nameIndex];
}

// source http://www.cse.yorku.ca/~oz/hash.html
uint32 hashsdbm(uint8 *str) {
	uint32 hash = 0;
	uint32 ch;
	while (ch = *str++)
		hash = ch + (hash << 6) + (hash << 16) - hash;

	return hash;
}
