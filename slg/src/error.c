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
	
	exit(EXIT_FAILURE);
}
