#include "parser.h"

// global scope vs function scope
// nested scope to the 0 or nth degree

// is a typename acceptable?
// is a type instance accpetable
// which types are acceptable (probably next pass)
// which type conversions need to / can be performed to make a expr valid
// which operators are valid?

// are we at the start of an expression? opening a paren starts an expression

// are we in a function definition
// are we in a function call

// are we expecting an expression (e.g. saw "-" as last symbol)

// this first pass doesn't look far forward while processing the current symbol
// but previous symbols can inform which current symbols are valid.
// the tape is consumed as it is read, so direct access to earlier tape
// positions is disallowed. This means symbols must update a grammar
// state machine. This machine must be updated in a number of ways
// for each new symbol that is read.

// at the different stages of the compiler, we represent the same idea
// in different bytes. Intermediates are almost irrational because of this,
// so if there is an intermediate, there should be a good reason for it.

// was the previous symbol a valid l-value (i.e. is assignment valid)

// is space acceptable?

// are we expecting an identifier?
// are we in a variable definition

// expression expression is never valid
// op op is sometimes valid (e.g. !  !  expr)

/*
definition <typename> [<optional-indirection> 
                       <undefined-identifier>
					   <optional-assignment>] [1..n]

the word function isn't written

function <typename> <optional-indirection>
                    <open-paren>
                    <typename> <undefined-identifier>
                    [<comma> <typename> <undefined-identifier>] [0..n]
                    <close-paren> <open-brace> <statement>[0..n] <close-brace>


*/

uint64 parseSource(uint8 *s, TreeRoot *root, SymbolTable *symbolTable, LineTable *lineTable) {
	if (s == NULL) return 1;

	if (functionIndexTable == NULL) return 1;

	LineTable *lineTable = malloc(8 + 256 * 4);

	globalPrePass(s, root, symbolTable, lineTable, functionIndexTable);
	for (uint32 i = 0; i < functionIndexTable->count, i++) {
		uint32 start = functionIndexTable->indices[i].start;
		uint32 end   = functionIndexTable->indices[i].end;
		// update index table with starting node offset of function tree
		functionIndexTable->indices[i].start = root->top;
		// fill out tree and symbol table with funciton information
		parseFunction(s, start, end, root, symbolTable, lineTable);
		// update index table with ending node offset of function tree
		functionIndexTable->indices[i].end = root->top;
	}
	// next compile all the functions based on tree and symbol table
	free(lineTable);
	free(functionIndexTable);
	return 0;
}

uint64 parseFunction(const uint8 *s, const uint32 start, const uint32 end, TreeRoot *root, 
	SymbolTable *symbolTable, const LineTable *lineTable) {
	uint8 *identfier = malloc(MAX_IDENTIFIER_LEN);
	if (identifier == NULL) { // error out of memory
		return 1;
	}
	vec32 *branchStack = vec32Create(256);
	if (branchStack == NULL) {
		return 1; // e out of mem
	}
	

	uint32 j;
	uint8 c;

	for (uint32 i = start; i < end; i++) {
		switch (s[i]) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				// read integer
				break;
			
			case 'A': case 'B': case 'C': case 'D': case 'E':
			case 'F': case 'G': case 'H': case 'I': case 'J':
			case 'K': case 'L': case 'M': case 'N': case 'O':
			case 'P': case 'Q': case 'R': case 'S': case 'T':
			case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
			case 'a': case 'b': case 'c': case 'd': case 'e':
			case 'f': case 'g': case 'h': case 'i': case 'j':
			case 'k': case 'l': case 'm': case 'n': case 'o':
			case 'p': case 'q': case 'r': case 's': case 't':
			case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
			case '_':
				// copy the name into identifier
				j = 0;
				do {
					c = s[i + j];
					identifier[j++] = c;
				} while (isalnum(c) || c == '_');
				i += j - 1; // minus 1 because i will be incremented at end of loop
				uint32 symIdx = lookupSymbolIndex(symbolTable, identifier);
				if (symIdx == 0) {
					printf("Undeclared identifier: \'%s\'\n", identifier);
				}

				break;
			case '/':
				if (s[i + 1] == '/') { // TODO add check for mid-string-literal
					while(i < end && s[i] != '\n') i++; // skip rest of line 
					break; // exit switch
				} else if (s[i + 1] == '*') {
					i += 2; // TODO add stack to support nested block comments
					while (i < end && !(s[i] == '*' && s[i + 1] == '/')) i++;
					break; // exit switch
				}
				// otherwise we have OP_DIV
				// check symbol 
				if (currentBranch.type & TREE_EXPR_BIT == 0) {
					printf("Error expected first operand to division\n");
				}
			case '*':
				// TODO consider deref opp
				// TODO consider mark of indirection in declaration
				
				// we have OP_MUL
				
			case '(':

				break;

			default:
				printf("Unrecognized symbol (%c) at %u\n", s[i], i);
		}
	}
	free(identifier);
	vec32Free(branchStack);

	return 0;
}


