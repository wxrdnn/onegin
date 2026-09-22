#ifndef TYPES_H

#define TYPES_H

#include <cstddef>

struct IndexBuffer
{
    char **ptr;
    size_t size;
    size_t lineCount;
};

enum SortingModes
{
    smAscending,
    smDescending
};

struct LaunchOptions
{
    const char *inputFileName;
    const char *outputFileName;
    SortingModes sortingMode;
};

#endif
