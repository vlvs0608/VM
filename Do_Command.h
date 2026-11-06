#ifndef DO_COMMAND_H
#define DO_COMMAND_H

#include "Commands.h"
#include "VM_functions_Init.h"

int Just_Do_This_Command( VM spu, VM adrs, Massives *asl);

int Just_Do_This_Command( VM spu, VM adrs, Massives *asl)
{
    int pc = 0;
    while( pc < asl->sumstrings)
    {
        int com;
        int arg;
        int len = sscanf( asl->index[pc], "%d %d", &com, &arg );

        if( len < 1 )
        {
            pc++;
            continue;
        }

        switch( com )
        {
            case COM_PUSH:
                StackPush( &spu, arg);
                break;

            case COM_ADD:
                ADD( &spu );
                break;

            case COM_SUB:
                SUB( &spu );
                break;

            case COM_DIV:
                DIV( &spu );
                break;

            case COM_OUT:
                OT( &spu );
                break;

            case COM_HLT:
                return 0;

            case COM_MUL:
                MUL( &spu );
                break;

            case COM_POP:
                spu.Regs[ arg - 1 ] = StackPop( &spu );
                break;

            case COM_PUSHR:
                StackPush( &spu, spu.Regs[ arg - 1 ] );
                break;

            case COM_JMP:
                pc = arg;
                continue;
                break;

            case COM_JA:
                if( JA( &spu ) )
                {
                    pc = arg;
                    continue;
                }
                break;

            case COM_CALL:
                StackPush( &adrs, pc + 1 );
                pc = arg;
                continue;
                break;

            case COM_RET:
                pc = StackPop( &adrs );
                continue;
                break;

            case COM_IN:
                In( &spu );
                break;

        }

        pc++;
    }
}

#endif
