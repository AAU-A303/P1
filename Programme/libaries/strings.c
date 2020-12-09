#include "strings.h"

void strings_append(Strings* strings, char* append) {
    int length = strlen(append);

    strings_increase_size(strings);

    strings->buffer[(strings->index-1)] = (char*)malloc((length) * sizeof(char*));
    strings->length[(strings->index-1)] = length;
    strings->buffer[(strings->index-1)] = append;
}

void strings_append_format(Strings* strings, const char* format, ...){
    int length;
    char* buffer;
    va_list args, argsc;
    
    va_start(args, format);
    va_start(argsc, format);

    length = vsnprintf(NULL, 0, format, argsc) + 2;
    buffer = calloc(length, sizeof(char));
    vsnprintf(buffer, length, format, args);

    va_end(argsc);
    va_end(args);
    
    strings_append(strings, buffer);
}

void strings_increase_size(Strings* strings){
    strings->index++;
    strings->length = realloc(strings->length, sizeof(int) * (strings->index));
    strings->buffer = realloc(strings->buffer, sizeof(char*) * (strings->index));
}