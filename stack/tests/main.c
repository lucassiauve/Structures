#include "stack.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct my_item
{
    const char *str;
};

void free_item(void *data)
{
    struct my_item *cast_item = data;
    free(cast_item);
}

void print_item(void *data)
{
    struct my_item *cast_item = data;
    printf("%s", cast_item->str);
}

int main(void)
{
    struct stack *stack = init_stack(sizeof(struct my_item));

    // insert item
    struct my_item *item1= malloc(sizeof(struct my_item));
    item1->str = "une";
    void *cast_data = item1;
    insert_stack(stack, cast_data, sizeof(struct my_item));

    struct my_item *item2= malloc(sizeof(struct my_item));
    item2->str = "string";
    cast_data = item2;
    insert_stack(stack, cast_data, sizeof(struct my_item));
    
    struct my_item *item3= malloc(sizeof(struct my_item));
    item3->str = "nulle";
    cast_data = item3;
    insert_stack(stack, cast_data, sizeof(struct my_item));

    print_stack(stack, print_item);

    struct item *i = pop_stack(stack, sizeof(struct my_item));
    item1 = i->data;
    printf("item = %s\n", item1->str);
    free_item(i->data);
    free(i);

    print_stack(stack, print_item);

    // stack is empty
    clear_stack(stack, free_item);
    print_stack(stack, print_item);


    // free stack
    free_stack(stack, free_item);
}
