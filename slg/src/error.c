// implements error.h

#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// [debug mode]:
// utility function for tracing the callstack
#ifdef __SLG_DEBUG

#include <execinfo.h>
#include <unistd.h>
#include <signal.h>

void _stack_tracer() {
	void* entries[128];
	
	size_t size = backtrace(entries, 128);
	
	fprintf(stderr, "stack:\n");
	backtrace_symbols_fd(entries, size, STDERR_FILENO);
	
	fflush(stderr);
}

void _stack_tracer_sig(int sig) {
	void* entries[128];
	
	size_t size = backtrace(entries, 128);
	
	fprintf(stderr, "(slg crashed unexpectedly with signal %d) stack:\n", sig);
	backtrace_symbols_fd(entries, size, STDERR_FILENO);
	
	fflush(stderr);
}
#endif

typedef struct {
	
	size_t size;
	size_t capacity;
	
	void** buffer;
	
} _Error_alloc_container;

_Error_alloc_container _error_alloc_container;

void init_errors() {
#ifdef __SLG_DEBUG
	signal(SIGFPE, _stack_tracer_sig);
	signal(SIGILL, _stack_tracer_sig);
	signal(SIGSEGV, _stack_tracer_sig);
	signal(SIGBUS, _stack_tracer_sig);
	signal(SIGABRT, _stack_tracer_sig);
	signal(SIGIOT, _stack_tracer_sig);
	signal(SIGSYS, _stack_tracer_sig);
#endif
	
	_error_alloc_container.size = _error_alloc_container.capacity = 0;
}

void* error_alloc(size_t bytes) {
	if (!_error_alloc_container.capacity) {
		_error_alloc_container.buffer =
		malloc(sizeof(void*) * (_error_alloc_container.capacity = 1));
		
		if (!_error_alloc_container.buffer) {
			internal_fatal_error("malloc failed");
		}
	}
	
	int do_realloc = 0;
	while (_error_alloc_container.size + 1 > _error_alloc_container.capacity) {
		_error_alloc_container.capacity <<= 1;
		
		do_realloc = 1;
	}
	
	if (do_realloc) {
		_error_alloc_container.buffer =
		realloc(_error_alloc_container.buffer, _error_alloc_container.capacity);
		
		if (!_error_alloc_container.buffer) {
			internal_fatal_error("realloc failed");
		}
	}
	
	_error_alloc_container.buffer[_error_alloc_container.size] = malloc(bytes);
	
	if (!_error_alloc_container.buffer[_error_alloc_container.size]) {
		internal_fatal_error("malloc failed");
	}
	
	return _error_alloc_container.buffer[_error_alloc_container.size++];
}

void _destruct__error_alloc_container() {
	if (_error_alloc_container.buffer) {
		for (size_t i = 0; i < _error_alloc_container.size; i++) {
			if (_error_alloc_container.buffer[i]) {
				free(_error_alloc_container.buffer[i]);
			}
		}
		
		free(_error_alloc_container.buffer);
	}
	
	_error_alloc_container.size = _error_alloc_container.capacity = 0;
	
	_error_alloc_container.buffer = NULL;
}

void fatal_error(const char* format, ...) {
	fprintf(stderr, "slg: \033[31mfatal error\033[0m: ");
	
	va_list arg;
	va_start(arg, format);
	vfprintf(stderr, format, arg);
	va_end(arg);
	
	fprintf(stderr, "\n");
	
	fflush(stderr);
	
#ifdef __SLG_DEBUG
	fprintf(stderr, "\n");
	_stack_tracer();
#endif
	
	_destruct__error_alloc_container();
	
	exit(EXIT_FAILURE);
}

void internal_fatal_error(const char* format, ...) {
	fprintf(stderr, "slg: \033[31mfatal error (internal)\033[0m: ");
	
	va_list arg;
	va_start(arg, format);
	vfprintf(stderr, format, arg);
	va_end(arg);
	
	fprintf(stderr, "\n");
	
	fflush(stderr);
	
#ifdef __SLG_DEBUG
	fprintf(stderr, "\n");
	_stack_tracer();
#endif
	
	_destruct__error_alloc_container();
	
	exit(EXIT_FAILURE);
}
