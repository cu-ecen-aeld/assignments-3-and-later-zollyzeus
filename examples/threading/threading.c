#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    // struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    thread_func_args->thread_complete_success = false; //init result to false
    usleep((thread_func_args->wait_to_obtain_ms)*1000); //wait before attempting mutex lock

    if (pthread_mutex_lock(thread_func_args->mutex) != 0) 
    {
        ERROR_LOG("Mutex lock failed");        
        free(thread_param);
        return NULL;
    }
    else
    {
        DEBUG_LOG("Mutex lock done\n");
    }

    usleep((thread_func_args->wait_to_release_ms)*1000); //wait before releasing mutex lock

    if (pthread_mutex_unlock(thread_func_args->mutex) != 0) {
        ERROR_LOG("Mutex unlock failed");        
        free(thread_param);
        return NULL;
    }
    else
    {
        DEBUG_LOG("Mutex unlock done\n");
    }    
    
    thread_func_args->thread_complete_success = true;//set result to true

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */

    struct thread_data* thread1_data = (struct thread_data*)malloc(sizeof(struct thread_data));
    if (thread1_data == NULL) 
    {
        ERROR_LOG("Memory allocation failed");        
        return false;
    }

    thread1_data->mutex = mutex;
    thread1_data->wait_to_obtain_ms = wait_to_obtain_ms;
    thread1_data->wait_to_release_ms = wait_to_release_ms;
    thread1_data->thread_complete_success = false; // Initial state

    if (pthread_create(thread, NULL, threadfunc, thread1_data) != 0) {
        ERROR_LOG("Thread creation failed");
        free(thread1_data);
        return false;
    }

    return true;
}

