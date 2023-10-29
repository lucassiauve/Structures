#include "stack.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Init and empty satck
struct stack *init_stack(size_t sizeof_data)
{
    struct stack *new_stack = malloc(sizeof(struct stack));

    new_stack->head = NULL;
    new_stack->size = 0;
    new_stack->error = 0;
    new_stack->sizeof_data = sizeof_data;

    return new_stack;
}

// Free stack items, stack is not free and stell usable
static void rec_clear_stack(struct item *item, func_free data_free)
{
    if (item == NULL)
        return;

    rec_clear_stack(item->next, data_free);
    data_free(item->data);
    free(item);
}

void clear_stack(struct stack* stack, func_free data_free)
{
    rec_clear_stack(stack->head, data_free);
    stack->head = NULL;
    stack->size = 0;
    stack->error = 0;
}

// free stack items and satck it self, stack is unusable
void free_stack(struct stack* stack, func_free data_free)
{
    clear_stack(stack, data_free);
    free(stack);
}

// insert new item at head with data data, return 1 succed otherwise 0
int insert_stack(struct stack *stack, void *data, size_t sizeof_data)
{
    if (stack == NULL || sizeof_data != stack->sizeof_data)
        return 0;

    struct item *new_item = malloc(sizeof(struct item));
    new_item->data = data;
    new_item->next = stack->head;
    stack->head = new_item;
    stack->size += 1;

    return 1;
}

// pop first element, return NULL if stack is empty otherwise first item
struct item *pop_stack(struct stack *stack, size_t sizeof_data)
{
    if (stack == NULL || sizeof_data != stack->sizeof_data || !stack->size)
        return NULL;

    struct item *tmp = stack->head;
    stack->head = stack->head->next;
    stack->size -= 1;

    return  tmp;
}

// print stack with line break at end
static void rec_print_stack(struct item *item, func_print data_print)
{
    if (item == NULL)
        return;

    rec_print_stack(item->next, data_print);
    data_print(item->data);
    printf(" -> ");
}

void print_stack(struct stack *stack, func_print data_print)
{
    if (stack->size == 0)
    {
        printf("stack is empty\n");
    }
    else
    {
        rec_print_stack(stack->head->next, data_print);
        data_print(stack->head->data);
        printf("(head)\n");
    }
}
