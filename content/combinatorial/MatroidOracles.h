/**
 * Author: kobor
 * Date: 2024-07-17
 * License: CC0
 * Description: An oracle has 3 functions:
 * 	check(int x): returns if current matroid can add x without becoming dependent;
 * 	add(int x): adds an element to the matroid (guaranteed to never make it dependent);
 * 	clear(): sets the matroid to the empty matroid.
 * Time: O(\log N)
 * Status: Tested on SWERC 2011D, Pick Your Own Nim
 */
#pragma once

struct ColorMat {
	vi clr, bound, cnt; int max_bound = 0, offset = 0;
	ColorMat(vi _clr, vi _bound) : clr(_clr), bound(_bound) {
		cnt.resize(SZ(bound));
		if(SZ(bound)) max_bound = *max_element(all(bound));
	}
	void fix(int x) { cnt[clr[x]] = max(cnt[clr[x]], offset); }
	bool check(int x) {
		fix(x); return cnt[clr[x]] - offset < bound[clr[x]];
	}
	void add(int x) { fix(x); cnt[clr[x]]++; }
	void clear() { offset += max_bound; }
};

struct GraphicMat {	// use normal UF to reduce memory
	vector<pii> edg; UF uf; vi vis;
	GraphicMat(vector<pii> _edg) : edg(_edg), uf(0) {
		int max_n = -1;
		for(auto &[x, y]: edg) max_n = max({max_n, x, y});
		uf = UF(max_n + 1);
	}
	bool check(int x) {
		return uf.find(edg[x].st) != uf.find(edg[x].nd);
	}
	void add(int x) { uf.join(edg[x].st,edg[x].nd); vis.pb(x); }
	void clear() {
		for(int x: vis) uf.e[edg[x].st] = uf.e[edg[x].nd] = -1;
		vis.clear();
	}
};

struct LinearMat {
	vector<ll> vals; set<ll, greater<ll>> basis, start;
	LinearMat(vector<ll> _vals, vector<ll> _s) : vals(_vals) {
		for(ll x: _s) basis.insert(red(x));
		start = basis;
	}
	ll red(ll x) { for(ll y: basis) x = min(x, x^y); return x; }
	bool check(int x) { return red(vals[x]); }
	void add(int x) { basis.insert(red(vals[x])); }
	void clear() { basis = start; }
};
