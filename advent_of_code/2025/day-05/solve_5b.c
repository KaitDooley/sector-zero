#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct { long long low, high; } Range;
Range ranges[100000];
int nranges = 0;

int cmp(const void *a, const void *b) {
    Range *ra = (Range *)a, *rb = (Range *)b;
    if (ra->low < rb->low) return -1;
    if (ra->low > rb->low) return 1;
    return 0;
}

int main() {
    FILE* fp = fopen("input_5.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    char line[BUFSIZ];

    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '\n') { break; }
		long long low, high;
		if (sscanf(line, "%lld-%lld", &low, &high) == 2) {
			ranges[nranges].low = low;
			ranges[nranges++].high = high;
		}
    }

	// Sort by low
    qsort(ranges, nranges, sizeof(Range), cmp);

    // Merge and count
    long long total = 0;
    long long cur_low = ranges[0].low, cur_high = ranges[0].high;
    for (int i = 1; i < nranges; i++) {
        if (ranges[i].low <= cur_high + 1) {
            // Overlapping or adjacent, extend if needed
            if (ranges[i].high > cur_high)
                cur_high = ranges[i].high;
        } else {
            // Gap, count current merged range and start new one
            total += cur_high - cur_low + 1;
            cur_low = ranges[i].low;
            cur_high = ranges[i].high;
        }
    }
    total += cur_high - cur_low + 1;  // last range

    printf("%lld\n", total);
    fclose(fp);
    return EXIT_SUCCESS;
}
