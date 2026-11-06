#include <TXlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Read_From_File.cpp"
#include "Commands.h"

#define MAX_TAGS 16
#define MAX_SIZE_COMMAND 16
#define MAX_SIZE_REG 8

#include "ASM_Func.cpp"

int main( int argc, char * argv[] )
{
    FILE * file_ptr = fopen( argv[1] , "w" );
    Massives * asl = StructInit( argv[2] );
    int Lebels[MAX_TAGS] = {};

    Collect_Tags( asl, Lebels );

    Convert_Commands( file_ptr, asl, Lebels);

    fclose( file_ptr );
    return 0;
}
