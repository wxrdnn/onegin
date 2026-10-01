#ifndef STRING_H

#define STRING_H

#include "types.h"

String_t *CreateString(const char *const s, size_t size);

void DestroyString(String_t *const str);

#endif
