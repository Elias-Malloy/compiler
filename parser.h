#ifndef PARSER_H
#define PARSER_H

#include "intdef.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


// purposefully ridiculously long (this is used for one or two swap bufs)
#define MAX_IDENTIFIER_LEN 512

// #define isdigit(x) ((x) >= '0' && (x) <= '9')

/*
   call this with a buffer full of source code
   I'm not entirely sure what is produced
   returns a stream of 64 bit ints (high 16 identify) (low 48 address)
*/
uint64 parseSource(uint8 *str);
/*
   read an integer from *buf, and advance *buf by nBytes read
   <digits> is decimal, 0<digits> is octal, 0x<digits> is hex
   if the first character isn't a digit, return 0 and don't advance str
   sign is not parsed here
   str is not null checked, its assumed to be a valid ptr
   ascii is assumed because that's the world we live in
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
