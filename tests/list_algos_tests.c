#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>

char *values[] = { "XXXX", "1234", "abcd", "xjvef", "NDSS" };

#define NUM_VALUES 5

List *create_words() {
    int i = 0;
    List *words = List_create();

    for (i = 0; i < NUM_VALUES; i++) {
        List_push(words, values[i]);
    }

    return words;
}

int is_sorted(List *words) {
    LIST_FOREACH(node, words) {
        if (node->next && strcmp(node->value, node->next->value) > 0) {
            debug("%s %s", (char*)node->value, (char*)node->next->value);
            return 0;
        }
    }

    return 1;    
}

char *test_bubble_sort() {
    List *words = create_words();

    // Should work on a list that needs sorting.
    int rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sort failed.");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");


    // Should work on an already sorted list
    rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sort of already sorted list.");
    mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

    List_destroy(words);

    // Should work on an empty list.
    words = List_create(words);
    rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    List_destroy(words);

    return NULL;
}

char *test_merge_sort() {
    List *words = create_words();

    // Should work on a list that needs sorting.
    List *res = List_merge_sort(words, (List_compare) strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

    List *res2 = List_merge_sort(res, (List_compare) strcmp);
    mu_assert(is_sorted(res), "Should still be sorted after merge sort.");
    List_destroy(res2);
    List_destroy(res);

    List_destroy(words);
    return NULL;
}

char *test_insert_sorted() {
    List *words = List_create();

    for (int i = 0; i < NUM_VALUES; i++) {
        List_insert_sorted(words, values[i], (List_compare) strcmp);
    }

    mu_assert(is_sorted(words), "Words elements were not insert sorted.");

    List_destroy(words);

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);
    mu_run_test(test_insert_sorted);

    return NULL;
}

RUN_TESTS(all_tests);
