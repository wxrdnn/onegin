#ifndef TYPES_H

#define TYPES_H

#include <cstddef>

struct String_t
{
    const char *data;
    size_t length;
};

struct IndexBuffer
{
    String_t **ptr;
    size_t size;
    size_t lineCount;
};

enum SortingModes
{
    smAscending,
    smDescending
};

enum CompareStringsModes
{
    csmFromStart,
    csmFromEnd
};

struct LaunchOptions
{
    const char *inputFileName;
    const char *outputFileName;
    SortingModes sortingMode;
};

#endif