// OLD CODE BELOW
/*

uint64 parse(uint8 *str) {
	// in global scope, we are expecting
	// a function definition
	// a variable/constant definition
	// assignment to a variable, with a valuable computable at compiletime
	// a type definition
	// an operator definition
	// an enum definition

	// we first cruise through in global scope, write down all the 
	// str addresses of functions we need to compile
	// we also define and evaluate global variables
	// we also evaluate type definitions and enum constants
	// we also note operator definitions and write down address for compile

	// then once that pass is done, we use the global info to compile
	// all the functions

	// this could be two functions but they are so similar
	// its a few added checks, major repetition avoided
	// keeps the binary small too

	// in the global pass, when we encounter a function def,
	// after the parameter list, we only keep a bracket stack,
	// and continue normally once its empty

	// read symbol
	// react to it
	// wow
	uint64 line = 0, col = 0;
	uint64 n;
	float64 f;
	// all these bools may end up as one or two uint64s eventually
	uint8 emptyline = 1; // is the current line empty (besides whitespace)

// this is how you make a while loop when you're dumb and don't like indents
begin:
	switch (*str) {
		case '\t': // who cares about whitespace
			col += TAB_WIDTH - 1;
		case ' ':
			col++;
			str++;
			break;
		case '\n':
			line++;
			col = 0;
			emptyline = 1;
			break;

		case '/':
			str++;
			if (*str == '/') {        // line comment
				do str++;
				while (*str != '\n' && *str != '\0');
				line++;
			} else if (*str == '*') {
				do {
					str++;
					col++;
					if (*str == '\n') { // I really hate this
						line++;
						col = 0;
						emptyline = 1;
					}
				} while (!(*str == '*' && str[1] == '/') && *str != '\0');
			} else {
				// parse operator
			}
			break;
		
		case '<':
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			n = readInteger(&str);
			if (*str == '.') {
				f = readFloat(&str);
				f += (float64) n;
				// add float constant to stream
			} else {
				// add integer constant to stream
			}

			break;

		case '\0':
			goto done;
	}
	
	goto begin;

done:
	return 0;
}


uint64 parseSource(uint8 *str) {
	// we need a string table. store str8s, sign-bit marks string-table index
	// we need a bracket stack

	// scope stack stores valid symbols at current scope
	// encoded as top of sym stack

	uint8 *identifier = aligned_alloc(32, MAX_IDENTIFIER_LEN);
	if (identifier == NULL) {
		printf("Error out of memory\n");
		return ~0ull;
	}

	// expression tree

	while (1) {
		switch (*str) { 
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				//uint64 n = readInteger(&str);
				if (*str == '.') {
					// respond to floating point
				}
				
				break;
			case 'A': case 'B': case 'C': case 'D': case 'E':
			case 'F': case 'G': case 'H': case 'I': case 'J':
			case 'K': case 'L': case 'M': case 'N': case 'O':
			case 'P': case 'Q': case 'R': case 'S': case 'T':
			case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
			case 'a': case 'b': case 'c': case 'd': case 'e':
			case 'f': case 'g': case 'h': case 'i': case 'j':
			case 'k': case 'l': case 'm': case 'n': case 'o':
			case 'p': case 'q': case 'r': case 's': case 't':
			case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
			case '_':
				//uint64 len = readIdentifier(&str, identifier);
				
				break;

			case '.':
				// was there a space previously, if 
				// did the preceding expression support direct member access?
				// was the preceding symbol an integer
				break;
		
			case '-':
				// is the next symbol a >, if so does the preceding
				// expression support indirect member access?
				// if so, read identifier and lookup in member names
				// for preceding type
				// if identifier is len 0 or unknown member, error

				// otherwise, mark that we are expecting an expression
				// is the next symbol =, if so check if previous is lvalue
				// space is acceptable

			case '+':
				// check lvalue if next is =
				// mark expecting symbol

			case '*':
				// if expecting expression, 

			default:
				printf("Unrecognized symbol %c (hex: %X)\n", *str, *str);			
		}
	}

	free(identifier);

	return 0;
}

uint64 readInteger(uint8 **buf) {
	uint8 *str = *buf;
	if (!isdigit(*str)) return 0;
	uint64 n = 0, i = 0; // n is return value, i is number of bytes read
	if (*str == '0') {
		i++;
		if (isdigit(str[i])) {
			// Octal
			for (; isdigit(str[i]); i++) {
				if (str[i] >= '8') break; 
				n = (n << 3) + (str[i] - '0');
			}
		} else if (str[i] == 'x') {
			// Hex (useless confusion below)
			while (i++) { // won't run more than 18446744073709551615 times :)
				uint64 m = str[i];
				if (isdigit(m)) {
					m -= '0';
				} else if (m >= 'a' && m <= 'f') {
					m -= 'a' + 10;
				} else if (m >= 'A' && m <= 'F') {
					m -= 'A' + 10;
				} else break;
				n = (n << 4) + m;
			}
		}
	} else {
		// Decimal
		for (; isdigit(str[i]); i++) {
			n = (n * 10) + (str[i] - '0');
		}
	}
	*buf += i;
	return n;
}

uint64 readDecimalInteger(uint8 **buf) {
	uint8 *str = *buf; 
	uint64 n = 0, i = 0;
	// if this was asm I'd jump to the final else of readInteger
	// but goto between functions isn't allowed in standard C
	for (; isdigit(str[i]); i++) {
		n = (n * 10) + (str[i] - '0');	
	}
	*buf += i;
	return n;
}

float64 readFloat64(uint8 **buf) {
	// leave it to the pros (I'll do it myself later)
	return strtod(*buf, buf);
}

uint64 readIdentifier(uint8 **buf, uint8 *dst) {
	uint64 i = 0;
	uint8 *src = *buf;
	if (isalpha(*src) || *src == '_') {
		*dst = *src;
		for (i = 1; i < MAX_IDENTIFIER_LEN; i++) {
			if (!isalnum(src[i]) && src[i] != '_') break;
			dst[i] = src[i];
		}
	}
	*buf += i;
	dst[i] = '\0';
	return i;
}
*/
