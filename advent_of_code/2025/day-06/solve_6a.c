#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 10000
#define MAX_ROWS 5
#define MAX_LINE 100000

long long grid[MAX_ROWS][MAX_COLS];
char ops[MAX_COLS];
int col = 0, row = 0;
char lines[MAX_ROWS + 1][MAX_LINE];

int main() {
    FILE* fp = fopen("input_6.txt", "r");
    if (fp == NULL) { 
		printf("Error opening file.\n"); 
		exit(EXIT_FAILURE);
	}
	
	// Read input
    int total_rows = 0;
    while (total_rows < MAX_ROWS + 1 && fgets(lines[total_rows], MAX_LINE, fp))
        total_rows++;
    fclose(fp);

    // Number rows
    for (int i = 0; i < total_rows - 1; i++) {
        int j = 0;
        char *token = strtok(lines[i], " \n");
        while (token != NULL) {
            grid[i][j++] = atoll(token);
            token = strtok(NULL, " \n");
        }
        if (i == 0) col = j;
        row++;
    }

    // Operator row
	int j = 0;
	char *token = strtok(lines[total_rows - 1], " \n");
	while (token != NULL) {
	    ops[j++] = token[0];
	    token = strtok(NULL, " \n");
	}

    // Traverse columns
    long long total = 0;
    for (int j = 0; j < col; j++) {
        long long result = 0;
		if (ops[j] == '*') 
				result = 1;
        for (int i = 0; i < row; i++) {
            if (ops[j] == '*') result *= grid[i][j];
            else result += grid[i][j];
        }
        total += result;
    }

    printf("%lld\n", total);
    return EXIT_SUCCESS;
}
