#ifndef SORT_H

#define SORT_H

enum SortingOptions
{
    soAscending,
    soDescending
};

void SortText(TextBuf *textBuf, SortingOptions sortingOption);

int CompareLineBufsAscending(const void *p1, const void *p2);

int CompareLineBufsDescending(const void *p1, const void *p2);

#endif
