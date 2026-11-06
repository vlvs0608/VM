#ifndef ASM_FUNC_INIT_H
#define ASM_FUNC_INIT_H

void Collect_Tags( Massives * strc, int * tags );
void Convert_Commands( FILE * file_ptr, Massives * strc, int * Lebels );
void Choice_Reg( char * reg, FILE * file_ptr );
void Choice_Tag( char * com, Massives * strc, FILE * file_ptr, int * Lebels, int i );

#endif
