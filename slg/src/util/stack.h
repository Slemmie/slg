// implements simple stack data structure - first in first out

#pragma once

#include <stddef.h>

typedef struct {
	
	char* data;
	
	size_t top;
	size_t capacity;
	
} Stack_char;

void construct_stack_char(Stack_char* stack_char);

void destruct_stack_char(Stack_char* stack_char);

void push_stack_char(Stack_char* stack_char, char value);

char top_stack_char(Stack_char* stack_char);

void pop_stack_char(Stack_char* stack_char);

int is_empty_stack_char(Stack_char* stack_char);
