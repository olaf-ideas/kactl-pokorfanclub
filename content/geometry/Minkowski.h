/**
 * Author: kobor
 * Date: 2024-04-21
 * Source: https://cp-algorithms.com/geometry/minkowski.html
 * Description: Computes the Minkowski sum of two convex polygons.
 *  Distance between two convex polygons can be computed by finding the closest edge of P - Q to the origin. 
 * Time: O(N)
 * Status: tested on a few tasks
 */
#pragma once

#include "Point.h"

template<class P>
vector<P> minkowski(vector<P> a, vector<P> b) {
	rotate(a.begin(), min_element(all(a)), a.end());
	rotate(b.begin(), min_element(all(b)), b.end());
	FOR(i, 0, 2) a.pb(a[i]), b.pb(b[i]);
	vector<P> res;
	for(int i = 0, j = 0; i < SZ(a) - 2 || j < SZ(b) - 2; ) {
		res.pb(a[i] + b[j]);
		auto cross = (a[i + 1] - a[i]).cross(b[j + 1] - b[j]);
		if(cross >= 0 && i < SZ(a)) i++;
		if(cross <= 0 && j < SZ(b)) j++;
	}
	return res;
}