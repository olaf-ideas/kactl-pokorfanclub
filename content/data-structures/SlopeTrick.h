/**
 * Author: kobor
 * Date: 2024-09-12
 * Source: https://ei1333.github.io/library/structure/others/slope-trick.hpp
 * Description: Linear functions container. Not tested!
 * Time: $O(\log N)$ per operation
 * Status: not tested!
 */
#pragma once

struct SlopeTrick {
	const ll INF = 3e18;
	ll min_f, add_l, add_r;
	priority_queue<ll> L;
	priority_queue<ll, vector<ll>, greater<>> R;
	void push_R(ll a) { R.push(a - add_r); }
	ll top_R() const { return SZ(R) ? R.top() + add_r : INF; }
	ll pop_R() {
		ll val = top_R(); if(SZ(R)) R.pop();
		return val;
	}
	void push_L(ll a) { L.push(a - add_l); }
	ll top_L() const { return SZ(L) ? L.top() + add_l : -INF; }
	ll pop_L() {
		ll val = top_L(); if(SZ(L)) L.pop();
		return val;
	}
	int size() { return SZ(L) + SZ(R); }
	// use only functions below!
	SlopeTrick() : min_f(0), add_l(0), add_r(0) {}
	struct Query { ll lx, rx, min_f; };
	// return 		min f(x)
	Query query() const { return Query(top_L(),top_R(),min_f); }
	// 				f(x) += a
	void add_all(ll a) { min_f += a; }
	// add \_		f(x) += max(a - x, 0)
	void add_a_minus_x(ll a) {
		min_f += max(0ll, a - top_R()); push_R(a); push_L(pop_R());
	}
	// add _/		f(x) += max(x - a, 0)
	void add_x_minus_a(ll a) {
		min_f += max(0ll, top_L() - a); push_L(a); push_R(pop_L());
	}
	// add \/		f(x) += abs(x - a)
	void add_abs(ll a) { add_a_minus_x(a); add_x_minus_a(a); }
	// \/ -> \_		f_{new} (x) = min f(y) (y <= x)
	void clear_right() { while(SZ(R)) R.pop(); }
	// \/ -> _/		f_{new} (x) = min f(y) (y >= x)
	void clear_left() { while(SZ(L)) L.pop(); }
	// \/ -> \_/	f_{new} (x) = min f(y) (x-b <= y <= x-a)
	void shift(ll a, ll b) {
		assert(a <= b); add_l += a; add_r += b;
	}
	// \/. -> .\/	f_{new} (x) = f(x - a)
	void shift(ll a) { shift(a, a); }
	// L, R is destroyed
	ll get(ll x) {
		ll ret = min_f;
		while(SZ(L)) ret += max(0ll, pop_L() - x);
		while(SZ(R)) ret += max(0ll, x - pop_R());
		return ret;
	}
	void merge(SlopeTrick &o) {
		if(SZ(o) > size()) {
			swap(o.L, L); swap(o.R, R);
			swap(o.add_l, add_l); swap(o.add_r, add_r);
			swap(o.min_f, min_f);
		}
		while(SZ(o.R)) add_x_minus_a(o.pop_R());
		while(SZ(o.L)) add_a_minus_x(o.pop_L());
		min_f += o.min_f;
	}
};
