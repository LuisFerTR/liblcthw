#ifndef stack_h
#define stack_h

#include <lcthw/list.h>

typedef List Stack;

#define Stack_create List_create
#define Stack_destroy List_destroy
#define Stack_push List_unshift
#define Stack_pop List_shift
#define Stack_peek List_first
#define Stack_count List_count

#define STACK_FOREACH(curr, stack) LIST_FOREACH(curr, stack)

#endif