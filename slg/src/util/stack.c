// implements util/stack.h

#include "stack.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>

void construct_stack_char(Stack_char* stack_char) {
	assert(!stack_char->data);
	
	stack_char->data = malloc(sizeof(char));
	
	stack_char->top = ~((size_t) 0);
	stack_char->capacity = 1;
}

void destruct_stack_char(Stack_char* stack_char) {
	if (stack_char->data) {
		free(stack_char->data);
	}
	stack_char->top = ~((size_t) 0);
	stack_char->capacity = 0;
}

void push_stack_char(Stack_char* stack_char, char value) {
	if (!stack_char->capacity) {
		stack_char->data = malloc(sizeof(char));
		stack_char->capacity = 1;
	}
	
	if (stack_char->top == ~((size_t) 0)) {
		stack_char->top = 0;
		stack_char->data[0] = value;
		return;
	}
	
	while (stack_char->top + 1 >= stack_char->capacity) {
		stack_char->data = realloc(stack_char->data, stack_char->capacity <<= 1);
	}
	
	stack_char->data[++stack_char->top] = value;
}

char top_stack_char(Stack_char* stack_char) {
	assert(stack_char->top != ~((size_t) 0));
	
	return stack_char->data[stack_char->top];
}

void pop_stack_char(Stack_char* stack_char) {
	assert(stack_char->top != ~((size_t) 0));
	
	if (!stack_char->top) {
		stack_char->top = ~((size_t) 0);
		return;
	}
	
	stack_char->top--;
}

int is_empty_stack_char(Stack_char* stack_char) {
	return stack_char->top == ~((size_t) 0);
}
