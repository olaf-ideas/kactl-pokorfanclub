/**
 * Author: UW, golfed by Kacper Topolski
 * Date: 2024-08-11
 * License: N/A
 * Source: https://github.com/tonowak/acmlib/blob/master/code/geo/convex-hull-online/main.cpp
 * Description: Allows online point insertion. If exists, left vertical segment is included; right one is excluded.
 * To get a lower hull add (-x, -y) instead of (x, y).
 * Time: amortized O(\log n) per add
 * Status: stress-tested
*/
#pragma once

#include "Point.h"

using P = Point<ll>;
struct UpperHull : set<P> {
	bool rm(auto it) {
		if (it==begin() || it==end() || next(it)==end() ||
		    it->cross(*prev(it), *next(it)) > 0)
			return false;
		erase(it); return true;
	}
	bool add(P p) { // true iff added
		auto [it, ok] = emplace(p);
		if (!ok || rm(it)) return false;
		while (rm(next(it)));
		while (it != begin() && rm(prev(it)));
		return true;
	}
};
