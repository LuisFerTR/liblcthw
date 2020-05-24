#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

int bubble_sort(List *list, List_compare cmp) {
    check(list != NULL, "List can't be NULL.");
    check(cmp != NULL, "Invalid compare function.");
    
    int i = 0;
    int j = 0;
    int swapped = 0;

    for (i = 0; i < list->count - 1; i++) {
        swapped = 0;

        LIST_FOREACH(list, first, next, cur) {
            if (cmp(cur->value, cur->next->value) > 0) {
                void *temp = cur->value;
                cur->value = cur->next->value;
                cur->next->value = temp;
                swapped = 1;
            }
        }

        if (swapped = 0) break;
    }

    return 0;

error:
    return 1;
}

List *merge_sort(List *list, List_compare cmp) {

}