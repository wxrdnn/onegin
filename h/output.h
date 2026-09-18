#ifndef OUTPUT_H

#define OUTPUT_H

#include <cstdio>
void DumpTextBuf(TextBuf *textBuf);

void FreeTextBuf(TextBuf *textBuf);

void DumpString(char *s);

void PrintTextToFile(TextBuf *textBuf, FILE *outputFile);

#endif
