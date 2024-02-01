#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

typedef void (*func_free)(void *data);
typedef void (*func_print)(void *data);

struct item
{
    void *data;
    struct item *next;
};


struct queue
{
    struct item *head;
    struct item *tail;
    size_t size;
    int error;
    size_t sizeof_data;
};

// create and destroy queue
struct queue *init_queue(size_t sizeof_data);
void clear_queue(struct queue* queue, func_free data_free);
void free_queue(struct queue* queue, func_free data_free);

// update queue
int add_queue(struct queue *queue, void *data, size_t sizeof_data);
struct item *pop_queue(struct queue *queue, size_t sizeof_data);

// check queue status
int is_queue_empty(struct queue *queue);

// manage error
void reset_error(struct queue *queue);
void set_error(struct queue *queue, int error);
int read_error(struct queue *queue);

// print data in queue
void print_queue(struct queue *queue, func_print data_print);

#endif /* ! QUEUE_H */
