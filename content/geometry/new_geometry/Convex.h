/**
 * Author: Olaf Surgut
 * Date: 2025-07-13
 * License: CC0
 * Source: old kactl, kobor & https://github.com/spaghetti-source/algorithm/blob/master/geometry/_geom.cc
 * Description: Convex polygon primitives
 * Status: not tested
 */

#include "Segment.h"

vector<P> convexHull(vector<P> pts) {
	sort(all(pts),cmp);
	if (sz(pts) <= 2) return pts;
	vector<P> h;
	rep(i,0,2) {
		int s = sz(h)+2;
		for (P p:pts){
			while (sz(h)>=s&&side(end(h)[-2],end(h)[-1],p)<=0)
				h.pop_back();
			h.pb(p);}
		h.pop_back(), reverse(all(pts));
	}
	return h;}
bool insideConvex(vector<P> const& q, P p) {
	if (sz(q) <= 2)
		return onSegment(q[0],q.back(),p);
	if (side(q[0],q[1],p) < 0 ||
        side(q.back(),q[0],p) < 0)
        return false;
	int l=1,r=sz(q)-1;
	while (r - l > 1) {
		int m=(l+r)>>1;
		(side(q[0],q[m],p)>=0?l:r)=m;
	}
    return side(q[l],q[r],p)>=0;}
int tangent(vector<P> const& q, P p, int dir, int l, int r) {
	while (r - l > 1) {
		int m = (l + r) >> 1;
		int pv = side(p,q[m],q[m-1])!=-dir;
		int nt = side(p,q[m],q[m+1])!=-dir;
        if (pv && nt) return m;
        if (!pv && !nt) {
			int i=tangent(q,p,dir,l,m);
			int j=tangent(q,p,dir,m,r);
			return side(p,q[i],q[j])==dir?i:j;}
		if (!pv) {
			if (side(p,q[m],q[l])==dir||side(p,q[l],q[r])==dir) r=m;
			else l = m;}
		if (!nt) {
			if (side(p,q[m],q[r])==dir||side(p,q[r],q[l])==dir) l=m;
			else r = m;}
	}
	return side(p,q[l],q[r])==dir?l:r;}
pii tangents(vector<P> const& q, P p) {
	return {tangent(q,p,-1,0,sz(q)-1),
            tangent(q,p,+1,0,sz(q)-1)};}
			
array<P, 2> hullDiameter(vector<P> S) {
	int n = sz(S), j = (n >= 2);
	pair<D, array<P, 2>> res({0, {S[0], S[0]}});
	rep(i,0,j)
		for (;; j = (j + 1) % n) {
			res = max(res, {len2(S[i] - S[j]), {S[i], S[j]}});
			if (det(S[(j + 1) % n] - S[j], S[i + 1] - S[i]) >= 0)
				break;
		}
	return res.second;
}
vector<P> minkowski(vector<P> a, vector<P> b) {
	rotate(a.begin(), min_element(all(a)), a.end());
	rotate(b.begin(), min_element(all(b)), b.end());
	rep(i,0,2) a.pb(a[i]), b.pb(b[i]);
	vector<P> res;
	for(int i = 0, j = 0; i < sz(a) - 2 || j < sz(b) - 2; ) {
		res.pb(a[i] + b[j]);
		auto cross = sgn(det(a[i + 1] - a[i], b[j + 1] - b[j]));
		if(cross >= 0 && i < sz(a)) i++;
		if(cross <= 0 && j < sz(b)) j++;
	}
	return res;
}