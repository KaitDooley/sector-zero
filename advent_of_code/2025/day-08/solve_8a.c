// Based on code from Programiz
#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 10000
#define TOP_K      1000

typedef struct {
    long long w;
    int u, v;
} edge;

int n;
int px[MAX_POINTS], py[MAX_POINTS], pz[MAX_POINTS];
int belongs[MAX_POINTS];

edge *elist;
int   elist_n;
edge  spanlist[TOP_K];
int   spanlist_n;

int find(int vertexno) {
    return belongs[vertexno];
}

void applyUnion(int c1, int c2) {
    for (int i = 0; i < n; i++)
        if (belongs[i] == c2)
            belongs[i] = c1;
}

int cmp_edge(const void *a, const void *b) {
    const edge *ea = (const edge *)a;
    const edge *eb = (const edge *)b;
    if (ea->w < eb->w) return -1;
    if (ea->w > eb->w) return  1;
    return 0;
}

void sort() {
    qsort(elist, elist_n, sizeof(edge), cmp_edge);
}

void kruskalAlgo() {
    elist_n = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            long long dx = px[i] - px[j];
            long long dy = py[i] - py[j];
            long long dz = pz[i] - pz[j];
            elist[elist_n].w = dx*dx + dy*dy + dz*dz;
            elist[elist_n].u = i;
            elist[elist_n].v = j;
            elist_n++;
        }
    }

    sort();

    for (int i = 0; i < n; i++)
        belongs[i] = i;

    spanlist_n = 0;
    for (int i = 0; i < TOP_K && i < elist_n; i++) {
        int cno1 = find(elist[i].u);
        int cno2 = find(elist[i].v);
        if (cno1 != cno2) {
            spanlist[spanlist_n++] = elist[i];
            applyUnion(cno1, cno2);
        }
    }
}

void print() {
    int freq[MAX_POINTS] = {0};
    for (int i = 0; i < n; i++)
        freq[belongs[i]]++;

    int sizes[MAX_POINTS], ns = 0;
    for (int i = 0; i < n; i++)
        if (freq[i] > 0)
            sizes[ns++] = freq[i];

    for (int i = 0; i < ns - 1; i++)
        for (int j = i + 1; j < ns; j++)
            if (sizes[j] > sizes[i]) { int t = sizes[i]; sizes[i] = sizes[j]; sizes[j] = t; }

    printf("%lld\n", (long long)sizes[0] * sizes[1] * sizes[2]);
}


// Main Execution
int main(void) {
    FILE *f = fopen("input_8.txt", "r");
    if (!f) { perror("input_8.txt"); return 1; }

    n = 0;
    while (fscanf(f, "%d,%d,%d", &px[n], &py[n], &pz[n]) == 3) n++;
    fclose(f);

    long long num_pairs = (long long)n * (n - 1) / 2;
    elist = malloc(num_pairs * sizeof(edge));
    if (!elist) { fprintf(stderr, "OOM\n"); return 1; }

    kruskalAlgo();
    print();

    free(elist);
    return 0;
}
