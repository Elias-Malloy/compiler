#include "parser.h"


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
