#ifndef PARSER_H
#define PARSER_H

#include "intdef.h"
#include "symbol.h"
#include "tree.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct LineTable {
	uint32 count;
	uint32 capacity;
	uint32 lines[2]; // overallocated
} LineTable;

typedef struct FunctionIndexTable {
	uint32 count;
	uint32 capacity;
	struct {
		uint32 start;
		uint32 end;
	} indices[1];
} FunctionIndexTable;

bool appendToLineTable(LineTable *lineTable, uint32 lineNumber);
bool appendToFunctionIndexTable(FunctionIndexTable *functionIndexTable, uint32 start, uint32 end);

// purposefully ridiculously long (this is used for one or two swap bufs)
#define MAX_IDENTIFIER_LEN 512

/*
	s is a pointer to source code
	root is a pointer to the memory store of the tree structure
	symtable is a pointer to a symbol table structure

output:
	the tree associated with root is filled out with program structure
	symtable is filled with symbol definitions

	returns 0 on success, otherwise an identifier for failure type
*/
uint64 parseSource(uint8 *s, TreeRoot *root, SymbolTable *symbolTable, LineTable *lineTable);
/*
	The global prepass does the following:
		import external global definitions
		declare global variables and assign global constants
		declare function prototypes
		declare global type definitions
		fill out line table (used for error messages)
		mark start and end of function bodies
		perform a basic check on {([])} nesting
	
	returns 0 on success
*/
uint64 globalPrePass(uint8 *s, TreeRoot root, SymbolTable *symbolTable, LineTable *lineTable,
	FunctionIndexTable *functionIndexTable);

/*
	parse function fills out a tree
	s must be valid and non-zero between s[start] and s[end]
	lineTable is unmodified
	symbolTable is filled with variable declarations, with scoped addends
	root may be reallocated if space runs out in the tree
	root->data[root->top] is implied to be the starting node of the function
*/
uint64 parseFunction(const uint8 *s, const uint32 start, const uint32 end, TreeRoot *root, 
	SymbolTable *symbolTable, const LineTable *lineTable);

// TODO adapt below functions to work with indexes not ptr arithmetic

/*
   read an integer from *buf, and advance *buf by nBytes read
   <digits> is decimal, 0<digits> is octal, 0x<digits> is hex
   if the first character isn't a digit, return 0 and don't advance str
   sign is not parsed here
   str is not null checked, its assumed to be a valid ptr
*/
uint64 readInteger(uint8 **buf);

/*
   same as readInteger, but without support for hex and octal
   this will be used for floating point parsing
*/
uint64 readDecimalInteger(uint8 **buf);


/*
   read a IEEE 754 double-precision float from *buf
   advance *buf by n bytes read
   sign is not parsed
   returns the parsed float
*/
float64 readFloat64(uint8 **buf);

/*
   reads an identifier from buf into dst
   dst must be at least MAX_IDENTIFIER_LEN bytes long
   returns length of the identifier (null terminator not counted)
*/
uint64 readIdentifier(uint8 **buf, uint8 *dst);

#endif
