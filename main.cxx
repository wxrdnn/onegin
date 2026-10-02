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
    RETURN_EXITCODE_IF_FAIL(error);

    char *rawTextBuf = NULL;
    error = CreateTextBuf(fileSize + 1, &rawTextBuf);
    RETURN_EXITCODE_IF_FAIL(error);

    error = LoadText(inputFileDescriptor, rawTextBuf, fileSize);
    RETURN_EXITCODE_IF_FAIL(error);

    IndexBuffer *indexBuffer = NULL;
    error = CreateIndexBuffer(cStartIndexBufSize, &indexBuffer);
    RETURN_EXITCODE_IF_FAIL(error);

    assert(indexBuffer);
    assert(indexBuffer->ptr);

    ParseTextBuffer(rawTextBuf, fileSize, indexBuffer);
    // fprintf(stderr, "DEBUG: in main.cxx:64: indexBuf->lineCount = %lu\n", indexBuffer->lineCount);

    SortText(indexBuffer, launchOptions.sortingMode, csmFromStart); // TODO csm option choose
    // fprintf(stderr, "DEBUG: in main.cxx:66: indexBuf->lineCount = %lu\n", indexBuffer->lineCount);

    error = PrintTextToFile(indexBuffer, outputFile);
    RETURN_EXITCODE_IF_FAIL(error);

    FreeIndexBuf(indexBuffer);
    free(rawTextBuf);

    close(inputFileDescriptor);
    fclose(outputFile);
    return 0;
}
