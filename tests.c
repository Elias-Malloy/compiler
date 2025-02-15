#include "tests.h"

void testReadInteger(void) {
	
	uint8 *str = "1234!";
	uint64 n = readInteger(&str);
	assert(n == 1234);
	assert(*str == '!');
	
	str = "0x1234!";
	n = readInteger(&str);
	assert(n == 0x1234);
	assert(*str == '!');
	
	str = "0123456789!";
	n = readInteger(&str);
	assert(n == 01234567);
	assert(*str == '8');

	str = "0";
	n = readInteger(&str);
	assert(n == 0);
	assert(*str == 0);

	str = "emm";
	n = readInteger(&str);
	assert(n == 0);
	assert(*str == 'e');

	printf("readInteger tests passed\n");
}

