#include "h/constants.h"
#include "h/errorHandle.h"
#include "h/input.h"
#include "h/interface.h"
#include "h/output.h"
#include "h/sort.h"
#include "h/types.h"
#include <assert.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // TODO Sort by line ends

    Error error = CreateError(ecSuccess, "");

    LaunchOptions launchOptions = {};
    int parseLaunchOptionsResult = ParseLaunchOptions(argc, argv, &launchOptions);
    if (parseLaunchOptionsResult < 0)
    {
        error = CreateError(ecWrongUsage, argv[0]);
        return HandleError(error).exitCode;
    }

    int inputFileDescriptor = open(launchOptions.inputFileName, O_RDONLY);
    if (inputFileDescriptor < 0)
    {
        error = CreateError(TranslateErrnoCode(errno), launchOptions.inputFileName);
        return HandleError(error).exitCode;
    }

    FILE *outputFile = fopen(launchOptions.outputFileName, "w");
    if (!outputFile)
    {
        error = CreateError(TranslateErrnoCode(errno), launchOptions.outputFileName);
        return HandleError(error).exitCode;
    }

    size_t fileSize = 0;
    error = GetFileSize(launchOptions.inputFileName, &fileSize);
    if (error.exitCode != ecSuccess)
    {
        return HandleError(error).exitCode;
    }

    char *rawTextBuf = NULL;
    error = CreateTextBuf(fileSize + 1, &rawTextBuf);
    if (error.exitCode != ecSuccess)
    {
        return HandleError(error).exitCode;
    }

    error = LoadText(inputFileDescriptor, rawTextBuf, fileSize);
    if (error.exitCode != ecSuccess)
    {
        return HandleError(error).exitCode;
    }

    IndexBuffer *indexBuffer = NULL;
    error = CreateIndexBuffer(cStartIndexBufSize, &indexBuffer);
    if (error.exitCode != ecSuccess)
    {
        return HandleError(error).exitCode;
    }

    assert(indexBuffer);
    assert(indexBuffer->ptr);

    ParseTextBuffer(rawTextBuf, indexBuffer);
    // printf("%d", CompareSrings("        const char *const s1", " const char *const s"));
    SortText(indexBuffer, launchOptions.sortingMode, csmFromEnd); // TODO csm option choose

    error = PrintTextToFile(indexBuffer, outputFile);
    if (error.exitCode != ecSuccess)
    {
        return HandleError(error).exitCode;
    }

    FreeIndexBuf(indexBuffer);
    free(rawTextBuf);

    close(inputFileDescriptor);
    fclose(outputFile);
    return 0;
}
