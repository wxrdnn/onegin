#include "h/input.h"
#include "h/errorHandle.h"
#include "h/types.h"
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

Error GetFileSize(const char *const path, size_t *size)
{
    struct stat buf = {};
    int errnoCode = stat(path, &buf);
    Error error = CreateError(TranslateErrnoCode(errnoCode), path);
    *size = (size_t)buf.st_size;
    return error;
}

Error LoadText(const int fd, char *const textBuf, const size_t fileSize) // needs textBuf size of <fileSize + 1>
{
    long int numberRead = read(fd, textBuf, fileSize);
    Error error = CreateError(ecSuccess, "");
    if (numberRead != (long int)fileSize)
    {
        error.exitCode = ecCantReadFile;
        return error;
    }

    textBuf[fileSize] = '\0';

    return error;
}

Error CreateTextBuf(const size_t size, char **textBuf)
{
    assert(textBuf);
    *textBuf = (char *)calloc(size, sizeof(char));
    Error error = CreateError(ecSuccess, "");
    if (!*textBuf)
    {
        error = CreateError(ecCantAllocateMemory, "text buffer");
        return error;
    }
    return error;
}

Error CreateIndexBuffer(const size_t startSize, IndexBuffer **indexBuffer)
{
    assert(indexBuffer);
    Error error = CreateError(ecSuccess, "");
    *indexBuffer = (IndexBuffer *)malloc(sizeof(IndexBuffer));

    if (!indexBuffer)
    {
        error = CreateError(ecCantAllocateMemory, "index buffer");
        return error;
    }

    (*indexBuffer)->size = startSize;
    (*indexBuffer)->lineCount = 0;
    (*indexBuffer)->ptr = (char **)calloc(startSize, sizeof(char *));

    if (!(*indexBuffer)->ptr)
    {
        error = CreateError(ecCantAllocateMemory, "index buffer lines");
        return error;
    }

    return error;
}

Error ExtendIndexBuffer(IndexBuffer **indexBuffer)
{
    assert(indexBuffer);
    Error error = CreateError(ecSuccess, "");

    size_t newSize = (*indexBuffer)->size * 2;
    (*indexBuffer)->ptr = (char **)realloc((*indexBuffer)->ptr, newSize * sizeof(char *));

    if (!*indexBuffer)
    {
        error = CreateError(ecCantAllocateMemory, "realloc of index buffer");
        return error;
    }

    (*indexBuffer)->size = newSize;
    return error;
}

void FreeIndexBuf(IndexBuffer *indexBuf)
{
    assert(indexBuf);
    assert(indexBuf->ptr);
    for (size_t i = 0; i < indexBuf->lineCount; ++i)
    {
        assert(indexBuf->ptr[i]);
        free(indexBuf->ptr[i]);
    }
    free(indexBuf->ptr);
    free(indexBuf);
    return;
}

char *ReadLine(char *buf, size_t bufSize, FILE *inputFile)
{
    assert(buf);
    memset(buf, 0, bufSize);
    return fgets(buf, (int)(bufSize - 1), inputFile);
}

void ParseTextBuffer(const char *const textBuf, IndexBuffer *indexBuf)
{
    assert(textBuf);
    assert(indexBuf);
    assert(indexBuf->ptr);

    const char *prevLinePos = textBuf;
    const char *nextLinePos = textBuf;

    while ((nextLinePos = strchr(prevLinePos, '\n')) != NULL)
    {
        CopyStringToBuffer(indexBuf, prevLinePos, nextLinePos);

        prevLinePos = nextLinePos + 1;
        // fprintf(stderr, "DEBUG: string after prevLinePos: <%s>", prevLinePos);
    }

    CopyStringToBuffer(indexBuf, prevLinePos, prevLinePos + strlen(prevLinePos));
}

Error CopyStringToBuffer(IndexBuffer *indexBuf, const char *const start, const char *const end)
{
    assert(indexBuf);
    assert(start);
    assert(end);

    Error error = CreateError(ecSuccess, "");

    size_t lineLength = (unsigned)(end - start) + 1;

    if (indexBuf->lineCount == indexBuf->size)
    {
        error = ExtendIndexBuffer(&indexBuf);
        if (error.exitCode != ecSuccess)
        {
            return error;
        }
    }

    indexBuf->ptr[indexBuf->lineCount] = (char *)calloc(lineLength + 1, sizeof(char));
    if (!indexBuf->ptr)
    {
        error = CreateError(ecCantAllocateMemory, "index buffer lines");
        return error;
    }

    // fprintf(stderr, "DEBUG: lineCount: %lu, nextLinePos: %ld\n", indexBuf->lineCount, nextLinePos - textBuf);
    assert(indexBuf->ptr[indexBuf->lineCount]);

    memcpy(indexBuf->ptr[indexBuf->lineCount], start, lineLength * sizeof(char));
    indexBuf->ptr[indexBuf->lineCount][lineLength - 1] = '\0';

    indexBuf->lineCount++;

    return error;
}
