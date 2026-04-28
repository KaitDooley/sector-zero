#!/usr/bin/env python3

class Solution:
    def sumOfNumbers(self, l: int, r: int, k: int) -> int:
        MOD = 10**9 + 7
        m = r - l + 1                          # digits available
        digit_sum = m * (l + r) // 2 % MOD    # sum of digits l..r

        def geo_sum(base, n):
            """1 + base + base^2 + ... + base^(n-1)  [recursive fast doubling]"""
            if n == 0: return 0
            if n == 1: return 1
            half = geo_sum(base, n // 2)
            result = half * (1 + pow(base, n // 2, MOD)) % MOD
            if n % 2 == 1:
                result = (result + pow(base, n - 1, MOD)) % MOD
            return result

        return digit_sum * pow(m, k - 1, MOD) % MOD * geo_sum(10, k) % MOD
