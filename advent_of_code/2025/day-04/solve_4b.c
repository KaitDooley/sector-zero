#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int main() {
	FILE* fp = fopen("input_4.txt", "r");
  	if (fp == NULL) {
    	printf("Error opening file.\n");
    	exit(EXIT_FAILURE);
    }
    int total = 0, index = 0;
	char line[BUFSIZ];
	char array[150][150] = {0};

	while (fgets(line, sizeof(line), fp)) {
		for (int i = 0; i < strlen(line); i++){
    		array[index][i] = line[i];
		}
		index++;
	}
	int close = 0, max = 150, round = 1;
	while (round > 0) {
		round = 0;
		for (int i = 0; i < index; i++) {
			for (int j = 0; j < max; j++) {
				if (array[i][j] == '@') {
					// check row above
					if (i > 0) {
						close += (array[i-1][j] == '@');
						if (j > 0) close += (array[i-1][j-1] == '@');
						if (j < max - 1) close += (array[i-1][j+1] == '@');
					}
					// check current row	
					if (j > 0) close += (array[i][j-1] == '@');
					if (j < max - 1) close += (array[i][j+1] == '@');
					// check row below
					if (i < max - 1) {
						close += (array[i+1][j] == '@');
						if (j > 0) close += (array[i+1][j-1] == '@');
						if (j < max - 1) close += (array[i+1][j+1] == '@');
					}
					// increment total if necessary
					if (close < 4) {
						round++;
						array[i][j] = '.';
					}
					close = 0;
				}
			}
		}
		total += round;
	}
	printf("%d\n", total);
	return EXIT_SUCCESS;
}


