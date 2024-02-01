#include "queue.h"

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
    struct queue *queue = init_queue(sizeof(struct my_item));

    // add item
    struct my_item *item1= malloc(sizeof(struct my_item));
    item1->str = "une";
    void *cast_data = item1;
    add_queue(queue, cast_data, sizeof(struct my_item));

    print_queue(queue, print_item);

    struct my_item *item2= malloc(sizeof(struct my_item));
    item2->str = "string";
    cast_data = item2;
    add_queue(queue, cast_data, sizeof(struct my_item));

    print_queue(queue, print_item);
    
    struct my_item *item3= malloc(sizeof(struct my_item));
    item3->str = "nulle";
    cast_data = item3;
    add_queue(queue, cast_data, sizeof(struct my_item));

    print_queue(queue, print_item);

    struct item *i = pop_queue(queue, sizeof(struct my_item));
    item1 = i->data;
    printf("item = %s\n", item1->str);
    free_item(i->data);
    free(i);

    print_queue(queue, print_item);

    i = pop_queue(queue, sizeof(struct my_item));
    item1 = i->data;
    printf("item = %s\n", item1->str);
    free_item(i->data);
    free(i);

    print_queue(queue, print_item);

    i = pop_queue(queue, sizeof(struct my_item));
    item1 = i->data;
    printf("item = %s\n", item1->str);
    free_item(i->data);
    free(i);

    print_queue(queue, print_item);

    // queue is empty
    clear_queue(queue, free_item);
    print_queue(queue, print_item);


    // free queue
    free_queue(queue, free_item);
}
