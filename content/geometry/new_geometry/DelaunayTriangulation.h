/**
 * Author: Mattias de Zalenski
 * Date: Unknown
 * Source: Geometry in C
 * Description: Computes the Delaunay triangulation of a set of points.
 *  Each circumcircle contains none of the input points.
 *  If any three points are collinear or any four are on the same circle, behavior is undefined.
 * Time: O(n^2)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"
#include "Hull3D.h"

template<class P, class F>
void delaunay(vector<P>& ps, F trifun) {
	if (sz(ps) == 3) { int d = (det(ps[0], ps[1], ps[2]) < 0);
		trifun(0,1+d,2-d); }
	vector<P3> p3;
	for (P p : ps) p3.emplace_back(p.x, p.y, dot(p,p));
	if (sz(ps) > 3) for(auto t:hull3d(p3)) if (det(p3[t.b]-p3[t.a],
			p3[t.c]-p3[t.a]).z < 0)
		trifun(t.a, t.c, t.b);
}
