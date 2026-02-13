#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int process_line(char *line, int *beams, int len);

int main() {
    FILE* fp = fopen("input_7.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
    	exit(EXIT_FAILURE);
    }

	int splits = 0;
    char line[BUFSIZ];

	// Find start
	fgets(line, sizeof(line), fp);
	int len = strlen(line);
	int beams[len];
	memset(beams, 0, sizeof(beams));

	for (int i = 0; i < len; i++) {
		if (line[i] == 'S') beams[i] = 1;
	}

	// Processes following lines
	while (fgets(line, sizeof(line), fp)) {
		splits += process_line(line, beams, len);
	}

    printf("%d\n", splits);
    fclose(fp);
    return EXIT_SUCCESS;
}


int process_line(char * line, int * beams, int len) {
	int splits = 0;
	for (int i = 0;	i < len; i++) {
		// Hits splitter
		if (beams[i] == 1 && line[i] == '^') {
			splits ++;
			beams[i] = 0;	// remove beam in row
			if (i > 0) beams[i-1] = 1;		// split left
			if (i < len-1) beams[i+1] = 1;	// split right
		}
	}
	return splits;
}
