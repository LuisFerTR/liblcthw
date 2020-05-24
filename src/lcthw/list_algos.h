#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>

typedef int (*List_compare) (const void *a, const void *b);

int bubble_sort(List *list, List_compare cmp);

List *merge_sort(List *list, List_compare cmp);

#endif