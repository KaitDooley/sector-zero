#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int main() {
	FILE* fp = fopen("input_5.txt", "r");
  	if (fp == NULL) {
    	printf("Error opening file.\n");
    	exit(EXIT_FAILURE);
    }
    int total = 0, index = 0;
	char line[BUFSIZ];

	while (fgets(line, sizeof(line), fp)) {
	

	}
	printf("%d\n", total);
	return EXIT_SUCCESS;
}


