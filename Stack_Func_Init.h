#ifndef STACK_FUNC_INIT_H
#define STACK_FUNC_INIT_H

//typedef int stack_elem_t;

#define CANARY_LEFT 0xBEDA
#define CANARY_RIGHT 0xBAD
#define STRUCT_CHECK 0xBADEDA
#define MAX_START_SIZE 8
#define MAX_REGS 8

typedef struct
{
    stack_elem_t * deita;
    int size;
    int capacity;
    int check;
    /*int ax;
    int bx;
    int cx;
    int dx;*/
    int * Regs;
} VM;

void StackInit( VM * s );

void StackResizeUp( VM * s );

void StackResizeDown( VM * s );

void StackDestroy( VM * s);

bool StackOK( VM * s );

void StackDump( VM * s );

void StackPush( VM * s, stack_elem_t value);

stack_elem_t StackPop( VM * s);

#endif
