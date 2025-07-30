/**
 * Author: kobor
 * Date: 2024-04-03
 * License: CC0
 * Source: bicsi's github
 * Description: Data structure that dynamically keeps track
 * of the intersection of half-planes.
 * Time: amortized O(\log n)
 * Status: somewhat tested on few tasks
 */
#pragma once

#include "new_geometry/Point.h"

int hf(P a) { return a.y < 0 || (a.y == 0 && a.x < 0); }
struct polarCmp {
	bool operator()(const P &a, const P &b) const {
		return hf(a) == hf(b) ? det(a, b) > 0 : hf(a) < hf(b);
	}
};

struct HalfplaneSet : map<P, P, polarCmp> {
	D INF = 1e6, area = 8 * INF * INF;
	HalfplaneSet() {
		P p(-INF, -INF), d(1, 0);
		rep(k, 0, 4) {
			insert({d, p}); p = p + d * 2 * INF; d = rot90(d); }
	}
	auto fix(auto it) { return it == end() ? begin() : it; }
	auto getNext(auto it) { return fix(next(it)); }
	auto getPrev(auto it) {
		return it == begin() ? prev(end()) : prev(it); }
	auto uSide(auto it, int change) {
		area += change * det(it->nd, getNext(it)->nd); }
	auto del(auto it) {
		uSide(getPrev(it), -1), uSide(it, -1);
		it = fix(erase(it));
		if(size()) uSide(getPrev(it), 1);
		return it;
	}
	void add(P s, P e) {
		auto eval = [&](auto it) { return sgn(det(s, e, it->nd)); };
		auto ii = [&](auto it) {
			return intersect(s, e, it->nd, it->st + it->nd); };
		auto it = fix(lower_bound(e - s));
		if(empty() || eval(it) >= 0) return;
		while(size() && eval(getPrev(it)) < 0) del(getPrev(it));
		while(size() && eval(getNext(it)) < 0) it = del(it);
		if(empty()) return;
		if(eval(getNext(it)) > 0) {
			uSide(getPrev(it), -1), uSide(it, -1);
			it->nd = ii(it);
			uSide(getPrev(it), 1), uSide(it, 1);
		}
		else it = del(it);
		it = getPrev(it);
		uSide(it, -1); insert(it, {e - s, ii(it)});
		uSide(it, 1), uSide(getNext(it), 1);
		if(eval(it) == 0) del(it);
	}
	D maxDot(P a) {
		return dot(a, fix(lower_bound(rot90(a)))->nd); }
	D getArea() { return area / 2; }
};