#include "h/constants.h"
#include "h/input.h"
#include "h/output.h"
#include "h/sort.h"
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
const char *cInputFileName = "onegin";

int main()
{
    // FILE *inputFile = fopen(cInputFileName, "r");
    int inputFileDescriptor = open(cInputFileName, O_RDONLY);
    FILE *outputFile = fopen("sorted_onegin", "w");

    size_t fileSize = 0;
    int error = GetFileSize(cInputFileName, &fileSize);
    if (error)
    {
        return error;
    }

    char *textBuf = CreateTextBuf(fileSize + 1);

    error = LoadText(inputFileDescriptor, textBuf, fileSize);
    if (error)
    {
        return error;
    }

    IndexBuffer *indexBuffer = CreateIndexBuffer(cStartIndexBufSize);
    assert(indexBuffer);
    assert(indexBuffer->ptr);
    ParseTextBuffer(textBuf, indexBuffer);
    // printf("%d", CompareSrings("        const char *const s1", " const char *const s"));
    SortText(indexBuffer, soDescending);

    PrintTextToFile(indexBuffer, outputFile);

    FreeIndexBuf(indexBuffer);
    free(textBuf);

    close(inputFileDescriptor);
    fclose(outputFile);
    return 0;
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
