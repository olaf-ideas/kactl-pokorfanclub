/**
 * Author: Krzysztof Potępa
 * Date: 2022-10-27
 * License: ???
 * Source: ???
 * Description: Computes Minkowski sum of two convex polygons in ccw order.
 * Vertices are required to be in ccw order.
 * Time: O(n+m)
 * Status: Stress-tested
 */

#pragma once

#include "Point.h"
#include "Angle.h"

P edgeSeq(vector<P> p, vector<P>& edges) {
	int i = 0, n = sz(p);
	rep(j, n) if (tie(p[i].y, p[i].x) > tie(p[j].y, p[j].x)) i = j;
	rep(j, n) edges.pb(p[(i+j+1)%n] - p[(i+j)%n]);
	return p[i];
}

vector<P> hullSum(vector<P> A, vector<P> B) {
	vector<P> sum, e1, e2, es(sz(A) + sz(B));
	P pivot = edgeSeq(A, e1) + edgeSeq(B, e2);
	merge(all(e1), all(e2), es.begin(), [&](P a, P b){
		return Angle(a.x, a.y) < Angle(b.x,b.y);
	});
	sum.pb(pivot);
	for(auto e: es) sum.pb(sum.back() + e);
	sum.pop_back();
	return sum; //can have collinear vertices!
}
