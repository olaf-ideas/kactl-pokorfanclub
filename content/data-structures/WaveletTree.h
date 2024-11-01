/**
 * Author: Czajnik
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Wavelet tree. Supports fast kth order statistics on ranges (no updates).
 * Time: O(\log N)
 * Status: stress-tested
 */

#pragma once

struct WaveletTree {
	vector<vi> seq, left;
	int len;
	WaveletTree() {}
	// time and space: O((n+maxVal) log maxVal)
	// Values are expected to be in [0;maxVal).
	WaveletTree(const vi& elems, int maxVal) {
		for (len = 1; len < maxVal; len *= 2);
		seq.resize(len*2); left.resize(len*2);
		seq[1] = elems; build(1, 0, len);
	}
	void build(int i, int b, int e) {
		if (i >= len) return;
		int m = (b+e) / 2;
		left[i].pb(0);
		for(auto &x : seq[i]) {
			left[i].pb(left[i].back() + (x < m));
			seq[i*2 + (x >= m)].pb(x);
		}
		build(i*2, b, m); build(i*2+1, m, e);
	} // Find k-th (0 indexed) smallest element in [begin;end)
	int kth(int begin, int end, int k, int i=1) {
		if (i >= len) return seq[i][0];
		int x = left[i][begin], y = left[i][end];
		if (k < y-x) return kth(x, y, k, i*2);
		return kth(begin-x, end-y, k-y+x, i*2+1);
	} // Count number of elements >= vb and < ve
	int count(int begin, int end, int vb, int ve, int i = 1, int b = 0, int e = -1) {
		if (e < 0) e = len;
		if (b >= ve || vb >= e) return 0;
		if (b >= vb && e <= ve) return end-begin;
		int m = (b+e) / 2; int x = left[i][begin], y = left[i][end];
		return count(x, y, vb, ve, i*2, b, m) + count(begin-x, end-y, vb, ve, i*2+1,m,e);
	}
};