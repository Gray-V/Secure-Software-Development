#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define INITIAL_CAPACITY 10
#define MAX_CAPACITY 1000
#define MAX_STRING_LENGTH 100

struct StackStruct {
    char** data;
    int size;
    int capacity;
};

static void check_allocation(void* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
}

Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    check_allocation(stack);

    stack->data = (char**)calloc(INITIAL_CAPACITY, sizeof(char*));
    check_allocation(stack->data);

    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;

    return stack;
}

int push(Stack* stack, const char* str) {
    if (stack == NULL || str == NULL)
        return 0;

    if (stack->size >= stack->capacity)
        return 0;

    size_t str_length = strnlen(str, MAX_STRING_LENGTH);
    if (str_length >= MAX_STRING_LENGTH)
        return 0;

    char* new_string = (char*)malloc((str_length + 1) * sizeof(char));
    check_allocation(new_string);

    strncpy(new_string, str, str_length);
    new_string[str_length] = '\0';

    stack->data[stack->size++] = new_string;

    return 1;
}

int pop(Stack* stack, char** str) {
    if (stack == NULL || str == NULL || stack->size <= 0)
        return 0;

    char* top = stack->data[--stack->size];
    *str = (char*)malloc((strnlen(top, MAX_STRING_LENGTH) + 1) * sizeof(char));
    check_allocation(*str);

    strncpy(*str, top, MAX_STRING_LENGTH);
    (*str)[MAX_STRING_LENGTH] = '\0';

    free(top);
    stack->data[stack->size] = NULL;

    return 1;
}

void destroy_stack(Stack** stack) {
    if (stack == NULL || *stack == NULL)
        return;

    Stack* s = *stack;

    for (int i = 0; i < s->size; i++) {
        free(s->data[i]);
        s->data[i] = NULL;
    }

    free(s->data);
    s->data = NULL;

    free(s);
    *stack = NULL;
}