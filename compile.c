#include "compile.h"
#include "assertm.h"


uint32 compileTree(Tree t, X86_64_Assembly *assembly);

uint32 compileStmts(Tree *t, X86_64_Assembly *assembly) {
	ASSERT_M(t->type == TREE_STMTS, "expected tree of statements\n");
	uint32 end = t->branchCount;
	for (uint32 i = 0; i < end; i++) {
		compileStmt(t->branch[i]);
	}
}

uint32 compileStmt(Tree *t) {
	switch (t->type) {
		case TREE_STMT_IF:
			// evaluate condition
			compileCondition(t->branch[0]);
			
			// insert condition and jump to conditional code
			if (t->branchCount == 3) { // else condition is present
				compileStmts(t->branch[2]); // compile if body
			}
			// jmp to post if
			// insert if-body-label
			compileStmts(t->branch[1]); // compile if body
			// insert end-if-label
		case TREE_STMT_FOR:
			
		case TREE_STMT_WHILE:
		case TREE_STMT_RETURN:
		
		default:
			return 1;
		
	}
	return 0;
}

uint32 compileExpr(Tree *t) {
	if (t->type == TREE_VALUE) return 0; // do nothing
	if (t->type < TREE_OP_COMMA) return 1; // error expected operator
	// evaluate sub expressions
	if (t->branch[0]->type != TREE_VALUE)
		compileExpr(t->branch[0]);
	if (t->type <= TREE_OP_MUL && t->branch[1]->type != TREE_VALUE)
		compileExpr(t->branch[1]);

	switch (t->type) {
		case TREE_OP_ADD:
			
			break;
		default:
			return 1;
	}

	return 0;
}

uint32 compileCondition(Tree *t) {
	switch(t->type) {
		case TREE_OP_LOGICAL_NOT:
			; bool inverted = true;
			switch (t->branch[0]->type) {
				case TREE_OP_CMP_L:
					t->branch[0]->type = TREE_OP_CMP_GE;
					break;
				case TREE_OP_CMP_G:
					t->branch[0]->type = TREE_OP_CMP_LE;
					break;
				case TREE_OP_CMP_LE:
					t->branch[0]->type = TREE_OP_CMP_G;
					break;
				case TREE_OP_CMP_GE:
					t->branch[0]->type = TREE_OP_CMP_L;
					break;
				case TREE_OP_CMP_EQ:
					t->branch[0]->type = TREE_OP_CMP_NEQ;
					break;
				case TREE_OP_CMP_NEQ:
					t->branch[0]->type = TREE_OP_CMP_EQ;
					break;
				case TREE_OP_LOGICAL_AND:
					t->branch[0]->type = TREE_NOP; // mark as nop temporarily
				case TREE_OP_LOGICAL_OR:
					// apply demorgan laws to simplify expression
					Tree *splices = malloc(sizeof(Tree) * 2);	
					if (splices == NULL) return 1;
					splices[0].type = splices[1].type = TREE_OP_LOGICAL_NOT;
					splices[0].location = splices[1].location = t->location; // TODO resolve what this is
					splices[0].branchCount = splices[1].branchCount = 1;
					splices[0].branch[0] = t->branch[0]->branch[0];
					splices[1].branch[0] = t->branch[0]->branch[1];
					t->branch[0]->branch[0] = &splices[0];
					t->branch[0]->branch[1] = &splices[1];
					if (t->branch[0]->type == TREE_NOP) // aka branch was and
						t->branch[0]->type = TREE_OP_LOGICAL_OR;
					else
						t->branch[0]->type = TREE_OP_LOGICAL_AND;
					break;

				default:
					inverted = false;
			}
			if (inverted) {
				// not has been evalutated, so is marked as a nop
				t->type = TREE_NOP;
				compileCondition(t->branch[0]);
			} else {
				compileExpr(t->branch[0]);
				// test result
				// jz to label
			}
			break;
		case TREE_OP_CMP_L:
			compileExpr(t->branch[0]);
			compileExpr(t->branch[1]);
			// compare based on locations of results
			break;
		case TREE_OP_CMP_G:
			break;
		case TREE_OP_CMP_LE:
			break;
		case TREE_OP_CMP_GE:
			break;
		case TREE_OP_CMP_EQ:
			break;
		case TREE_OP_CMP_NEQ:
			break;	
		case TREE_OP_LOGICAL_AND:
			compileCondition(t->branch[0]);
			compileCondition(t->branch[1]);
			break;
		case TREE_OP_LOGICAL_OR:
			break;
		
	}
}
