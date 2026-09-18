#ifndef INPUT_H

#define INPUT_H

#include <cstdio>
enum SortingOptions
{
    soAscending = 0,
    soDescending = 1,
};

char *LoadText(const int descriptor, char *const textBuf);

char *CreateTextBuf(const size_t size);

TextBuf *ExtendTextBuffer(TextBuf *textBuf);

char *ReadLine(char *buf, size_t bufSize, FILE *inputFile);

int GetFileSize(const char *const path, size_t *size);

#endif
