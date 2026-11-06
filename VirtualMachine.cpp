typedef int stack_elem_t;
#include <TXlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STACK_DUMP( stk ) do { \
    fprintf( stderr, "STACKDUMP: %s  %d   <%s>\n", __FILE__, __LINE__, __func__); \
    StackDump( stk );\
} while(0)

#include "Stack_Func.cpp"
#include "VM_functions.cpp"
#include "Read_From_File.cpp"
#include "Commands.h"
#include "Do_Command.h"

int main( int argc, char* argv[] )
{
    VM spu = {};
    StackInit( &spu );
    VM adrs = {};
    StackInit( &adrs );
    Massives * asl = StructInit( argv[1] );

    return Just_Do_This_Command( spu, adrs, asl );
}
