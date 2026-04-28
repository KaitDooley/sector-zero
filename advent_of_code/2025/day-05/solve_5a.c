#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct { long long low, high; } Range;
Range ranges[100000];
int nranges = 0;

int main() {
    FILE* fp = fopen("input_5.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    int in_ids = 0, total = 0;
    char line[BUFSIZ];

    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '\n') { in_ids = 1; continue; }
        if (!in_ids) {
            long long low, high;
            if (sscanf(line, "%lld-%lld", &low, &high) == 2) {
                ranges[nranges].low = low;
                ranges[nranges++].high = high;
            }
        } else {
            long long id;
            if (sscanf(line, "%lld", &id) == 1) {
                for (int i = 0; i < nranges; i++) {
                    if (id >= ranges[i].low && id <= ranges[i].high) {
                        total++;
                        break;
                    }
                }
            }
        }
    }

    printf("%d\n", total);
    fclose(fp);
    return EXIT_SUCCESS;
}
