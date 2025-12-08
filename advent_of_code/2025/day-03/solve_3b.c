#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


int main() {
        FILE* fp = fopen("input_3.txt", "r");
        if (fp == NULL) {
                printf("Error opening file.\n");
                exit(EXIT_FAILURE);
        }
		uint64_t alpha, total = 0, num;
		int len, index = 0;
        char line[BUFSIZ];


        while (fgets(line, sizeof(line), fp)) { 
			len = strlen(line);
			if (line[len - 1] == '\n') len--;
			index = 0;
			num = 0;
			for (int j = 12; j > 0; j--) {
				alpha = 0;
				for (int i = index ; i <= len - j; i++) {
					if (line[i] - '0' > alpha) {
						alpha = line[i] - '0';
						index = i + 1;
					}
				}
				num = num*10 + alpha;
			}		
			total += num;	
		}
		printf("%llu\n", total);
        return EXIT_SUCCESS;
}

