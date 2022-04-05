// implements tmp_dir_manager.h

#include "tmp_dir_manager.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

char* tmp_dir = NULL;

void create_tmp_dir() {
	assert(!tmp_dir);
	
	srand(time(NULL));
	
	tmp_dir = malloc(sizeof(char) * 32);
	strcpy(tmp_dir, "/tmp/slg");
	tmp_dir[30] = '/';
	tmp_dir[31] = '\0';
	for (int i = 8; i < 30; i++) {
		tmp_dir[i] = '0' + (rand() % 10);
	}
	
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
