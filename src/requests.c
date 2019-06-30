#include "requests.h"

int service_request()
{
    queue_node_t *req = dequeue();

    if(req == NULL)
    {
        printf("No requests\n");
        return FAILURE;
    }
    else
    {
        sleep(req->req.sleep_time);
        printf("\tFinished servicing request with sleep time = %d\n\t",req->req.sleep_time);
		print_queue();
        return SUCCESS;
    }
	
}

void register_request()
{
    int random = rand() % 10;
    printf("Enqueuing %d\n",random);
    enqueue(random);
    print_queue();
}