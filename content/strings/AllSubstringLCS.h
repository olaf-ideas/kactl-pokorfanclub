/**
 * Author: copy kobor copy
 * Date: 2023-12-17
 * Description: Computes LCS of s and t[i, j]
 * Time: $O(NM)$
 */
#pragma once

const int N = 2002;
int f[N][N], g[N][N], ans[N][N];
void all_substring_lcs(string s, string t) {
	int n = SZ(s), m = SZ(t);
	s = "#" + s; t = "#" + t;
	rep(i, 1, m) f[0][i] = i;
	rep(i, 1, n) rep(j, 1, m) {
		if(s[i] == t[j]) {
			f[i][j] = g[i][j - 1]; g[i][j] = f[i - 1][j];
		} else {
			f[i][j] = max(f[i - 1][j], g[i][j - 1]);
			g[i][j] = min(g[i][j - 1], f[i - 1][j]);
		}
	}
	rep(i, 1, m) for(int j = i, a = 0; j <= m; ++j) {
		a += i > f[n][j]; ans[i][j] = a; }
}
