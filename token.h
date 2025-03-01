#ifndef TOKEN_H
#define TOKEN_H

#include "intdef.h"

typedef union Token {
	TokenTypeName typeName;
	TokenKeyword keyword;
} Token;

typedef struct TokenTypeName {
	uint16 tokenType;	// TokenType enum value identifying this struct
	uint16 indirection;	// rate how many stars
	uint32 modifiers;	// idk like const, volatile that sorta thing (bitmask)
	uint32 typeId;		// lookup into type table
} TokenTypeName;

typedef struct TokenKeyword {
	uint16 tokenType;	// TokenType enum value identifying this struct
	uint16 keywordId;	// numeric identifier for keyword
} TokenKeyword;


// constants retain type information to enable overloaded ops on constant vals
// such as SUNDAY + 1 = MONDAY but also MONDAY + 6 = SUNDAY
// this allows groups to be expressed simply

// keywords introduce punctuation requirements

enum TokenType {
	TOKEN_TYPE_NAME,
	TOKEN_TYPE_MODIFIER,
	TOKEN_KEYWORD, // may be changed
	TOKEN_CONSTANT, // could be an integer, float, string literal
	TOKEN_VARIABLE,
	TOKEN_PUNCTUATION,
	TOKEN_OPERATOR	
};


#endif
