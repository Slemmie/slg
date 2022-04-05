// implements tmp_dir_manager.h

#include "tmp_dir_manager.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

char* tmp_dir = NULL;

void create_tmp_dir() {
	assert(!tmp_dir);
	
	srand(time(NULL));
	
	tmp_dir = malloc(sizeof(char) * 32);
	strcpy(tmp_dir, "/tmp/slg");
	tmp_dir[30] = '/';
	tmp_dir[31] = '\0';
	
	do {
		for (int i = 8; i < 30; i++) {
			tmp_dir[i] = '0' + (rand() % 10);
		}
	} while (!access(tmp_dir, F_OK));
	
	int system_exit_status = 0;
	
	char command[9 + 32];
	strcpy(command, "mkdir -p ");
	strcat(command, tmp_dir);
	system_exit_status = system(command);
	if (system_exit_status) {
		printf("[fatal]: failed to create tmp dir\n");
		free(tmp_dir);
		exit(1);
	}
}

const char* get_tmp_dir() {
	return tmp_dir;
}

void clean_exit(int code) {
	if (tmp_dir) {
		char command[7 + 32];
		strcpy(command, "rm -rf ");
		strcat(command, tmp_dir);
		int system_exit_status = system(command);
		if (system_exit_status) {
			printf("[warning]: failed to remove tmp dir\n");
		}
		free(tmp_dir);
	}
	exit(code);
}

void create_file_of(const char* of_path, char* buffer) {
	// create child directory inside tmp directory
	int last_slash_index = -1;
	for (int i = 0; of_path[i] != '\0'; i++) {
		if (of_path[i] == '/') {
			last_slash_index = i;
		}
	}
	char* abs_dir_path = NULL;
	if (last_slash_index) {
		abs_dir_path = malloc(31 + last_slash_index + 1 + 1);
		strcpy(abs_dir_path, tmp_dir);
		for (int i = 0; i <= last_slash_index; i++) {
			abs_dir_path[32 + i] = of_path[i];
		}
		abs_dir_path[31 + last_slash_index + 1] = '\0';
	} else {
		abs_dir_path = malloc(31 + 1);
		strcpy(abs_dir_path, tmp_dir);
	}
	if (last_slash_index != -1) {
		char* command = malloc(sizeof(char) * (9 + strlen(abs_dir_path) + 1));
		strcpy(command, "mkdir -p ");
		strcat(command, abs_dir_path);
		int system_exit_status = system(command);
		if (!system_exit_status) {
			printf("[fatal]: failed to create temporary directory '%s'\n", abs_dir_path);
			clean_exit(1);
		}
	}
	
	// fill buffer
	assert(!buffer);
	buffer = malloc(sizeof(char) * (31 + strlen(of_path) + 1));
	strcpy(buffer, tmp_dir);
	strcat(buffer, of_path);
}
