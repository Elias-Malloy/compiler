#ifndef OPERATOR_H
#define OPERATOR_H

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
	// unary post
	[OP_POST_INC] = 14, [OP_POST_DEC] = 14, 
	[OP_FUNCTION_CALL] = 14, [OP_SUBSCRIPT] = 14,
	[OP_DIRECT_MEMBER_ACCESS] = 14,
	[OP_INDIRECT_MEMBER_ACCESS] = 14,
	
	// unary pre
	[OP_PRE_INC] = 13, [OP_PRE_DEC] = 13,
	[OP_POSITIVE] = 13, [OP_NEGATIVE] = 13,
	[OP_LOGICAL_NOT] = 13, [OP_COMPLEMENT] = 13,
	[OP_REF] = 13, [OP_DEREF] = 13,
	[OP_SIZEOF] = 13, [OP_ALIGNOF] = 13,

	// binary
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

/* these tables will be used if precedence info is ever incomplete


bool OP_IS_UNARY_PRE_TABLE[OPERATOR_COUNT] = {
	[OP_PRE_INC] = true, [OP_PRE_DEC] = true,
	[OP_POSITIVE] = true, [OP_NEGATIVE] = true,
	[OP_LOGICAL_NOT] = true, [OP_COMPLEMENT] = true,
	[OP_REF] = true, [OP_DEREF] = true,
	[OP_SIZEOF] = true, [OP_ALIGNOF] = true,
};

bool OP_IS_UNARY_POST_TABLE[OPERATOR_COUNT] = {
	[OP_POST_INC] = true, [OP_POST_DEC] = true, 
	[OP_FUNCTION_CALL] = true, [OP_SUBSCRIPT] = true,
	[OP_DIRECT_MEMBER_ACCESS] = true,
	[OP_INDIRECT_MEMBER_ACCESS] = true,
};
*/


#endif
