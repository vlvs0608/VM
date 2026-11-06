#include "ASM_Func_Init.h"
#include "Commands.h"

void Collect_Tags( Massives * strc, int * tags )
{
    for( int i = 0; i < strc->sumstrings; i++)
    {
        int n;
        if( sscanf( strc->index[i], ":%d", &n ) == 1 )
            if( n < MAX_TAGS )
                tags[n] = i;
    }
}

void Convert_Commands( FILE * file_ptr, Massives * strc, int * Lebels )
{
    for( int i = 0; i < strc->sumstrings; i++)
    {
        char com[MAX_SIZE_COMMAND] = {0};
        char reg[MAX_SIZE_REG] = {0};

        sscanf( strc->index[i], "%s", com);
        if( !strcmp( com, "PUSH" ) )
        {
            fprintf(file_ptr, "%d ", COM_PUSH);
            int n = 0;
            sscanf( strc->index[i], "%s %d", com, &n );
            fprintf(file_ptr, "%d \n", n );
        }

        else if( !strcmp( com, "ADD") )
            fprintf(file_ptr, "%d \n", COM_ADD);

        else if( !strcmp( com, "SUB") )
            fprintf(file_ptr, "%d \n", COM_SUB);

        else if( !strcmp( com, "DIV") )
            fprintf(file_ptr, "%d \n", COM_DIV);

        else if( !strcmp( com, "OUT") )
            fprintf(file_ptr, "%d \n", COM_OUT);

        else if( !strcmp( com, "HLT") )
            fprintf(file_ptr, "%d \n", COM_HLT);

        else if( !strcmp( com, "MUL") )
            fprintf(file_ptr, "%d \n", COM_MUL);

        else if( !strcmp( com, "POP") )
        {
            fprintf(file_ptr, "%d ", COM_POP);

            sscanf( strc->index[i], "%s %s", com,  reg );

            Choice_Reg( reg, file_ptr );

        }

        else if( !strcmp( com, "PUSHR") )
        {
            fprintf(file_ptr, "%d ", COM_PUSHR);

            sscanf( strc->index[i], "%s %s", com, reg ) ;

            Choice_Reg( reg, file_ptr );

        }

        else if( !strcmp( com, "JMP") )
        {
            fprintf(file_ptr, "%d ", COM_JMP);
            Choice_Tag( com, strc, file_ptr, Lebels, i );
        }

        else if( !strcmp( com, "JA" ) )
        {
            fprintf(file_ptr, "%d ", COM_JA);
            Choice_Tag( com, strc, file_ptr, Lebels, i );
        }

        else if( !strcmp( com, "CALL" ) )
        {
            fprintf(file_ptr, "%d ", COM_CALL );
            Choice_Tag( com, strc, file_ptr, Lebels, i );
        }

        else if( !strcmp( com, "RET" ) )
            fprintf(file_ptr, "%d \n", COM_RET );

        else if( !strcmp( com, "IN" ) )
            fprintf( file_ptr, "%d \n", COM_IN );

        else
            fprintf(file_ptr, " \n" );
    }
}

void Choice_Reg( char * reg, FILE * file_ptr )
{
    if( !strcmp( reg, "AX") )
        fprintf(file_ptr, "1 \n");

    else if( !strcmp( reg, "BX") )
        fprintf(file_ptr, "2 \n");

    else if( !strcmp( reg, "CX") )
        fprintf(file_ptr, "3 \n");

    else
        fprintf( file_ptr, "4 \n");
}

void Choice_Tag( char * com, Massives * strc, FILE * file_ptr, int * Lebels, int i )
{
    int n = 0;
    sscanf( strc->index[i], "%s :%d", com, &n );
    fprintf(file_ptr, "%d \n", Lebels[n] );
}
