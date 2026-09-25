#ifndef SORT_H

#define SORT_H

#include "types.h"

void SortText(IndexBuffer *indexBuffer, SortingModes sortingMode, CompareStringsModes compareMode);

int CompareLinesAscendingFromStart(const void *p1, const void *p2);

int CompareLinesDescendingFromStart(const void *p1, const void *p2);

int CompareLinesAscendingFromEnd(const void *p1, const void *p2);

int CompareLinesDescendingFromEnd(const void *p1, const void *p2);

int CompareSringsFromStart(const char *const s1, const char *const s2);

int CompareSringsFromEnd(const char *const s1, const char *const s2);

#endif
