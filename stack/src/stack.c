#include "stack.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static typedef void (*func_free)(void *data);
static typedef void (*func_print)(void *data);

/*
 * Create and destroy stack
 */
// Init and empty satck
struct stack *init_stack(size_t sizeof_data, free_func free_func,
                         print_func print_func)
{
    struct stack *new_stack = malloc(sizeof(struct stack));

    new_stack->head = NULL;
    new_stack->size = 0;
    new_stack->error = 0;
    new_stack->sizeof_data = sizeof_data;

    new_stack->free_func = free_func;
    new_stack->print_func = print_func;

    return new_stack;
}

// Free stack items, stack is not free and stell usable
static void rec_clear_stack(struct item *item, free_func free_func)
{
    if (item == NULL)
        return;

    rec_clear_stack(item->next, data_free);
    data_free(item->data);
    free(item);
}

void clear_stack(void *void_stack)
{
    struct stack *cast_stack = void_stack;

    // Only use if data need to be free
    if (cast_stack->free_func != NULL)
        rec_clear_stack(cast_stack->head, cast_stack->free_func);

    // Reset stack value
    stack->head = NULL;
    stack->size = 0;
    stack->error = 0;
}

// free stack items and satck it self, stack is unusable
void free_stack(void *void_stack)
{
    struct stack *cast_stack = void_stack;

    // clear items in stack
    clear_stack(void_stack, cast_stack->free_func);

    // free stack
    free(cast_stack);
}

/*
 * Update stack
 */
// insert new item at head with data data, return 1 succed otherwise 0
int push_stack(struct stack *stack, void *data)
{
    if (stack == NULL)
        return 0;

    struct item *new_item = malloc(sizeof(struct item));
    if (new_item == NULL)
        return 0;

    new_item->data = data;
    new_item->next = stack->head;
    stack->head = new_item;
    stack->size += 1;

    return 1;
}

// pop first element, return NULL if stack is empty otherwise first item
void *pop_stack(struct stack *stack)
{
    if (stack == NULL)
        return NULL;

    struct item *tmp = stack->head;
    stack->head = stack->head->next;
    stack->size -= 1;

    void *data = tmp->data;
    free(tmp);

    return data;
}

/*
 * Print data in stack
 */
// print stack with line break at end
static void rec_print_stack(struct item *item, print_func print_func)
{
    if (item == NULL)
        return;

    rec_print_stack(item->next, print_func);
    print_func(item->data);
    printf(" -> ");
}

void print_stack(void *void_stack)
{
    if (void_stack == NULL)
        return;

    struct stack *cast_stack = void_stack;
    if (stack->size == 0)
        printf("stack is empty\n");
    else
    {
        if (cast_stack->print_func == NULL)
        {
            printf("no function were given to print data in stack\n");
            return;
        }
        rec_print_stack(cast_stack->head->next, cast_stack->print_func);
        cast_stack->print_func(stack->head->data);
        printf("(head)\n");
    }
}
