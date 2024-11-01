/**
 * Author: KokiYmgch
 * Date: a lot of years ago
 * License: N / A
 * Source: https://codeforces.com/blog/entry/57496
 * Description: Calculates chromatic number of a graph represented by a vector of bitmasks. Self loops are not allowed.
 * Usage: chromaticNumber({6, 5, 3}) // 3-clique
 * Time: O(2^n n)
 * Status: Stress-tested
 * Details: This code does not compute the chromatic polynomial (as claimed by the cf blog). It computes the number of k-tuples
 * where each member is an independent set, and every element is included in at least one of them (possibly more than one).
 */
#pragma once

const int MOD = 1000500103; // big prime
int chromaticNumber(vi g) {
	int n = sz(g);
	if (!n) return 0;
	vi ind(1 << n, 1), s(1 << n);
	rep(i, 1 << n) s[i] = __popcount(i) & 1 ? -1 : 1;
	fwd(i, 1, 1 << n) {
		int ctz = __builtin_ctz(i);
		ind[i] = ind[i - (1 << ctz)] + ind[(i - (1 << ctz)) & ~g[ctz]];
		if (ind[i] >= MOD) ind[i] -= MOD;
	}
	fwd(k, 1, n) {
		ll sum = 0;
		rep(i, 1 << n) {
			s[i] = int((ll)s[i] * ind[i] % MOD);
			sum += s[i];
		}
		if (sum % MOD) return k;
	}
	return n; }
