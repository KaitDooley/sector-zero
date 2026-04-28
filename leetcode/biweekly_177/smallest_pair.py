#!/usr/bin/env python3

class Solution:
    def minDistinctFreqPair(self, nums: list[int]) -> list[int]:
        if len(nums) <= 1:
            return [-1, -1]
        nums.sort()
        freq_map = defaultdict(int)

        for num in nums:
            freq_map[num] += 1

        for a, b in combinations(freq_map.keys(), 2):
            if freq_map[a] != freq_map[b]:
                return [a, b]

        return [-1, -1]
