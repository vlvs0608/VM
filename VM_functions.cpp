#include "VM_functions_Init.h"
#include <stdio.h>

void ADD( VM * stk )
{
    stack_elem_t b = StackPop( stk );
    stack_elem_t a = StackPop( stk );
    StackPush( stk, a+b);
}

void SUB( VM * stk )
{
    stack_elem_t b = StackPop( stk );
    stack_elem_t a = StackPop( stk );
    StackPush( stk, a-b );
}

void DIV( VM * stk )
{
    stack_elem_t b = StackPop( stk );
    stack_elem_t a = StackPop( stk );
    StackPush( stk, a/b );
}

void MUL( VM * stk )
{
    stack_elem_t a = StackPop( stk );
    stack_elem_t b = StackPop( stk );
    StackPush( stk, a*b );
}

void OT( VM * s )
{
    printf( "<<<%d>>>\n", StackPop( s ) );
}

int HLT( void )
{
    return 0;
}

bool JA( VM * s )
{
    stack_elem_t a = StackPop( s );
    stack_elem_t b = StackPop( s );
    return a < b;
}

void In( VM * s )
{
    int n = 0;
    scanf( "%d", &n );
    StackPush( s, n );
}
