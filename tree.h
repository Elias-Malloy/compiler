#ifndef TREE_H
#define TREE_H

#include "intdef.h"
#include "symbol.h"
#include "operator.h"

typedef struct Tree {
	uint16 type;		// identifier for node type
	uint16 branchCount; // length of branches array
	uint32 location;    // location within source code
	Tree *branches[1];   // possibly overallocated array of branches
} Tree;

enum TreeNodeType {
	// unary operators branch 0 is operand expr
	TREE_OP_POST_INC,
	TREE_OP_POST_DEC,
	TREE_OP_FUNCTION_CALL,
	TREE_OP_SUBSCRIPT,
	TREE_OP_DIRECT_MEMBER_ACCESS,
	TREE_OP_INDIRECT_MEMBER_ACCESS,
	TREE_OP_PRE_INC,
	TREE_OP_PRE_DEC,
	TREE_OP_POSITIVE,
	TREE_OP_NEGATIVE,
	TREE_OP_LOGICAL_NOT,
	TREE_OP_COMPLEMENT,
	TREE_OP_REF,
	TREE_OP_DEREF,
	TREE_OP_SIZEOF,
	TREE_OP_ALIGNOF,
	// binary operators branch 0,1 are operand exprs
	TREE_OP_MUL,
	TREE_OP_DIV,
	TREE_OP_MOD,
	TREE_OP_ADD,
	TREE_OP_SUB,
	TREE_OP_LSHIFT,
	TREE_OP_RSHIFT,
	TREE_OP_CMP_L,
	TREE_OP_CMP_G,
	TREE_OP_CMP_LE,
	TREE_OP_CMP_GE,
	TREE_OP_CMP_EQ,
	TREE_OP_CMP_NEQ,
	TREE_OP_AND,
	TREE_OP_XOR,
	TREE_OP_OR,
	TREE_OP_LOGICAL_AND,
	TREE_OP_LOGICAL_OR,
	TREE_OP_ASSIGN,
	TREE_OP_COMMA,
	TREE_NOP,

	TREE_VALUE, // branch 0 is type, branch 1 is location, branch 2 is value-ptr of immediate if relevent
	
	TREE_TYPE_BUILT_IN, // branch 0 is an integer contant identifying the built in
	TREE_TYPE_POINTER, // branch 0 points to a type tree
	TREE_TYPE_ARRAY, // branch 0 points to a type tree, branch 1 is an integer size of array
	TREE_TYPE_STRUCT, // branches are decls for fields
	TREE_DECL, // branch 0 points to a type tree, branch 1 is a pointer to a string name

	TREE_STMTS,
	TREE_STMT_IF,
	TREE_STMT_FOR,
	TREE_STMT_WHILE,
	TREE_STMT_RETURN,
};

uint32 typecheckTree(Tree *t)

// returns true if t represents an expression tree which
// evaluates to an assignable value
bool exprIsAssignable(Tree t, Symbol *symbols);

// returns a type index of the expression t represents
// 0 (void) is returned if t doesn't logically have a datatype
uint32 typeofExpr(Tree t, Symbol *symbols);

// prints out a text representation of a tree
void printTree(Tree t, Symbol *symbols);

#endif
