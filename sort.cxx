#include "h/sort.h"
#include <cctype>
#include <cstdlib>

void SortText(IndexBuffer *indexBuffer, SortingModes sortingMode)
{
    int (*comp)(const void *, const void *);

    switch (sortingMode)
    {
    default:
    case smAscending:
        comp = CompareLinesAscending;
        break;

    case smDescending:
        comp = CompareLinesDescending;
        break;
    }

    qsort(indexBuffer->ptr, indexBuffer->lineCount, sizeof(*indexBuffer->ptr), comp);
    return;
}

int CompareLinesAscending(const void *p1, const void *p2)
{
    const char *const *s1 = (const char *const *)p1;
    const char *const *s2 = (const char *const *)p2;
    return CompareSrings(*s1, *s2);
}

int CompareLinesDescending(const void *p1, const void *p2)
{
    const char *const *s1 = (const char *const *)p1;
    const char *const *s2 = (const char *const *)p2;
    return -CompareSrings(*s1, *s2);
}

int CompareSrings(const char *const s1, const char *const s2)
{
    // size_t len1 = strlen(s1);
    // size_t len2 = strlen(s2);

    // if (len1 != len2)
    // {
    //     return len1 - len2;
    // }
    // else
    // {
    const char *p1 = s1;
    const char *p2 = s2;

    while (*p1 != '\0' && *p2 != '\0')
    {
        if (isspace(*p1))
        {
            ++p1;
            continue;
        }
        if (isspace(*p2))
        {
            ++p2;
            continue;
        }

        if (*p1 != *p2)
        {
            return *p1 - *p2;
        }
        ++p1;
        ++p2;
    }
    // }

    if (*p1 != '\0')
    {
        return 1;
    }
    else if (*p2 != '\0')
    {
        return -1;
    }

    return 0;
}
