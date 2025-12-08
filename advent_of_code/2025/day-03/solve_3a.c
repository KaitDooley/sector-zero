#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int main() {
        FILE* fp = fopen("input_3.txt", "r");
        if (fp == NULL) {
                printf("Error opening file.\n");
                exit(EXIT_FAILURE);
        }
		int alpha, beta, len, total = 0, index = 0;
        char line[BUFSIZ];


        while (fgets(line, sizeof(line), fp)) { 
			len = strlen(line);
			if (line[len - 1] == '\n') len--;
			alpha = 0;
			beta = 0;
			for (int i = 0; i < len - 1; i++) {
				if (line[i] - '0' > alpha) {
					alpha = line[i] - '0';
					index = i;
				}
			}
			for (int i = index + 1; i < len; i++) {
				if (line[i] - '0' > beta) beta = line[i] - '0';
			}
			total += (alpha * 10) + beta;
			printf("%d\n", total);
		}
		printf("%d\n", total);
        return EXIT_SUCCESS;
}

