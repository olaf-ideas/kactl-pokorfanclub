/**
 * Author: Krzysztof Potępa
 * Date: N/A
 * License: N/A
 * Description: Compute Lyndon factorization for s; Word is simple iff it's stricly smaller
 * than any of it's nontrivial suffixes. Lyndon factorization is division of string
 * into non-increasing simple words. It is unique.
 * Time: O(n)
 * Status: N/A
 */
#pragma once

vector<string> duval(const string &s) {
	int n = sz(s), i = 0;
	vector<string> ret;
	while (i < n) {
		int j = i + 1, k = i;
		while (j < n && s[k] <= s[j])
			k = (s[k] < s[j] ? i : k + 1), j++;
		while (i <= k)
			ret.pb(s.substr(i, j - k)), i += j - k;
	}
	return ret;
}
