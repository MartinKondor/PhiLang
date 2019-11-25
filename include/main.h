#ifndef _MAIN_H_INCLUDED_
#define _MAIN_H_INCLUDED_

typedef unsigned int bool;

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

void Phi_execToken(char* token);
void Phi_eval(char* code);

#endif
