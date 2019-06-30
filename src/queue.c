#include "queue.h"

queue_node_t *start = NULL, *end = NULL;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;

//enter the queue from the end.
void enqueue (int value)
{
    pthread_mutex_lock   (&queue_mutex);

    queue_node_t *node = malloc(sizeof(queue_node_t));
    memset(node,0,sizeof(queue_node_t));
    node->req.sleep_time = value;
    
    if(start == NULL || end == NULL)
    {
        start       = node;
        end         = node;
    }
    else
    {
        end->next   = node;
        node->prev  = end;
        end         = node;
    }

    pthread_mutex_unlock (&queue_mutex);
}

//exit the queue from the start
queue_node_t* dequeue()
{
    queue_node_t *ret = NULL;
    pthread_mutex_lock   (&queue_mutex);
    if(!(start == NULL || end == NULL))
    {
        ret         = start;
        start       = start->next;
        if(start == NULL)
        {
            end = NULL;
        }
        else
        {
            start->prev = NULL;
            ret->next   = NULL;
            ret->prev   = NULL;
        }
    }
    pthread_mutex_unlock (&queue_mutex);
    return ret;
}

void print_queue()
{
    pthread_mutex_lock   (&queue_mutex);
    if(start == NULL || end == NULL)
    {
        printf("\tEmpty queue\n");
    }
    else
    {
        queue_node_t *temp;
        printf("\tstart->");
        for(temp = start; temp != NULL; temp = temp->next)
        {
            printf("%d->",temp->req.sleep_time);
        }
        printf("end\n");
    }
    pthread_mutex_unlock (&queue_mutex);
}