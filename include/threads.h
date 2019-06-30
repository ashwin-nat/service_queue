#ifndef __THREADS_H__
#define __THREADS_H__

#include "main.h"

#define WORKER_ASLEEP			0
#define	WORKER_AWAKE			1

void *thread_reader(void *arg);
void *thread_worker(void *arg);
int get_exit_flag();
void set_exit_flag(int value);
void request_ready_signal();
void wait_for_requests();
int get_worker_state();
void set_worker_state (int state);

#endif  //__THREADS_H__