// implements compilation_preprocessing.h

#include "compilation_preprocessing.h"

#include "tmp_dir_manager.h"
#include "util/stack.h"
#include "util/numerical.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void check_balanced_brackets(const char* input_buffer) {
	const int brackets_count = 3;
	const char brackets_open[] = "({[";
	const char brackets_close[] = ")}]";
	
	Stack_char stck;
	construct_stack_char(&stck);
	
	for (size_t i = 0; input_buffer[i] != '\0'; i++) {
		char c = input_buffer[i];
		// handle quotes
		if (c == '\'') {
			if (!is_empty_stack_char(&stck) && top_stack_char(&stck) == '\'') {
				pop_stack_char(&stck);
			} else {
				push_stack_char(&stck, '\'');
			}
			continue;
		}
		
		// if inside quotes, do not care about balancing
		if (!is_empty_stack_char(&stck) && top_stack_char(&stck) == '\'') {
			continue;
		}
		
		// check actual brackets
		for (int j = 0; j < brackets_count; j++) {
			if (c == brackets_open[j]) {
				push_stack_char(&stck, c);
			} else if (c == brackets_close[j]) {
				if (is_empty_stack_char(&stck) || top_stack_char(&stck) != brackets_open[j]) {
					printf("[fatal]: unbalanced brackets in input file\n");
					clean_exit(1);
				}
			}
		}
	}
	
	// make sure the stack is left empty
	if (!is_empty_stack_char(&stck)) {
		printf("[fatal]: unbalanced brackets in input file\n");
		clean_exit(1);
	}
}

void replace_charconstexpr(char** input_buffer) {
	size_t needed_size = 1;
	
	for (size_t i = 0; (*input_buffer)[i] != '\0'; i++) {
		if ((*input_buffer)[i] != '\'') {
			needed_size++;
			continue;
		}
		if ((*input_buffer)[i + 1] == '\'') {
			printf("[fatal]: incorrect contents of ' enclosed expression\n");
			clean_exit(1);
		}
		if ((*input_buffer)[i + 2] != '\'' && (*input_buffer)[i + 3] != '\'') {
			printf("[fatal]: incorrect contents of ' enclosed expression\n");
			clean_exit(1);
		}
		if ((*input_buffer)[i + 3] == '\'') {
			if ((*input_buffer)[i + 1] != '\\') {
				printf("[fatal]: incorrect contents of ' enclosed expression\n");
				clean_exit(1);
			}
			if (
			(*input_buffer)[i + 2] != 'n' &&
			(*input_buffer)[i + 2] != 't' &&
			(*input_buffer)[i + 2] != '0') {
				printf("[fatal]: incorrect contents of ' enclosed expression\n");
				clean_exit(1);
			}
			needed_size += digit_count(
			(*input_buffer)[i + 2] == 'n' ? '\n' :
			(*input_buffer)[i + 2] == 't' ? '\t' :
			(*input_buffer)[i + 2] == '0' ? '\0' :
			'\0');
			i += 3;
		} else {
			needed_size += digit_count((*input_buffer)[i + 1]);
			i += 2;
		}
	}
	
	char* result_buffer = malloc(sizeof(char) * needed_size);
	result_buffer[0] = '\0';
	
	char scat[2];
	scat[1] = '\0';
	
	for (size_t i = 0; (*input_buffer)[i] != '\0'; i++) {
		if ((*input_buffer)[i] != '\'') {
			scat[0] = (*input_buffer)[i];
			strcat(result_buffer, scat);
			continue;
		}
		if ((*input_buffer)[i + 2] == '\'') {
			char num[4];
			scat[0] = (*input_buffer)[i + 1];
			iota(scat[0], num, 10);
			strcat(result_buffer, num);
			i += 2;
		} else {
			char num[4];
			scat[0] =
			(*input_buffer)[i + 2] == 'n' ? '\n' :
			(*input_buffer)[i + 2] == 't' ? '\t' :
			(*input_buffer)[i + 2] == '0' ? '\0' :
			'\0';
			iota(scat[0], num, 10);
			strcat(result_buffer, num);
			i += 3;
		}
	}
	
	free(*input_buffer);
	*input_buffer = result_buffer;
}
