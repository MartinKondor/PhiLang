#ifndef _STACK_H_INCLUDED_
#define _STACK_H_INCLUDED_

typedef struct
{
    /**
     * Stores variables and function for a given scope.
     */
    unsigned int id;
    // variables: list = []  # list[PhiVariable]
    // functions: list = []  # list[PhiFunction]
} PhiStack;

void PhiStack_init(unsigned int id);

#endif
