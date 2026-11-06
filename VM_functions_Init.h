#ifndef VM_FUNCTIONS_INIT_H
#define VM_FUNCTIONS_INIT_H

#include "Stack_Func_Init.h"

#include <stdbool.h>

void ADD( VM* s );

void SUB( VM * s );

void DIV( VM * s );

void MUL( VM * s );

void JMP( VM * s );

void OT( VM * s );

int HLT( void );

bool JA( VM * s );

void In( VM* s );

#endif
