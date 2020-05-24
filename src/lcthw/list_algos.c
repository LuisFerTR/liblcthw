#include <lcthw/list_algos.h>
#include <stdbool.h>
#include <stdio.h>
#include <lcthw/dbg.h>

void printList(char *msg, List *list) {
	printf("%s", msg);
	LIST_FOREACH(curr, list)
	{
		printf("%s ", (char *)curr->value);
	}
	
	printf("\n");
}

void List_swap_nodes(ListNode *first, ListNode *second) {
    void *tmp = first->value;
    first->value = second->value;
    second->value = tmp;
}

int List_bubble_sort(List *list, List_compare cmp) {
    check(list != NULL, "List can't be NULL");
    check(cmp != NULL, "Compare function can't be NULL.");

    bool sorted = false;
	while (!sorted) {
        sorted = true;
        LIST_FOREACH(node, list)  {
            if (!node->next) continue;

            if (cmp(node->value, node->next->value) > 0)  {
                List_swap_nodes(node, node->next);
                
                sorted = false;
            }
        }
	}

	return 0;

error:
    return 1;
}

List *List_merge_sort(List *list, List_compare cmp) {
    check(cmp != NULL, "Compare function can't be NULL.");

    if (List_count(list) <= 1) return list;

    List *first = List_create();
    List *second = List_create();
    List *result = List_create();

    int i = 0;
    LIST_FOREACH(node, list) {
        if (i < List_count(list) / 2) {
            List_push(first, node->value);
        } else {
            List_push(second, node->value);
        }
        i++;
    }

    first = List_merge_sort(first, cmp);
    second = List_merge_sort(second, cmp);
	
    ListNode *firstNode = first->first;
    ListNode *secondNode = second->first;
    while (firstNode != NULL && secondNode != NULL) {
        if (cmp(firstNode->value, secondNode->value) <= 0) {
            List_push(result, firstNode->value);
            firstNode = firstNode->next;
        }
        else {
            List_push(result, secondNode->value);
            secondNode = secondNode->next;
        }
    }

    while (firstNode != NULL) {
        List_push(result, firstNode->value);
        firstNode = firstNode->next;
    }
    
    while (secondNode != NULL) {
        List_push(result, secondNode->value);
        secondNode = secondNode->next;
    }
    
    List_destroy(first);
    List_destroy(second);

	return result;

error:
    return NULL;
}

void List_insert_sorted(List * list, void *value, List_compare cmp) {
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;
    node->prev = NULL;
    node->next = NULL;
    
    if (list->first == NULL) {
        list->first = node;
        list->last = node;       
    } else if (cmp(list->first->value, value) >= 0) {
        node->next = list->first;
        node->next->prev = node;
        list->first = node;
    } else {
        ListNode *current = list->first;
        while (current->next != NULL && cmp(current->next->value, value) < 0){
            current = current->next;
        }
        
        node->next = current->next;
        
        if (current->next != NULL) node->next->prev = node;

        current->next = node;
        node->prev = current;
    }

    list->count++;

error:
    return;
}