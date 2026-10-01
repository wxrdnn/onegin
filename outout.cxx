#include "h/errorHandle.h"
#include "h/output.h"
#include "h/types.h"
#include <cassert>
#include <cerrno>
#include <cstdio>
#include <cstring>

void DumpIndexBuf(IndexBuffer *indexBuf)
{
    for (size_t i = 0; i < indexBuf->lineCount; ++i)
    {
        fprintf(stderr, "DEBUG: Line %lu: <%s>.\n", i, indexBuf->ptr[i]->data);
    }
    return;
}

void DumpStringRaw(const char *str, const char *name)
{
    assert(str);
    assert(name);
    fprintf(stderr, "DEBUG: <const char *(%s)> dump: <%s>\n", name, str);
}

void DumpStringExpanded(String_t *str, const char *name)
{
    assert(str);
    assert(str->data);

    fprintf(stderr, "DEBUG: Begin <String_t (%s)> dump: \n", name);
    for (size_t i = 0; i < str->length; ++i)
    {
        fprintf(stderr, "DEBUG: <\'%c\' = %d>\n", str->data[i], str->data[i]);
    }
    fprintf(stderr, "DEBUG: End String_t \"%s\" dump.\n", name);
    return;
}

void DumpStringExpanded(const char *str, const char *name)
{
    assert(str);

    fprintf(stderr, "DEBUG: Begin const char* \"%s\" dump:\n", name);
    size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i)
    {
        fprintf(stderr, "DEBUG: <\'%c\' = %d>\n", str[i], str[i]);
    }
    fprintf(stderr, "DEBUG: End const char* \"%s\" dump.\n", name);
    return;
}

Error PrintTextToFile(IndexBuffer *indexBuf, FILE *outputFile)
{
    Error error = CreateError(ecSuccess, "");

    // fprintf(stderr, "DEBUG: in PrintTextToFile: indexBuf->lineCount = %lu\n", indexBuf->lineCount);

    for (size_t i = 0; i < indexBuf->lineCount; ++i)
    {
        // fprintf(stderr, "DEBUG: i: %lu, lineAmount: %lu.\n", i, textBuf->lineAmount);
        assert(indexBuf);
        assert(indexBuf->ptr);
        assert(indexBuf->ptr[i]);
        assert(indexBuf->ptr[i]->data);
        // DUMP_STRING_RAW(indexBuf->ptr[i]->data);
        if (fprintf(outputFile, "%s", indexBuf->ptr[i]->data) < 0)
        {
            error = CreateError(TranslateErrnoCode(errno), "");
            return error;
        }
        fprintf(outputFile, "\n");
    }
    return error;
}
