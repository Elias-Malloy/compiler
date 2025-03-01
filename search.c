#include "search.h"

uint32 binarySearch(uint32 *sorted, uint32 start, uint32 end, uint32 value) {
	uint32 len = end - start;
	if (len <= 1) return start;

	uint32 midIndex = start + (len / 2);
	uint32 midValue = sorted[midIndex];
	if (value < midValue) {
		return binarySearch(sorted, start, midIndex, value);
	} else if (value > midValue) {
		return binarySearch(sorted, midIndex, end, value);
	}
	return midIndex;
}
