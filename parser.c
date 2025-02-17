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

uint64 parseSource(uint8 *str) {
	// we need a string table. store str8s, sign-bit marks string-table index
	// we need a bracket stack

	// if you think 32 is dumb just wait till I get a xeon	
	uint8 *identifier = aligned_alloc(32, MAX_IDENTIFIER_LEN);
	if (identifier == NULL) {
		printf("Error out of memory\n");
		return ~0ull;
	}

	while (1) {
		// what symbol is under the tape head?
		switch (*str) { // switch bitch
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
