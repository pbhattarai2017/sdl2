#include <stdio.h>
#include <stdlib.h>
#define ULLI unsigned long long int

int main(int argc, char *argv[]) {
	char cmdString[50];
	int error = 0;
	if(argc == 1) {
		system("make run");
	} else if(argc == 2) {
		snprintf(cmdString, 50, "make all NAME=%s", argv[1]);
		system(cmdString);
	} else {
		fprintf(stderr, "Invalid arguments");
		fprintf(stderr, "\n\n");
		fprintf(stderr, "Usage: maker main.c");
		fprintf(stderr, "\n");
		fprintf(stderr, "Usage: maker (to execute the recent build)");
		fprintf(stderr, "\n");
	}
	return 0;
}
