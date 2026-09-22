#ifndef INPUT_H

#define INPUT_H

#include <cstdio>

struct IndexBuffer
{
    char **ptr;
    size_t size;
    size_t lineCount;
};

int LoadText(const int fd, char *const textBuf, const size_t fileSize);

char *CreateTextBuf(const size_t size);

IndexBuffer *CreateIndexBuffer(const size_t startSize);

IndexBuffer *ExtendIndexBuffer(IndexBuffer *indexBuffer);

char *ReadLine(char *buf, size_t bufSize, FILE *inputFile);

int GetFileSize(const char *const path, size_t *size);

void ParseTextBuffer(const char *const textBuf, IndexBuffer *indexBuf);

void CopyStringToBuffer(IndexBuffer *const indexBuf, const char *const start, const char *const end);

#endif
