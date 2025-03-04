#ifndef INTDEF_H
#define INTDEF_H

#include <stdint.h>

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef  int8_t   int8;
typedef  int16_t  int16;
typedef  int32_t  int32;
typedef  int64_t  int64;

typedef uint8_t bool;

#define true  (bool)1
#define false (bool)0

// not really ints
typedef double float64;
typedef float  float32;

#endif
