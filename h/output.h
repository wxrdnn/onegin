#ifndef OUTPUT_H

#define OUTPUT_H

#include "input.h"
#include <cstdio>

void DumpIndexBuf(IndexBuffer *indexBuf);

void FreeIndexBuf(IndexBuffer *indexBuf);

void DumpString(char *s);

void PrintTextToFile(IndexBuffer *indexBuf, FILE *outputFile);

#endif
