#ifndef SYMBOL_H
#define SYMBOL_H

#include "intdef.h"
#include "types.h"

typedef uint32 Symbol;

typedef enum SymbolType {
	SYMBOL_KEYWORD,
	SYMBOL_OPERATOR,
	SYMBOL_VARIABLE,
	SYMBOL_CONSTANT,
	SYMBOL_STRING_LITERAL,
	SYMBOL_TYPE,
	SYMBOL_PUNCTUATION,
}

/*
sym[3:0] is symbol type

if symbol type is keyword
sym[7:4] is zero (reserved)
sym[15:8] is a keyword index
sym[31:16] is zero (reserved)

if symbol type is operator
sym[7:4] is zero (reserved)
sym[15:8] is an operator index
sym[31:16] is zero (reserved)

if symbol type is variable
sym[7:4] is zero (reserved)
sym[31:8] is an index into a table describing the variables characteristics

if symbol type is constant
sym[7:4] is zero (reserved)
sym[31:8] is an index into a table storing contant values and their types

if symbol type is string literal
sym[31:4] is an address into the string table

if symbol type is SYMBOL_TYPE
sym[7:4] is level of indirection. An indirection of 15 marks an ind ext,
	meaning another uint32 follows the symbol storing the real ind level
sym[31] is the array flag meaning a uint32 size follows the symbol
sym[30:8] is a unique identifier for the type. This value will be used to 
	lookup into tables describing type characteristics

sym <optional-indirection-ext> <optional-array-size-ext>

if symbol type is punctuation
sym[7:4] is zero (reserved)
sym[15:8] is a punctuation mark index

*/

#endif
