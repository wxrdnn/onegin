#include "h/output.h"
#include <cassert>
#include <cstring>

void DumpIndexBuf(IndexBuffer *indexBuf)
{
    for (size_t i = 0; i < indexBuf->lineCount; ++i)
    {
        fprintf(stderr, "DEBUG: Line %lu: <%s>.\n", i, indexBuf->ptr[i]);
    }
    return;
}

void DumpString(char *s)
{
    assert(s);

    size_t len = strlen(s);
    fprintf(stderr, "DEBUG: Begin string dump:");
    for (size_t i = 0; i < len; ++i)
    {
        fprintf(stderr, "DEBUG: <\'%c\' = %d>\n", s[i], s[i]);
    }
    fprintf(stderr, "DEBUG: End string dump.\n");
    return;
}
void PrintTextToFile(IndexBuffer *indexBuf, FILE *outputFile)
{
    for (size_t i = 0; i < indexBuf->lineCount; ++i)
    {
        // fprintf(stderr, "DEBUG: i: %lu, lineAmount: %lu.\n", i, textBuf->lineAmount);
        assert(indexBuf);
        assert(indexBuf->ptr);
        // DumpString(textBuf->lines[i].ptr);
        fprintf(outputFile, "%s", indexBuf->ptr[i]);
    }
    return;
}
