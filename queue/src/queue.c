#include "queue.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Create and destroy queue
 */
// Init and empty queue
struct queue *init_queue(size_t sizeof_data)
{
    struct queue *new_queue = malloc(sizeof(struct queue));

    new_queue->head = NULL;
    new_queue->tail = NULL;
    new_queue->size = 0;
    new_queue->error = 0;
    new_queue->sizeof_data = sizeof_data;

    return new_queue;
}

// Free queue items, queue is not free and stell usable
static void rec_clear_queue(struct item *item, func_free data_free)
{
    if (item == NULL)
        return;

    rec_clear_queue(item->next, data_free);
    data_free(item->data);
    free(item);
}

void clear_queue(struct queue* queue, func_free data_free)
{
    rec_clear_queue(queue->head, data_free);
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->error = 0;
}

// free queue items and queue it self, queue is unusable
void free_queue(struct queue* queue, func_free data_free)
{
    clear_queue(queue, data_free);
    free(queue);
}

/*
 * Update queue
 */
// insert new item at tail with data data, return 1 succed otherwise 0
int add_queue(struct queue *queue, void *data, size_t sizeof_data)
{
    if (queue == NULL || sizeof_data != queue->sizeof_data)
        return 0;

    struct item *new_item = malloc(sizeof(struct item));
    new_item->data = data;
    new_item->next = NULL;

    // first item in queue
    if (queue->size == 0)
        queue->head = new_item;
    else
        queue->tail->next = new_item;
    queue->tail = new_item;
    queue->size += 1;


    return 1;
}

// pop first element, return NULL if queue is empty otherwise first item
struct item *pop_queue(struct queue *queue, size_t sizeof_data)
{
    if (queue == NULL || sizeof_data != queue->sizeof_data || !queue->size)
        return NULL;

    struct item *tmp = queue->head;
    queue->head = queue->head->next;
    queue->size -= 1;

    return  tmp;
}

/*
 * Check queue status
 */
int is_queue_empty(struct queue *queue)
{
    if (queue->size != 0)
        return 0;
    return 1;
}

/*
 * Manage error
 */
void reset_error(struct queue *queue)
{
    queue->error = 0;
}

void set_error(struct queue *queue, int error)
{
    queue->error = error;
}

int read_error(struct queue *queue)
{
    return queue->error;
}

/*
 * Print data i queue
 */
// print queue with line break at end
static void rec_print_queue(struct item *item, func_print data_print)
{
    if (item == NULL)
        return;

    printf(" <- ");
    data_print(item->data);
    rec_print_queue(item->next, data_print);
}

void print_queue(struct queue *queue, func_print data_print)
{
    if (queue->size == 0)
    {
        printf("queue is empty\n");
    }
    else
    {
        printf("(head)");
        data_print(queue->head->data);
        rec_print_queue(queue->head->next, data_print);
        printf("(tail)\n");
    }
}
