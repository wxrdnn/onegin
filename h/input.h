#ifndef INPUT_H

#define INPUT_H

#include "errorHandle.h"
#include "sort.h"
#include <cstddef>
#include <cstdio>

Error GetFileSize(const char *const path, size_t *size);

Error LoadText(const int fd, char *const textBuf, const size_t fileSize); // needs textBuf size of <fileSize + 1>

Error CreateTextBuf(const size_t size, char **textBuf);

Error CreateIndexBuffer(const size_t startSize, IndexBuffer **indexBuffer);

Error ExtendIndexBuffer(IndexBuffer **indexBuffer);

void FreeIndexBuf(IndexBuffer *indexBuf);

char *ReadLine(char *buf, size_t bufSize, FILE *inputFile);

void ParseTextBuffer(const char *const textBuf, const size_t textBufSize, IndexBuffer *indexBuf);

Error WriteStringToBuffer(IndexBuffer *indexBuf, const char *const start, const char *const end);

#endif
