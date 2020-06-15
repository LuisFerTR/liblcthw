#ifndef stack_h
#define stack_h

#include <lcthw/list.h>
#include <dbg.h>

typedef struct stack {
    List *head;
    int size;
} Stack;

Stack *Stack_create();
int Stack_destroy(Stack *stack);
int Stack_push(Stack *stack, void *value);
void *Stack_pop(Stack *stack);
void *Stack_peek(Stack *stack);
int Stack_count(Stack *stack);


Stack *Stack_create() {
    Stack *temp = (Stack*)malloc(sizeof(Stack));
    check_mem(temp);

    temp->head = List_create();
    check_mem(temp->head);

    temp->size = 0;

error:
    return NULL;
}

int Stack_destroy(Stack *stack) {
    check(stack != NULL, "stack points to NULL");

    if (stack->head) List_clear_destroy(stack->head);
    free(stack);

    return 0;
error:
    return -1;
}

int Stack_push(Stack *stack, void *value) {
    check(stack != NULL, "Stack does not exist.");
    check(value != NULL, "value can't be NULL.");

    List_unshift(stack->head, value);
    stack->size = stack->head->count;

    return 0;
error:
    return -1;    
}

void *Stack_pop(Stack *stack) {
    check(stack != NULL, "Stack can't be NULL.");

    void * temp = List_shift(stack->head);
    stack->size = stack->head->count;

    return temp;

error:
    return NULL;
}

void *Stack_peek(Stack *stack) {
    check(stack != NULL, "stack can't be NULL");

    return stack->head->first;

error:
    return NULL;
}

#define STACK_FOREACH(stack, cur) \
	ListNode *cur = stack->head->first;\
    for (ListNode *_node = stack->head->first; \
         _node != NULL; \
         cur = _node = _node->next)

#endif