#include "h/utils.h"
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

TextBuf *LoadText(FILE *inputFile, TextBuf *textBuf);
TextBuf CreateTextBuf(size_t startSize);
void DumpTextBuf(TextBuf *textBuf);
void FreeTextBuf(TextBuf *textBuf);
void DumpString(char *s);
void DumpTextToFile(TextBuf *textBuf, FILE *outputFile);

int main()
{
    FILE *inputFile = fopen("onegin", "r");
    FILE *outputFile = fopen("sorted_onegin", "w");
    TextBuf textBuf = CreateTextBuf(cStartTextBufSize);
    LoadText(inputFile, &textBuf);
    DumpTextToFile(&textBuf, outputFile);
    FreeTextBuf(&textBuf);

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

TextBuf *LoadText(FILE *inputFile, TextBuf *textBuf)
{
    char buf[cBufSize] = {};
    size_t lineIndex = 0;
    char *ptrToWrite = textBuf->lines[lineIndex].ptr;
    bool lastIteration = false;

    while (!lastIteration)
    {
        lastIteration = fread(buf, sizeof(char), cBufSize - 1, inputFile) != (cBufSize - 1);

        char *newLinePos = NULL;
        char *ptrToRead = buf;
        while ((newLinePos = strchr(ptrToRead, '\n')) != NULL)
        {
            assert(ptrToRead < (buf + sizeof(buf) / sizeof(buf[0])));

            if (textBuf->lineAmount == textBuf->bufSize)
            {
                size_t newBufSize = textBuf->bufSize * 2;
                textBuf->lines = (LineBuf *)realloc(textBuf->lines, newBufSize * (sizeof(LineBuf)));
                textBuf->bufSize = newBufSize;
            }

            size_t lineLength = (size_t)(newLinePos - ptrToRead + 1);

            textBuf->lines[lineIndex].ptr = (char *)calloc(lineLength + 1, sizeof(char));
            textBuf->lines[lineIndex].size = lineLength + 1;
            textBuf->lineAmount++;

            ptrToWrite = textBuf->lines[lineIndex].ptr;

            strncpy(ptrToWrite, ptrToRead, lineLength);
            ptrToWrite += lineLength;
            ptrToRead += lineLength;
            lineIndex++;
        }

        lineIndex--;
        size_t lineTailLength = strlen(ptrToRead) + 1;
        size_t ptrToWriteOffset = (size_t)(ptrToWrite - textBuf->lines[lineIndex].ptr);
        textBuf->lines[lineIndex].ptr =
            (char *)realloc(textBuf->lines[lineIndex].ptr, textBuf->lines[lineIndex].size + lineTailLength);
        ptrToWrite = textBuf->lines[lineIndex].ptr + ptrToWriteOffset;
        strncpy(ptrToWrite, ptrToRead, lineTailLength);
    }

    return textBuf;
}

TextBuf CreateTextBuf(size_t startSize)
{
    TextBuf textBuf = {};
    textBuf.lines = (LineBuf *)malloc(sizeof(LineBuf) * startSize);
    textBuf.bufSize = startSize;
    textBuf.lineAmount = 0;
    return textBuf;
}

void DumpTextBuf(TextBuf *textBuf)
{
    for (size_t i = 0; i < textBuf->lineAmount; ++i)
    {
        // DumpString(textBuf->lines[i].ptr);
        char *line = strdup(textBuf->lines[i].ptr);
        ReplaceNewLineCharWithNullTerminator(line);
        fprintf(stderr, "DEBUG: Line %lu: <%s> size of %lu.\n", i, line, textBuf->lines[i].size);
        free(line);
    }
    return;
}

void FreeTextBuf(TextBuf *textBuf)
{
    for (size_t i = 0; i < textBuf->lineAmount; ++i)
    {
        free(textBuf->lines[i].ptr);
    }
    free(textBuf->lines);
    return;
}

void DumpString(char *s)
{
    size_t len = strlen(s);
    fprintf(stderr, "DEBUG: Begin string dump:");
    for (size_t i = 0; i < len; ++i)
    {
        fprintf(stderr, "DEBUG: <\'%c\' = %d>\n", s[i], s[i]);
    }
    fprintf(stderr, "DEBUG: End string dump.\n");
    return;
}
void DumpTextToFile(TextBuf *textBuf, FILE *outputFile)
{
    for (size_t i = 0; i < textBuf->lineAmount; ++i)
    {
        fprintf(stderr, "DEBUG: i: %lu, lineAmount: %lu.\n", i, textBuf->lineAmount);
        assert(textBuf->lines[i].ptr != NULL);
        fprintf(outputFile, "%s", textBuf->lines[i].ptr);
    }
    return;
}
