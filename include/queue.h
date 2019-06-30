#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "main.h"

typedef struct _node_contents
{
    int sleep_time;
    int dummy;
    //add the data for the worker thread here
}node_contents_t;

typedef struct _queue_node
{
    node_contents_t req;
    struct _queue_node *next;
    struct _queue_node *prev;
}queue_node_t;

void print_queue();
void enqueue (int value);
queue_node_t* dequeue();

#endif  //__QUEUE_H__