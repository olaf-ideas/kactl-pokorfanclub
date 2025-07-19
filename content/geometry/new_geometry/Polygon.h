/**
 * Author: Olaf Surgut
 * Date: 2025-07-13
 * License: CC0
 * Source: old kactl, kobor & https://github.com/spaghetti-source/algorithm/blob/master/geometry/_geom.cc
 * Description: Polygon primitives
 * Status: not tested
 */

#include "Point.h"
#include "Line.h"
#include "Segment.h"

bool inPolygon(vector<P> const& p, P a, bool strict=true) {
    int cnt = 0, n = sz(p);
    rep(i,0,n) {
        P q = p[(i+1)%n];
        if (onSegment(p[i], q, a)) return !strict;
        cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * det(a,p[i],q) > 0;
    }
    return cnt;
}

P polygonCenter(vector<P> const& p) {
    P res{0, 0}; D area = 0;
    for (int i = 0, j = sz(p) - 1; i < sz(p); j = i++) {
        res = res+(p[i]+p[j])*det(p[i],p[j]);
        area += det(v[i], v[j]);
    }
    return res / area / 3;
}

vector<P> polygonCut(vector<P> const& p, P a, P b) {
    vector<P> res;
    for (int i = 0, j = sz(p) - 1; i < sz(p); j = i++) {
        bool side = det(a, b, p[i]) < 0;
        if (side != (det(a, b, p[j]) < 0))
            res.pb(intersect(a, b, p[i], p[j]));
        if (side)
            res.pb(p[i]);
    }
    return res;
}

D rat(P a, P b) { return sgn(b.x) ? a.x/b.x : a.y/b.y; }
D polyUnion(vector<vector<P>> const& p) {
	D ret = 0;
	rep(i,0,sz(poly)) rep(v,0,sz(p[i])) {
		P A = p[i][v], B = p[i][(v + 1) % sz(p[i])];
		vector<pair<D, int>> segs = {{0, 0}, {1, 0}};
		rep(j,0,sz(p)) if (i != j) {
			rep(u,0,sz(p[j])) {
				P C = p[j][u], D = p[j][(u + 1) % sz(p[j])];
				int sc = sideOf(A, B, C), sd = sideOf(A, B, D);
				if (sc != sd) {
					D sa = det(C, D, A), sb = det(C, D, B);
					if (min(sc, sd) < 0)
						segs.eb(sa / (sa - sb), sgn(sc - sd));
				} else if (!sc && !sd && j<i && sgn(dot(B-A, D-C))>0){
					segs.eb(rat(C - A, B - A), 1);
					segs.eb(rat(D - A, B - A), -1);
				}
			}
		}
		sort(all(segs));
		for (auto& s : segs) s.st = fmin(fmax(s.st, 0.0), 1.0);
		D sum = 0;
		int cnt = segs[0].nd;
		rep(j,1,sz(segs)) {
			if (!cnt) sum += segs[j].st - segs[j - 1].st;
			cnt += segs[j].nd;
		}
		ret += det(A, B) * sum;
	}
	return ret / 2;
}

D triangulate(vector<P> const& p) {
    int n = p.size();
    vi next(n);
    rep(i,0,n-1) next[i] = i+1;
    auto is_ear = [&](int i, int j, int k) {
        if (sgn(det(p[i], p[j], p[k])) <= 0) return false;
        for (int l = next[k]; l != i; l = next[l])
            if (sgn(det(p[l], p[i], p[j])) >= 0 && 
                sgn(det(p[l], p[j], p[k])) >= 0 && 
                sgn(det(p[l], p[k], p[i])) >= 0) return false;
        return true;
    };
    D area = 0;
    for (int i = 0; next[next[i]] != i; ) {
        if (is_ear(i, next[i], next[next[i]])) {
            D += abs(det(p[i], p[next[i]], p[next[next[i]]])) / 2;
            next[i] = next[next[i]];
        } else i = next[i];
    }
    return area;
}
