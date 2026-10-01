#include "h/string.h"
#include "h/types.h"
#include <cassert>
#include <cstdlib>
#include <stdlib.h>

String_t *CreateString(const char *const s, size_t size)
{
    String_t *str = (String_t *)calloc(1, sizeof(String_t));
    str->data = s;
    str->length = size;
    return str;
}

void DestroyString(String_t *const str)
{
    assert(str);
    assert(str->data);

    free((char *)str->data);
    free(str);
    return;
}
