#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

/* EMM */

typedef enum SymbolType {
	NONE=0,
	TYPE_DEFINITION,
	VARIABLE,
	CONSTANT,
	LITERAL,
} SymbolType;

typedef struct Symbol {
	SymbolType symType;	// if this is zero, the other stuff isn't actually here
	uint32 offset;		// index of lookup in relevant table for symboltype
	union {
		uint8 name[8];
		struct {
			uint32 hasShortName; // zero if name is > 7 chars
			uint32 nameIndex; // lookup into string table
		};
	};
} Symbol;

typedef struct SymbolTable {	
	Symbol *symbols;
	uint32 *lookup;
	uint32 symbolCount;
	uint32 tableSize;
	uint8 *stringTable;
	uint32 stringTableSize;
} SymbolTable;


//uint32 deleteLookupEntry(SymbolTable *symtab, uint32 symbolIndex);
uint32 lookupSymbolIndex(SymbolTable *symtab, uint8 *name);
uint32 addSymbol(SymbolTable *symtab, uint8 *name, SymbolType type, uint32 dataIndex);
uint8 *getSymbolName(SymbolTable *symtab, uint32 symbolIndex) {
uint32 hashsdbm(uint8 *str);

#endif
