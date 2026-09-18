#include "h/constants.h"
#include "h/input.h"
#include "h/output.h"
#include "h/sort.h"
#include "h/utils.h"
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
const char *cInputFileName = "onegin";

int main(int argc, char *argv[])
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

    char *textBuf = CreateTextBuf(fileSize);

    LoadText(inputFile, &textBuf);
    SortText(&textBuf, soDescending);

    PrintTextToFile(&textBuf, outputFile);
    FreeTextBuf(&textBuf);

    fclose(inputFile);
    fclose(outputFile);
    return 0;
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

TextBuf *ExtendTextBuffer(TextBuf *textBuf)
{
    size_t newSize = textBuf->bufSize * 2;
    textBuf->lines = (LineBuf *)realloc(textBuf->lines, newSize * sizeof(LineBuf));
    textBuf->bufSize = newSize;
    return textBuf;
}

void SortText(TextBuf *textBuf, SortingOptions sortingOption)
{
    int (*comp)(const void *, const void *);

    switch (sortingOption)
    {
    default:
    case soAscending:
        comp = CompareLineBufsAscending;
        break;

    case soDescending:
        comp = CompareLineBufsDescending;
        break;
    }

    qsort(textBuf->lines, textBuf->lineAmount, sizeof(LineBuf), comp);
    return;
}

int CompareLineBufsAscending(const void *p1, const void *p2)
{
    const LineBuf *lb1 = (const LineBuf *)p1;
    const LineBuf *lb2 = (const LineBuf *)p2;
    return strcmp(lb1->ptr, lb2->ptr);
}

int CompareLineBufsDescending(const void *p1, const void *p2)
{
    const LineBuf *lb1 = (const LineBuf *)p1;
    const LineBuf *lb2 = (const LineBuf *)p2;
    return -strcmp(lb1->ptr, lb2->ptr);
}
