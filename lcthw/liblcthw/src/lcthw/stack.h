#ifndef lcthw_stack_h
#define lcthw_stack_h

#include "list.h"

typedef struct Stack {
    List *list;
} Stack;

Stack *Stack_create();
void Stack_destroy(Stack *stack);
void Stack_push(Stack *stack, void *value);
void *Stack_peek(Stack *stack);
void *Stack_pop(Stack *stack);
int Stack_count(Stack *stack);

#define STACK_FOREACH(stack, cur) \
    LIST_FOREACH(stack->list, first, next, cur)

#endif

