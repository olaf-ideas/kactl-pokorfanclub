/**
 * Author: kobor
 * Date: 2024-07-30
 * License: CC0
 * Source: https://judge.yosupo.jp/submission/234937
 * Description: Fully dynamic upper / lower convex hull, can be used for computing onion layers.
 *  All points should be known in advance.
 * 	Points on the edges are included in the hull.
 * 	Return indices are the same as in the input.
 * Time: O(\log^2 n), as fast as other O(\log n) hulls
 * Status: tested on yosupo
 */
#pragma once

#include "Point.h"

template<class T>
struct DynHull {
	using P = Point<T>;
	struct Node { int l, r; }; vector<P> ps;
	int n; vi in, id; int s; vector<Node> t; vector<T> m;
	DynHull(vector<P> _ps, bool lower = 0, int start = -1)
		 : ps(_ps), n(sz(ps)), in(n), id(n) {
		if(start == -1) start = n;
		s = 1; while(s < n) s *= 2;
		t.resize(s * 2, {-1, -1}); m.resize(s);
		vector<pair<P, int>> pts;
		rep(i, n) pts.pb({ps[i] * (lower ? -1 : 1), i});
		sort(all(pts));
		rep(i, n) {
			tie(ps[i], id[i]) = pts[i]; in[id[i]] = i;
			int p = i + s; while((p & 1) ^ 1) p >>= 1;
			m[p >> 1] = ps[i].x;
		}
		rep(i, start) t[s + in[i]] = {in[i], in[i]};
		for (int i = s - 1; i >= 1; i --) pull(i);
	}
	int go(int v) { 
		while(t[v].l < 0) v = v * 2 + t[v].l + 3;
		return v;
	}
	void pull(int v) {
		auto crossNegX = [](P a, P b, P c, P d, T x) {
			// change __int128 if using doubles!
			__int128 p = a.cross(b, c), q = b.cross(a, d);
			return p + q == 0 || (d.x - x) * p + (c.x - x) * q <= 0;
		};
		int p = v * 2, q = p + 1;
		if(t[p].l == -1 && t[q].l == -1) t[v] = {-1, -1};
		else if(t[p].l == -1) t[v] = {-2, -2};
		else if(t[q].l == -1) t[v] = {-3, -3};
		else {
			p = go(p), q = go(q);
			while(p < s || q < s) {
				auto [a, b] = t[p]; auto [c, d] = t[q];
				if(a != b && ps[a].cross(ps[b], ps[c]) > 0) {
					p = go(p * 2); }
				else if(c != d && ps[b].cross(ps[c], ps[d]) > 0) {
					q = go(q * 2 + 1); }
				else if(a == b) q = go(q * 2);
				else if(c == d ||
					crossNegX(ps[a], ps[b], ps[c], ps[d], m[v])) {
					p = go(p * 2 + 1); }
				else q = go(q * 2);
			}
			t[v] = {p - s, q - s};
		}
	}
	void add(int i) {
		i = in[i]; int v = i + s; t[v] = {i, i};
		while(v >>= 1) pull(v);
	}
	void del(int i) {
		i = in[i]; int v = i + s; t[v] = {-1, -1};
		while(v >>= 1) {
			if(t[v].l < 0 || t[v].l == i || t[v].r == i) pull(v); }
	}
	void dfs(int v, int l, int r, vi &h) {
		if(v >= s) return h.pb(id[t[v].l]);
		if(l <= t[v].l) dfs(go(v * 2), l, min(t[v].l, r), h);
		if(t[v].r <= r) dfs(go(v * 2 + 1), max(t[v].r, l), r,  h);
	}
	vi hull() { 
		vi h; if(~t[1].l) dfs(go(1), 0, n - 1, h); return h;
	}
};