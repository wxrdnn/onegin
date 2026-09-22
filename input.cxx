#include "h/input.h"
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

int GetFileSize(const char *const path, size_t *size)
{
    struct stat buf = {};
    int error = stat(path, &buf);
    *size = (size_t)buf.st_size;
    return error;
}

int LoadText(const int fd, char *const textBuf, const size_t fileSize) // needs textBuf size of <fileSize + 1>
{
    long int numberRead = read(fd, textBuf, fileSize);
    if (numberRead != (long int)fileSize)
    {
        return -1;
    }

    textBuf[fileSize] = '\0';

    return 0;
}

char *CreateTextBuf(const size_t size)
{
    return (char *)calloc(size, sizeof(char));
}

IndexBuffer *CreateIndexBuffer(const size_t startSize)
{
    IndexBuffer *indexBuf = (IndexBuffer *)malloc(sizeof(IndexBuffer));

    indexBuf->size = startSize;
    indexBuf->lineCount = 0;
    indexBuf->ptr = (char **)calloc(startSize, sizeof(char *));

    return indexBuf;
}

IndexBuffer *ExtendIndexBuffer(IndexBuffer *indexBuffer)
{
    size_t newSize = indexBuffer->size * 2;
    indexBuffer->ptr = (char **)realloc(indexBuffer->ptr, newSize * sizeof(char *));
    indexBuffer->size = newSize;
    return indexBuffer;
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

void CopyStringToBuffer(IndexBuffer *const indexBuf, const char *const start, const char *const end)
{
    assert(indexBuf);
    assert(start);
    assert(end);

    size_t lineLength = (unsigned)(end - start) + 1;

    if (indexBuf->lineCount == indexBuf->size)
    {
        ExtendIndexBuffer(indexBuf);
    }

    indexBuf->ptr[indexBuf->lineCount] = (char *)calloc(lineLength + 1, sizeof(char));

    // fprintf(stderr, "DEBUG: lineCount: %lu, nextLinePos: %ld\n", indexBuf->lineCount, nextLinePos - textBuf);
    assert(indexBuf->ptr[indexBuf->lineCount]);

    memcpy(indexBuf->ptr[indexBuf->lineCount], start, lineLength * sizeof(char));
    indexBuf->ptr[indexBuf->lineCount][lineLength - 1] = '\0';

    indexBuf->lineCount++;
}
