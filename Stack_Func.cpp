#include "Stack_Func_Init.h"
#include <stdio.h>
#include <TXlib.h>
#include <stdlib.h>

void StackInit( VM * s )
{
    int cap = MAX_START_SIZE;

    s->deita = ( stack_elem_t *)calloc( cap + 2, sizeof(stack_elem_t));

    s->deita[0] = CANARY_LEFT;

    s->deita[cap + 1] = CANARY_RIGHT;// malloc realloc

    s->Regs = ( int * )calloc( MAX_REGS , sizeof( int ) );

    s->size = 0 ;

    s->capacity = cap;

    s->check = STRUCT_CHECK;

    if( !StackOK(s) )
    {
        fprintf( stderr, "Ошибка инициализации стека");
        abort();
    }
}

void StackDestroy( VM * s)
{
    free( s->deita );
}

bool StackOK( VM * s )
{
    if (s == NULL)
    {
        fprintf(stderr, "Обнаружен нулевой указатель на структуру стека\n");
        return false;
    }
    if( s->deita == NULL )
    {
        fprintf( stderr, "Обнаружен нулевой указатель на структуру");
        STACK_DUMP(s);
        return  false;
    }
    if( s->size > s->capacity )
    {
        fprintf( stderr, "size > capacity ");
        STACK_DUMP(s);
        return false;
    }
    if( s->size < 0 )
    {
        fprintf( stderr, "Отрицательный size");
        STACK_DUMP(s);
        return false;
    }
    if( s->capacity <= 0 )
    {
        fprintf( stderr,"Отрицательный capacity");
        STACK_DUMP(s);
        return false;
    }
    if( s->deita[0] != CANARY_LEFT )
    {
        fprintf( stderr, "Ошибка левой канарейки");
        STACK_DUMP(s);
        return false;
    }
    if( s->deita[1 + s->capacity] != CANARY_RIGHT )
    {
        fprintf( stderr, "Ошибка правой канарейки");
        STACK_DUMP(s);
        return false;
    }
    if( s->check != STRUCT_CHECK )
    {
        fprintf( stderr, "Перезапись значений в структуре" );
        STACK_DUMP(s);
        return false;
    }
    return true;

}

void StackDump( VM * stk )
{
    fprintf( stderr, "STACKDUMP: \n");

    if( stk == NULL )
    {
        fprintf( stderr, "Обращение к нулевому указателю" );

    }

    fprintf( stderr, "Адрес структуры: %p \n", stk);
    fprintf( stderr, "size: %d \n", stk->size);
    fprintf( stderr, "capacity: %d \n", stk->capacity);
    fprintf( stderr, "Адрес стека: %p \n", stk->deita);
    for( int i = 1; i <= stk->capacity; i++ )
    {
        if( i <= stk->size )
            fprintf( stderr, "*[%d] = %d\n", i, stk->deita[i] );
        else
            fprintf( stderr, "*[%d] = 666.666\n", i);
    }

}

void StackPush( VM * s, stack_elem_t value)
{
    if( !StackOK( s ) )
    {
        STACK_DUMP( s );
        return;
    }
    if ( s->size == s->capacity)
        StackResizeUp( s );
    s->deita[1 + s->size++] = value;
}

stack_elem_t StackPop( VM * s)
{
    if( !StackOK( s ) || s->size == 0 )
    {
        fprintf( stderr, "POP при нулевом size\n");
        STACK_DUMP( s );
        return 666.666;
    }

    if( s->capacity >= 4*( s->size) )
        StackResizeDown( s );
    stack_elem_t a = s->deita[1 + (--s->size)];
    return a;
}

void StackResizeUp( VM * s )
{
    stack_elem_t * temp = ( stack_elem_t * )realloc( s->deita, sizeof(stack_elem_t)*((s->capacity)*2 + 2) );

    if ( !temp )
    {
        fprintf( stderr, "Ошибка увеличения размера стека");
        STACK_DUMP( s );
        free(s->deita);
        return;
    }

    s->deita = temp;

    s->capacity = (s->capacity)*2;

    s->deita[s->capacity + 1] = CANARY_RIGHT;
}

void StackResizeDown( VM * s )
{
    stack_elem_t * tempstk = ( stack_elem_t * )realloc( s->deita, sizeof( double )*(( s->capacity )/2 + 2));
    if ( tempstk == NULL )
    {
        fprintf( stderr, "Ошибка при уменьшении размера стека");
        STACK_DUMP( s );
        return;
    }

    s->deita = tempstk;

    s->capacity = ( s->capacity ) / 2;

    s->deita[1 + s->capacity] = CANARY_RIGHT;
}
