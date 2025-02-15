#ifndef PARSER_H
#define PARSER_H

#include "intdef.h"
#include <ctype.h>

// #define isdigit(x) ((x) >= '0' && (x) <= '9')

/*
   read an integer from *str, and advance *str by nBytes read
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

#endif
