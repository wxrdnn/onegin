#include "h/sort.h"
#include "h/types.h"
#include <cctype>
#include <cstdlib>
#include <cstring>

void SortText(IndexBuffer *indexBuffer, SortingModes sortingMode, CompareStringsModes compareMode)
{
    int (*comp)(const void *, const void *);

    switch (sortingMode)
    {
    default:
    case smAscending:
        switch (compareMode)
        {
        default:
        case csmFromStart:
            comp = CompareLinesAscendingFromStart;
            break;
        case csmFromEnd:
            comp = CompareLinesAscendingFromEnd;
            break;
        }
        break;

    case smDescending:
        switch (compareMode)
        {
        default:
        case csmFromStart:
            comp = CompareLinesDescendingFromStart;
            break;
        case csmFromEnd:
            comp = CompareLinesDescendingFromEnd;
            break;
        }
        break;
    }

    qsort(indexBuffer->ptr, indexBuffer->lineCount, sizeof(*indexBuffer->ptr), comp);
    return;
}

int CompareLinesAscendingFromStart(const void *p1, const void *p2)
{
    const String_t *const *str1 = (const String_t *const *)p1;
    const String_t *const *str2 = (const String_t *const *)p2;
    return CompareSringsFromStart((*str1)->data, (*str2)->data);
}

int CompareLinesDescendingFromStart(const void *p1, const void *p2)
{
    const String_t *const *str1 = (const String_t *const *)p1;
    const String_t *const *str2 = (const String_t *const *)p2;
    return -CompareSringsFromStart((*str1)->data, (*str2)->data);
}

int CompareLinesAscendingFromEnd(const void *p1, const void *p2)
{
    const String_t *const *str1 = (const String_t *const *)p1;
    const String_t *const *str2 = (const String_t *const *)p2;
    return CompareSringsFromEnd((*str1)->data, (*str2)->data);
}

int CompareLinesDescendingFromEnd(const void *p1, const void *p2)
{
    const String_t *const *str1 = (const String_t *const *)p1;
    const String_t *const *str2 = (const String_t *const *)p2;
    return -CompareSringsFromEnd((*str1)->data, (*str2)->data);
}

int CompareSringsFromStart(const char *const s1, const char *const s2)
{
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

int CompareSringsFromEnd(const char *const s1, const char *const s2)
{
    const char s1FirstChar = *s1;
    const char s2FirstChar = *s2;

    const char *p1 = s1 + strlen(s1);
    const char *p2 = s2 + strlen(s2);

    while (*p1 != s1FirstChar && *p2 != s2FirstChar)
    {
        if (isspace(*p1))
        {
            --p1;
            continue;
        }
        if (isspace(*p2))
        {
            --p2;
            continue;
        }

        if (*p1 != *p2)
        {
            return *p1 - *p2;
        }
        --p1;
        --p2;
    }

    if (*p1 != s1FirstChar)
    {
        return 1;
    }
    else if (*p2 != s2FirstChar)
    {
        return -1;
    }

    return 0;
}
