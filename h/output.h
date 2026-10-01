#ifndef OUTPUT_H

#define OUTPUT_H

#include "errorHandle.h"
#include "types.h"
#include <cstdio>

void DumpIndexBuf(IndexBuffer *indexBuf);

void DumpStringExpanded(String_t *str, const char *name);

void DumpStringExpanded(const char *str, const char *name);

void DumpStringRaw(const char *str, const char *name);

#define DUMP_STRING_RAW(__str) DumpStringRaw((__str), #__str);

Error PrintTextToFile(IndexBuffer *indexBuf, FILE *outputFile);

#endif
