
/**
 * Author: Krzysztof Potepa
 * Date: N/A
 * License: N/A
 * Description: All-substrings common sequences algorithm.
 * Given strings A and B, algorithm computes:
 * $C(i,j,k) = |LCS(A[:i), B[j:k))|$ in compressed form;
 * To describe the compression, note that:
 * 1. $C(i,j,k-1) <= C(i,j,k) <= C(i,j,k-1)+1$
 * 2. If $j < k$ and $C(i,j,k) = C(i,j,k-1)+1$,
 *  then $C(i,j+1,k) = C(i,j+1,k-1)+1$
 * 3. If $j >= k$, then $C(i,j,k) = 0$
 * This allows us to store just the following:
 * $ih(i,k)$ = min j s.t. $C(i,j,k-1) < C(i,j,k)$
 * Time: O(nm)
 * Status: N/A
 */

#pragma once

struct ALCS {
	string A, B;
	vector<vi> ih;

	// Precompute compressed matrix; time: O(nm)
	ALCS(string s, string t) : A(s), B(t) {
		int n = sz(A), m = sz(B);
		ih.resize(n + 1, vi(m + 1));
		iota(all(ih[0]), 0);
		rep(l, 1, n + 1) {
			int iv = 0;
			rep(j, 1, m + 1) {
				if (A[l - 1] != B[j - 1]) {
					ih[l][j] = max(ih[l - 1][j], iv);
					iv = min(ih[l - 1][j], iv);
				} else {
					ih[l][j] = iv;
					iv = ih[l - 1][j];
				}
			}
		}
	}

	// Compute |LCS(A[:i), B[j:k))|; time: O(k-j)
	// Note: You can precompute data structure
	// to answer these queries in O(log n)
	// or compute all answers for fixed `i`.
	int operator()(int i, int j, int k) {
		int ret = 0;
		rep(q, j, k) ret += (ih[i][q + 1] <= j);
		return ret;
	}

	// Compute subsequence LCS(A[:i), B[j:k));
	// time: O(k-j)
	string recover(int i, int j, int k) {
		string ret;
		while (i > 0 && j < k) {
			if (ih[i][k--] <= j) {
				ret.pb(B[k]);
				while (A[--i] != B[k])
					;
			}
		}
		reverse(all(ret));
		return ret;
	}

	// Compute LCS'es of given prefix of A,
	// and all prefixes of given suffix of B.
	// Returns vector L of length |B|+1 s.t.
	// L[k] = |LCS(A[:i), B[j:k))|; time: O(|B|)
	vi row(int i, int j) {
		vi ret(sz(B) + 1);
		rep(k, j + 1, sz(ret)) ret[k] = ret[k - 1] + (ih[i][k] <= j);
		return ret;
	}
};
