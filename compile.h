#ifndef COMPILE_H
#define COMPILE_H

typedef struct X86_64_Assembly {
	uint8 *code;
	uint64 size;
} X86_64_Assembly;

uint32 compileTree(Tree t, X86_64_Assembly *assembly);

uint32 compileFunction(Tree t, X86_64_Assembly *assembly);

#endif
