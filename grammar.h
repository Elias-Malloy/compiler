#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "intdef.h"


// goto labels need to be handled differently
// goto x;, expect x within function scope


typedef uint64 GrammarState;

#define GLOBAL_SCOPE_FLAG			(1ull << 0)
#define LVALUE_PRECEDING_FLAG		(1ull << 1)
#define ARGUMENT
#define PARAMETER

#define IN_STRING_LITERAL

/*

suffixes are a no, constants can be casted or converted implicitely
convert<uint8>(32) aka (uint8) 32
reinterpret<float32>(12) (float32) 

constant :== integer-constant | floating-constant |
             enumeration-constant | character-constant


keywords

break
continue
else
for
goto
if
operator
return
sizeof
switch
typedef
while

built-in types

enum
struct

void
float32
float64
float80
int8
int16
int32
int64
uint8
uint16
uint32
uint64

operators

,

<<
>>

++
--

~
^
&
|
/
%
*
-
+
= (may be modified to <<=, >>=, ~= ^=, &=, |=, /=, %=, *=, -=, +=)
a op= b is resolved to a = a op b, like immediately maybe

relational
==
!=
>
<
>=
<=

logical
!
&&
||

The ternary operator is not supported because its stupid
 
*/

#endif
