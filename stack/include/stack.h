#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef void (*func_free)(void *data);
typedef void (*func_print)(void *data);

struct item
{
    void *data;
    struct item *next;
};

struct stack
{
    struct item *head;
    size_t size;
    int error;
    size_t sizeof_data;
};

// create and destroy stack
struct stack *init_stack(size_t sizeof_data);
void clear_stack(struct stack* stack, func_free data_free);
void free_stack(struct stack* stack, func_free data_free);

// update stack
int insert_stack(struct stack *stack, void *data, size_t sizeof_data);
struct item *pop_stack(struct stack *stack, size_t sizeof_data);

// check status of stack

// print data in stack
void print_stack(struct stack *stack, func_print data_print);

#endif /* ! STACK_H */
