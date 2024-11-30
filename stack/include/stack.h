#ifndef STACK_H
#define STACK_H

#include <stddef.h>

#define SIZEOF_STACK sizeof(struct stack)

typedef struct stack my_stack;

struct item
{
    void *data;
    struct item *next;
};

struct stack
{
    struct item *head;
    size_t size;
    size_t sizeof_data;
    int error;

    void (* free_func)(void *data);
    void (* print_func)(void *data);
};

// create and destroy stack
struct stack *init_stack(size_t sizeof_data);
void clear_stack(void *void_stack);
void free_stack(void *void_stack);

// update stack
int push_stack(struct stack *stack, void *data);
void *pop_stack(struct stack *stack, size_t sizeof_data);

// print data in stack
void print_stack(void *void_stack);

#endif /* ! STACK_H */
