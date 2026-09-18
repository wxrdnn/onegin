#ifndef MAIN_H

#define MAIN_H

#include <stddef.h>
#include <stdio.h>

const size_t cBufSize = 1024; // TODO handle buffers that dont have \n
const size_t cMaxLine = 1024;
const size_t cStartTextBufSize = 1024;

struct LineBuf
{
    char *ptr;
    size_t size;
};

struct TextBuf
{
    LineBuf *lines;
    size_t bufSize;
    size_t lineAmount;
};

enum SortingOptions
{
    soAscending = 0,
    soDescending = 1,
};

TextBuf *LoadText(FILE *inputFile, TextBuf *textBuf);

TextBuf CreateTextBuf(size_t startSize);

void DumpTextBuf(TextBuf *textBuf);

void FreeTextBuf(TextBuf *textBuf);

void DumpString(char *s);

void PrintTextToFile(TextBuf *textBuf, FILE *outputFile);

char *ReadLine(char *buf, size_t bufSize, FILE *inputFile);

TextBuf *ExtendTextBuffer(TextBuf *textBuf);

void SortText(TextBuf *textBuf, SortingOptions sortingOption);

int CompareLineBufsAscending(const void *p1, const void *p2);

int CompareLineBufsDescending(const void *p1, const void *p2);

#endif
