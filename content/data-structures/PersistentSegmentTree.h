/**
 * Author: kobor
 * Date: 2024-07-22
 * License: CC0
 * Source: own work
 * Description:
 * 	Persistent structures use a lot of memory in general,
 * 	so remember to optimise the code whenever possible.
 * 	Push function is responsible for creating copies of children,
 * 	so whenever we enter a vertex (either add or query) it's already
 * 	a fresh copy.
 * 	When there is no lazy, it's better to modify this approach,
 * 	and only create a vertex when we really visit it, so we can save memory.
 * Time: $O(\log N)$ per operation
 * Status: somewhat tested
 */
#pragma once

struct PersistentTree {
	using T = ll;	// persistency needs a lot of memory
	struct Node {	// so make sure to make it efficient
		int ch[2] = {-1, -1}; T sum, mini, add;
		Node() : sum(0), mini(0), add(0) {}	// start / neutral
		Node(T val) : sum(val), mini(val), add(0) {}
		void apply(T val, int len) {
			sum += val * len; mini += val; add += val;
		}
		void pull(Node &l, Node &r) {
			sum = l.sum + r.sum; mini = min(l.mini, r.mini);
		}
	};
	vector<Node> t; int max_n;
	PersistentTree(int _max_n) : max_n(_max_n) {}
	PersistentTree(vector<T> vals) : max_n(SZ(vals) - 1) {
		function<int(int, int)> build = [&](int l, int r) {
			if(l == r) { t.pb(Node(vals[l])); return SZ(t)-1; }
			int mid = (l + r) / 2; Node a;
			a.ch[0] = build(l, mid), a.ch[1] = build(mid + 1, r);
			a.pull(t[a.ch[0]], t[a.ch[1]]);
			t.pb(a); return SZ(t) - 1;
		};
		build(0, max_n);
	}
	int copy(int v) { t.pb(~v ? t[v]:Node()); return SZ(t)-1; }
	void push(int v, int len) {
		FOR(i, 0, 2) {
			t[v].ch[i] = copy(t[v].ch[i]);
			t[t[v].ch[i]].apply(t[v].add, len / 2);
		}
		t[v].add = 0;
	}
	void add(int v, int l, int r, T val, int le, int re) {
		if(re < l || r < le) return;
		if(l <= le && re <= r) return t[v].apply(val, re-le + 1);
		push(v, re - le + 1); int mid = (le + re) / 2;
		add(t[v].ch[0], l, r, val, le, mid);
		add(t[v].ch[1], l, r, val, mid + 1, re);
		t[v].pull(t[t[v].ch[0]], t[t[v].ch[1]]);
	}
	Node query(int v, int l, int r, int le, int re) {
		if(re < l || r < le) return Node();
		if(l <= le && re <= r) return t[v];
		push(v, re - le + 1); int mid = (le + re) / 2;
		Node a = query(t[v].ch[0], l, r, le, mid);
		Node b = query(t[v].ch[1], l, r, mid + 1, re);
		Node res; res.pull(a, b); return res;
	}
	void add(int &v, int l, int r, T val) {
		v = copy(v); add(v, l, r, val, 0, max_n);
	}
	Node query(int v, int l, int r) {
		int sz = SZ(t);
		v = copy(v); Node res = query(v, l, r, 0, max_n);
		t.resize(sz); return res;
	}
};
