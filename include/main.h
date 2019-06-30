#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <string.h>

#include "requests.h"
#include "queue.h"
#include "threads.h"

void cleanup();
void sigint_handler(int sig);

#define TRUE    1
#define FALSE   0

#define SUCCESS 0
#define FAILURE -1
#endif