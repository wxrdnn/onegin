#include "h/input.h"
#include "h/constants.h"
#include <cassert>
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
    *size = buf.st_size;
    return error;
}

char *LoadText(const int descriptor, char *const textBuf)
{
}

char *CreateTextBuf(const size_t size)
{
    return (char *)calloc(size, sizeof(char));
}

char *ReadLine(char *buf, size_t bufSize, FILE *inputFile)
{
    assert(buf);
    memset(buf, 0, bufSize);
    return fgets(buf, (int)(bufSize - 1), inputFile);
}
