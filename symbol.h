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
} SymbolType;

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

// grouped by precedence, precedence is same as C
typedef enum Operator {
	OP_POST_INC,                // ++
	OP_POST_DEC,                // --
	OP_FUNCTION_CALL,           // ()
	OP_SUBSCRIPT,               // []
	OP_DIRECT_MEMBER_ACCESS,    // .
	OP_INDIRECT_MEMBER_ACCESS,  // ->
	
	OP_PRE_INC,                 // ++
	OP_PRE_DEC,                 // --
	OP_POSITIVE,                // +
	OP_NEGATIVE,                // -
	OP_LOGICAL_NOT,             // !
	OP_COMPLEMENT,              // ~
	OP_REF,                     // &
	OP_DEREF,                   // *
	OP_SIZEOF,                  // sizeof
	OP_ALIGNOF,                 // alignof

	OP_MUL,                     // *
	OP_DIV,                     // /
	OP_MOD,                     // %

	OP_ADD,                     // +
	OP_SUB,                     // -

	OP_LSHIFT,                  // <<
	OP_RSHIFT,                  // >>
	
	OP_CMP_L,                   // <
	OP_CMP_G,                   // >
	OP_CMP_LE,                  // <=
	OP_CMP_GE,                  // >=
	
	OP_CMP_EQ,                  // ==
	OP_CMP_NEQ,                 // !=
	
	OP_AND,                     // &
	
	OP_XOR,                     // ^
	
	OP_OR,                      // |
	
	OP_LOGICAL_AND,             // &&
	
	OP_LOGICAL_OR,              // ||
	
	OP_ASSIGN,                  // =
	
	OP_COMMA,                   // ,
	
	OPERATOR_COUNT
} Operator;

// higher is executed first
uint8 OP_PRECEDENCE_TABLE[OPERATOR_COUNT] = {
	
	[OP_POST_INC] = 14, [OP_POST_DEC] = 14, 
	[OP_FUNCTION_CALL] = 14, 
	[OP_SUBSCRIPT] = 14,
	[OP_DIRECT_MEMBER_ACCESS] = 14,
	[OP_INDIRECT_MEMBER_ACCESS] = 14,

	[OP_PRE_INC] = 13, [OP_PRE_DEC] = 13,
	[OP_POSITIVE] = 13, [OP_NEGATIVE] = 13,
	[OP_LOGICAL_NOT] = 13, [OP_COMPLEMENT] = 13,
	[OP_REF] = 13, [OP_DEREF] = 13,
	[OP_SIZEOF] = 13, [OP_ALIGNOF] = 13,

	[OP_MUL] = 12, [OP_DIV] = 12, [OP_MOD] = 12,

	[OP_ADD] = 11, [OP_SUB] = 11,

	[OP_LSHIFT] = 10, [OP_RSHIFT] = 10,

	[OP_CMP_L] = 9, [OP_CMP_G] = 9, [OP_CMP_LE] = 9, [OP_CMP_GE] = 9,

	[OP_CMP_EQ] = 8, [OP_CMP_NEQ] = 8,

	[OP_AND] = 7,

	[OP_XOR] = 6,

	[OP_OR] = 5,

	[OP_LOGICAL_AND] = 4,

	[OP_LOGICAL_OR] = 3,

	[OP_ASSIGN] = 2,

	[OP_COMMA] = 1,
};


#endif
