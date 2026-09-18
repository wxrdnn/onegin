#include "h/utils.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void PrintTextToFile(TextBuf *textBuf, FILE *outputFile);
char *ReadLine(char *buf, size_t bufSize, FILE *inputFile);
TextBuf *ExtendTextBuffer(TextBuf *textBuf);

int main()
{
    FILE *inputFile = fopen("onegin", "r");
    FILE *outputFile = fopen("sorted_onegin", "w");
    TextBuf textBuf = CreateTextBuf(cStartTextBufSize);
    LoadText(inputFile, &textBuf);
    PrintTextToFile(&textBuf, outputFile);
    FreeTextBuf(&textBuf);

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

TextBuf *LoadText(FILE *inputFile, TextBuf *textBuf)
{
    char buf[cBufSize] = {};

    while (ReadLine(buf, cBufSize, inputFile) != NULL)
    {
        buf[cBufSize - 1] = '\0';
        if (textBuf->lineAmount == textBuf->bufSize - 1)
        {
            ExtendTextBuffer(textBuf);
        }

        size_t index = textBuf->lineAmount;
        size_t lineLength = strlen(buf);

        textBuf->lines[index].ptr = (char *)calloc(lineLength + 1, sizeof(char));
        textBuf->lines[index].size = lineLength + 1;
        strncpy(textBuf->lines[index].ptr, buf, lineLength);

        // DumpString(buf);
        ++textBuf->lineAmount;
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
    assert(textBuf);
    assert(textBuf->lines);
    for (size_t i = 0; i < textBuf->lineAmount; ++i)
    {
        assert(textBuf->lines[i].ptr);
        free(textBuf->lines[i].ptr);
    }
    free(textBuf->lines);
    return;
}

void DumpString(char *s)
{
    assert(s);

    size_t len = strlen(s);
    fprintf(stderr, "DEBUG: Begin string dump:");
    for (size_t i = 0; i < len; ++i)
    {
        fprintf(stderr, "DEBUG: <\'%c\' = %d>\n", s[i], s[i]);
    }
    fprintf(stderr, "DEBUG: End string dump.\n");
    return;
}
void PrintTextToFile(TextBuf *textBuf, FILE *outputFile)
{
    for (size_t i = 0; i < textBuf->lineAmount; ++i)
    {
        // fprintf(stderr, "DEBUG: i: %lu, lineAmount: %lu.\n", i, textBuf->lineAmount);
        assert(textBuf->lines[i].ptr != NULL);
        // DumpString(textBuf->lines[i].ptr);
        fprintf(outputFile, "%s", textBuf->lines[i].ptr);
    }
    return;
}

char *ReadLine(char *buf, size_t bufSize, FILE *inputFile)
{
    assert(buf);
    memset(buf, 0, bufSize);
    return fgets(buf, (int)(bufSize - 1), inputFile);
}

TextBuf *ExtendTextBuffer(TextBuf *textBuf)
{
    size_t newSize = textBuf->bufSize * 2;
    textBuf->lines = (LineBuf *)realloc(textBuf->lines, newSize * sizeof(LineBuf));
    textBuf->bufSize = newSize;
    return textBuf;
}
