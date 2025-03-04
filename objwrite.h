#ifndef OBJWRITE_H
#define OBJWRITE_H

#include "intdef.h"
#include "elf.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ObjectFile {
	char *filename;
	uint64 *code;
	uint64 codeSize;
	uint64 *initializedData;
	uint64 initializedDataSize;
	uint64 uninitializedDataSize;
	uint64 *readonlyData;
	uint64 readonlyDataSize;
	bool gnu; // kinda temporary
} ObjectFile;

uint32 writeElf64(ObjectFile *obj);

#endif
