#ifndef SEARCH_H
#define SEARCH_H

#include "intdef.h"

/*
	This implementation will return the index of sorted where
	the contents of any higher index is greater than value where
	for the returned index i, start <= i < end

	this is being used to find the line number of a source code index
*/
uint32 binarySearch(uint32 *sorted, uint32 start, uint32 end, uint32 value);

#endif
