#ifndef queue_h
#define queue_h

#include <lcthw/list.h>

typedef List Queue;

#define Queue_create List_create
#define Queue_destroy List_destroy
#define Queue_send List_push
#define Queue_recv List_shift
#define Queue_count List_count
#define Queue_peek List_first
#define QUEUE_FOREACH(curr, queue) LIST_FOREACH(curr, queue)

#endif