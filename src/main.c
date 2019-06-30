#include "main.h"

extern queue_node_t *queue_start, *queue_end;
extern pthread_mutex_t queue_mutex;
extern pthread_mutex_t  exit_flag_mutex;

void sigint_handler(int sig)
{
    printf("\nSIGINT handler\n");
    exit(0);
}


int main()
{
    struct sigaction act;
    
	act.sa_handler = sigint_handler;

 
	if (sigaction(SIGINT, &act, NULL) < 0) {
		perror ("sigaction");
		return 1;
	}
 

    srand(time(NULL));

    pthread_t reader, writer;

    pthread_create (&reader, NULL, thread_reader, NULL);
    pthread_create (&writer, NULL, thread_worker, NULL);

    pthread_join (reader, NULL);
    pthread_join (writer, NULL);

    return SUCCESS;
}