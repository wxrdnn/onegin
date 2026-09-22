#ifndef OUTPUT_H

#define OUTPUT_H

#include "errorHandle.h"
#include "types.h"
#include <cstdio>

void DumpIndexBuf(IndexBuffer *indexBuf);

void DumpString(char *s);

Error PrintTextToFile(IndexBuffer *indexBuf, FILE *outputFile);

#endif
