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

    stack->data = (char**)malloc(INITIAL_CAPACITY * sizeof(char*));
    check_allocation(stack->data);

    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;

    return stack;
}

void push(Stack* stack, const char* str) {
    if (stack->size >= stack->capacity) {
        fprintf(stderr, "Stack overflow.\n");
        exit(1);
    }

    if (strnlen(str, MAX_STRING_LENGTH + 1) > MAX_STRING_LENGTH) {
        fprintf(stderr, "String exceeds maximum length.\n");
        exit(1);
    }

    char* new_string = (char*)malloc((MAX_STRING_LENGTH + 1) * sizeof(char));
    check_allocation(new_string);

    strncpy(new_string, str, MAX_STRING_LENGTH);
    new_string[MAX_STRING_LENGTH] = '\0';

    stack->data[stack->size++] = new_string;
}

char* pop(Stack* stack) {
    if (stack->size <= 0) {
        fprintf(stderr, "Stack underflow.\n");
        exit(1);
    }

    char* top = stack->data[--stack->size];
    stack->data[stack->size] = NULL;
    return top;
}

void destroy_stack(Stack* stack) {
    if (stack == NULL)
        return;

    for (int i = 0; i < stack->size; i++) {
        free(stack->data[i]);
        stack->data[i] = NULL;
    }

    free(stack->data);
    stack->data = NULL;

    free(stack);
    stack = NULL;
}