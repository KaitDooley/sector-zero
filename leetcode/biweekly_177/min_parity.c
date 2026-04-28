typedef struct {
    int val;
    int pos;
} Pair;

int cmp(const void *a, const void *b) {
    return ((Pair*)a)->val - ((Pair*)b)->val;
}

void solve(int *nums, int n, int start_even, int *out_ops, long long *out_range) {
    int ops = 0;
    // Each position has 1 or 2 candidates
    // Max 2*n pairs
    Pair *all_vals = (Pair*)malloc(2 * n * sizeof(Pair));
    int total = 0;

    for (int i = 0; i < n; i++) {
        int expected_even = (start_even) ? (i % 2 == 0) : (i % 2 != 0);
        int current_even = (nums[i] % 2 == 0);
        // handle negative: -3 % 2 == -1 in C
        if (nums[i] < 0) current_even = (nums[i] % 2 == 0) ? 1 : 0;
        // simpler: use absolute parity
        current_even = ((nums[i] & 1) == 0);

        if (current_even == expected_even) {
            all_vals[total].val = nums[i];
            all_vals[total].pos = i;
            total++;
        } else {
            ops++;
            all_vals[total].val = nums[i] - 1;
            all_vals[total].pos = i;
            total++;
            all_vals[total].val = nums[i] + 1;
            all_vals[total].pos = i;
            total++;
        }
    }

    qsort(all_vals, total, sizeof(Pair), cmp);

    int *count = (int*)calloc(n, sizeof(int));
    int covered = 0;
    long long best = LLONG_MAX;
    int left = 0;

    for (int right = 0; right < total; right++) {
        int i = all_vals[right].pos;
        if (count[i] == 0) covered++;
        count[i]++;

        while (covered == n) {
            long long range = (long long)all_vals[right].val - all_vals[left].val;
            if (range < best) best = range;

            int li = all_vals[left].pos;
            count[li]--;
            if (count[li] == 0) covered--;
            left++;
        }
    }

    free(all_vals);
    free(count);

    *out_ops = ops;
    *out_range = best;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* makeParityAlternating(int* nums, int numsSize, int* returnSize) {
    *returnSize = 2;
    int *ans = (int*)malloc(2 * sizeof(int));

    if (numsSize == 1) {
        ans[0] = 0;
        ans[1] = 0;
        return ans;
    }

    int o1, o2;
    long long r1, r2;

    solve(nums, numsSize, 1, &o1, &r1);
    solve(nums, numsSize, 0, &o2, &r2);

    if (o1 < o2) {
        ans[0] = o1;
        ans[1] = (int)r1;
    } else if (o2 < o1) {
        ans[0] = o2;
        ans[1] = (int)r2;
    } else {
        ans[0] = o1;
        ans[1] = (int)(r1 < r2 ? r1 : r2);
    }

    return ans;
}
