#ifndef READ_FROM_FILE_INIT_H
#define READ_FROM_FILE_INIT_H

typedef struct
{
    char * buffer;
    char ** index;
    size_t sizeofbuf;
    int sumstrings;
} Massives;

Massives * StructInit( char * file );

FILE * FileOpen( char * file);

char * CreateBuffer ( char * file);

size_t SizeOfFile( char * file);

int CountingStrings( char *strings, size_t length);

void ReplaceSymbols( char * strings, size_t length);

void CollectMassive( Massives * st);

#endif
