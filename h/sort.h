#ifndef SORT_H

#define SORT_H

#include "input.h"

enum SortingOptions
{
    soAscending,
    soDescending
};

int CompareLinesAscending(const void *p1, const void *p2);

int CompareLinesDescending(const void *p1, const void *p2);

void SortText(IndexBuffer *indexBuffer, SortingOptions sortingOption);

int CompareSrings(const char *const s1, const char *const s2);

#endif
