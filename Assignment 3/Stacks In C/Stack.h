#ifndef STACK_H
#define STACK_H

typedef struct StackStruct Stack;

Stack* create_stack();
int push(Stack* stack, const char* str);
int pop(Stack* stack, char** str);
void destroy_stack(Stack** stack);

#endif /* STACK_H */
