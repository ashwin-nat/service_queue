#include "threads.h"

pthread_mutex_t exit_flag_mutex = PTHREAD_MUTEX_INITIALIZER;
sig_atomic_t    exit_flag       = FALSE;

pthread_mutex_t cond_mutex      = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var         = PTHREAD_COND_INITIALIZER;
sig_atomic_t is_input_ready     = FALSE;

pthread_mutex_t worker_state_mutex	= PTHREAD_MUTEX_INITIALIZER;
sig_atomic_t worker_state		= WORKER_ASLEEP;

int input;

int get_exit_flag()
{
    int ret;
    pthread_mutex_lock      (&exit_flag_mutex);
    ret = (int) exit_flag;
    pthread_mutex_unlock    (&exit_flag_mutex);
    return ret;
}

void set_exit_flag(int value)
{
    pthread_mutex_lock      (&exit_flag_mutex);
    exit_flag   = (sig_atomic_t) value;
    pthread_mutex_unlock    (&exit_flag_mutex);
}

void request_ready_signal()
{
	if(WORKER_ASLEEP == get_worker_state())
	{
		pthread_mutex_lock  (&cond_mutex);
		is_input_ready = TRUE;
		pthread_cond_signal (&cond_var);
		pthread_mutex_unlock(&cond_mutex);
	}
}

void wait_for_requests()
{
	set_worker_state (WORKER_ASLEEP);
	pthread_mutex_lock(&cond_mutex);
	is_input_ready  = FALSE;
	while(is_input_ready == FALSE)
	{
		pthread_cond_wait(&cond_var,&cond_mutex);
	}

	
	pthread_mutex_unlock(&cond_mutex);
	set_worker_state (WORKER_AWAKE);
}

int get_worker_state()
{
	pthread_mutex_lock	(&worker_state_mutex);
	int ret	= (int) worker_state;	
	pthread_mutex_unlock(&worker_state_mutex);
	return ret;
}

void set_worker_state (int state)
{
	pthread_mutex_lock	(&worker_state_mutex);
	worker_state	= (sig_atomic_t) state;
	pthread_mutex_unlock(&worker_state_mutex);
}

void *thread_reader(void *arg)
{
    int choice;
    while(1)
    {
        printf("%s: 1. enqueue 2. print: ",__func__);
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                register_request();
				request_ready_signal();
                break;
            
            case 2:
                print_queue();
                break;

            default:
                printf("%s: invalid input\n",__func__);
                break;
        }
        


    }

    return NULL;
}

void *thread_worker(void *arg)
{
    
    while(1)
    {
        printf("%s: waiting...\n",__func__);
		wait_for_requests();
        
        printf("%s: woke up\n",__func__);
        while(1)
        {
            if(FAILURE == service_request())
            {
                break;
            }
        }
        
    }
}