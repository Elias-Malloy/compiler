#ifndef TREE_H
#define TREE_H

#include "intdef.h"
#include "symbol.h"

typedef struct Tree {
	uint8  context;
	uint8  type;
	uint16 branchCount; 
	uint32 offset;
} Tree;

typedef struct TreeRoot {
	Tree *data; // where tree entries are stored
	uint32 top; // index into data, where new entries may go
	uint32 capacity; // limit of entries that can be made into data, before resizing
} TreeRoot;

// language notes

// there is nothing special about an initializer value such as with c array initializers

// statement -> compound statement(8*statement(empty to mark end, ext to mark continueation))
// statement -> if (expression, statement, optional-statement(else clause))
// statement -> for (expression(decl permitting), condition, expression)
// statement -> expression
// statement -> decl-expression 2-branch base-type decl-triplet or comma(decl-triplet, decl-tiplet)
// decl-triplet 3-branch optional-indirection name optional-expression(assigned-value)

// expression -> constant
// expression -> variable
// expression -> binary-op(expression, expression)
// expression -> unary-op(expression)

// if operator expression, the operator is encoded in the node, branches are operands, the op holds post/pre info
// at the tree level, operator precedence has already been resolved
// op comma must be an op for within decl
// 


enum TreeNodeType {
	TREE_EMPTY = 0, // sentinal marker for end of entry
	TREE_BRANCH_EXT, // sentinal to mark n additional branches at the current node, found at offset

	TREE_EXPR_BIT = 0x40, // general expression //

	TREE_EXPR_OP_POST_INC = TREE_EXPR_BIT | OP_POST_INC,
	TREE_EXPR_OP_PRE_INC = TREE_EXPR_BIT | OP_PRE_INC,
	TREE_EXPR_OP_ADD = TREE_EXPR_BIT | OP_ADD,

	TREE_EXPR_OP_COMMA = TREE_EXPR_BIT | OP_COMMA,
	
	TREE_EXPR_VARIABLE = TREE_EXPR_BIT | OPERATOR_COUNT, // place after all operators

	TREE_STMT = 0x80, // general statement
	TREE_STMT_COMPOUND = TREE_STMT | 1, // offset marks the start of a TREE_EMPTY terminated sequence of statements

	TREE_STMT_IF = TREE_STMT | 2, // 3-branch, expr(condition) statement(body) statement(else clause, TREE_EMPTY to omit)
	TREE_STMT_FOR = TREE_STMT | 3, // 4-branch expr(decl-allowed) expr(condition) expr(increment) statement(body)
	TREE_STMT_WHILE = TREE_STMT | 4, // 2-branch expr(condition) statement(body)
}

// assignment -> (lvalue, expression)

// returns true if t represents an expression tree which
// evaluates to an assignable value
bool exprIsAssignable(Tree t, Symbol *symbols);

// returns a type index of the expression t represents
// 0 (void) is returned if t doesn't logically have a datatype
uint32 typeofExpr(Tree t, Symbol *symbols);

// prints out a text representation of a tree
void printTree(Tree t, Symbol *symbols);

#endif
