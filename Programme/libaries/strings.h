#ifndef STRINGS_H
#define STRINGS_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdarg.h>

    typedef struct _Strings{
        int *length;
        int index;
        char **buffer;
    } Strings;
    
    void strings_append_format(Strings* strings, const char* format, ...);
    void strings_append(Strings* strings, char* append);
    void strings_increase_size(Strings* strings);
    void strings_copy(Strings* strings, int index, char* source);
    void free_strings(Strings* strings);
#endif /* STRINGS_H */
