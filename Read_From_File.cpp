#include "Read_From_File_Init.h"
#include <stdio.h>
#include <sys/stat.h>

size_t SizeOfFile( char * file)
{
    struct stat st = {};
    stat( file , &st);
    size_t length = st.st_size;
    return length;
}

FILE * FileOpen( char * filename)
{
    if( filename == NULL)
    {
        printf("Ошибка чтения файла название");
        return NULL;
    }
    FILE * file_ptr = fopen( filename , "rb");

    if( file_ptr == NULL)
    {
        printf("Ошибка чтения файла указатель");
        return NULL;
    }

    return file_ptr;
}

char * CreateBuffer ( char * file)
{
    FILE * file_ptr = FileOpen(file);
    const size_t length = SizeOfFile(file);
    char * Buffer = ( char *)calloc( length, sizeof(char));
    if( Buffer == NULL)
    {
        printf("Ошибка cоздания буффера");
        return NULL;
    }
    fread( Buffer, sizeof(char) , length, file_ptr);
    Buffer[length] = '\0';
    ReplaceSymbols( Buffer, length );
    fclose(file_ptr);
    return Buffer;
}

Massives * StructInit( char * file )
{
    Massives * st = (Massives *) calloc(1, sizeof(Massives));
    if (!st)
    {
        fprintf( stderr, "Ошибка создания структуры");
        return NULL;
    }
    st->buffer = CreateBuffer( file );
    st->sizeofbuf = SizeOfFile( file );
    st->sumstrings = CountingStrings(st->buffer, st->sizeofbuf);

    st->index = ( char * * )calloc( st->sumstrings, sizeof(char *));

    if (st->index == NULL)
    {
        fprintf( stderr, "Ошибка создания массива указателей");
        return NULL;
    }

    st->index[0] = &st->buffer[0];

    CollectMassive( st );

    return st;
}

int CountingStrings( char *strings, size_t length)
{
    int count = 0;
    for( int i = 1; i <= length; i++)
        if ( strings[i - 1] == '\0' && strings[i] != '\0')
            count++;
    return count + 1;
}

void ReplaceSymbols( char * buf, size_t length)
{
    for( int i = 0; i <= length; i++)
    {
        if( buf[i] == '\n')
            buf[i] = '\0';
        else if( buf[i] == '\r')
            buf[i] = '\0';
    }
}

void CollectMassive( Massives * st)
{
    for( int i = 1, j = 1; i < st->sizeofbuf && j < st->sumstrings; i++)
        if(st->buffer[i] == '\0' && st->buffer[i + 1] != '\0')
        {
            st->index[j++] = &st->buffer[i + 1];
        }
}

