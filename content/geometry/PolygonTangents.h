/**
 * Author: Oleksandr Bacherikov, kobor
 * Date: 2023-12-03
 * License: Boost Software License
 * Source: https://github.com/AlCash07/ACTL/blob/main/include/actl/geometry/algorithm/tangents/point_convex_polygon.hpp
 * Description: Polygon tangents from a given point.
 *  The polygon must be ccw and have no collinear points.
 *  Returns a pair of indices of the given polygon.
 *  Should work for a point on border (for a point being polygon vertex returns previous and next one).
 * Time: O(\log n)
 * Status: tested on one task
 */
#pragma once

#include "Point.h"

#define pdir(i) (ph ? p - poly[(i)%n] : poly[(i)%n] - p)
#define cmp(i,j) sgn(pdir(i).cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
template <class P>
array<int, 2> polygonTangents(vector<P>& poly, P p) {
	auto bs = [&](int ph) {
		int n = sz(poly), lo = 0, hi = n;
		if(extr(0)) return 0;
		while(lo + 1 < hi) {
			int m = (lo + hi) / 2;
			if(extr(m)) return m;
			int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
			(ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi:lo) = m;
		}
		return lo;
	};
	array<int, 2> res = {bs(0), bs(1)};
	if(res[0] == res[1]) res[0] = (res[0] + 1) % SZ(poly);
	if(poly[res[0]] == p) res[0] = (res[0] + 1) % SZ(poly);
	return res;
}