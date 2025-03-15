#ifndef SYMBOL_H
#define SYMBOL_H

#include "intdef.h"
#include "types.h"

typedef enum SymbolType {
	NONE=0,
	SYM_TYPE_NAME,
	SYM_TYPE_MODIFIER,
	SYM_VARIABLE,
	SYM_CONSTANT,
	SYM_FUNCTION, // may be redundant with variable but we'll see
	SYM_KEYWORD_IF,
	SYM_KEYWORD_ELSE,
	SYM_KEYWORD_FOR,
	SYM_KEYWORD_WHILE,
	SYM_KEYWORD_BREAK,
	SYM_KEYWORD_CONTINUE,
	SYM_KEYWORD_RETURN,
	SYM_KEYWORD_SIZEOF,
} SymbolType;

typedef struct Symbol { // 16 bytes
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

#endif
