/**
 * Author: Olaf Surgut
 * Date: 2025-07-13
 * License: CC0
 * Source: old kactl, kobor & https://github.com/spaghetti-source/algorithm/blob/master/geometry/_geom.cc
 * Description: Circle primitives
 * Status: not tested
 */
#pragma once

#include "Point.h"
#include "Line.h"

const D pi = acos(-1);

vector<P> intersect(P a, D r, P b, D R) {
    if (sgn(dist2(a,b))==0) return assert(sgn(r-R)!=0), {};
    P v = rot90(b-a);
    D d2 = len2(v), sum = r+R, dif = r-R,
      p = (d2+r*r-R*R)/(d2*2), h2 = r*r-p*p*d2;
    if (sum*sum < d2 || dif*dif > d2) return {};
    P m = a+v*p, per = v * sqrt(fmax(0, h2)/d2);
    return {m+per, m-per};
}

D intersectArea(P a, D r, P b, D R) {
    if (r < R) swap(a, b), swap(r, R);
    auto A = [&](D r, D h) { return r*r*acos(h/r)-h*sqrt(r*r-h*h); };
    auto l = len(a-b), k = (l*l+r*r-R*R)/(2*l);
    if (sgn(l-r-R) >= 0) return 0;
    if (sgn(r-r+R) <= 0) return pi*R*R;
    if (sgn(l-r) >= 0) return A(r,k)+A(r,l-k);
    else return A(r,k)+pi*r*r-A(r,k-l);
}

D intersectArea(P c, D r, vector<P> poly) {
    auto arg = [&](P p, P q) { return atan2(det(p,q), dot(p,q)); };
    auto tri = [&](P p, P q) {
        P w = q-p;
        auto a = dot(w,p)/dot(w,w), b = (dot(p,p)-r*r)/dot(w,w);
        auto d = a*a-b;
        if (d <= 0) return arg(p,q)*r*r/2;
        auto s = fmax(0,-a-sqrt(d)), t = fmin(1, -a+sqrt(d));
        if (t < 0 || 1 <= s) return r*r*arg(p,q)/2;
        P u = p+s*w, v = p+t*w;
        return arg(p,u)*r*r/2+det(u,v)/2+arg(v,q)*r*r/2;
    };
    D res = 0;
    rep(i,0,sz(poly))
        res += tri(poly[i]-c, poly[(i+1)%sz(poly)]-c);
    return res;
}

vector<pair<P,P>> tangents(P a, D r, P b, D R) {
    P v = rot90(b-a);
    D dr = r-R, d2 = len2(v), h2 = d2-dr*dr;
    if (sgn(d2) == 0 || h2 < 0) return {};
    vector<pair<P,P>> res;
    for (D sign : {-1, +1}) {
        P v = (d*dr+v*sqrt(h2)*sign)/d2;
        res.pb({c1+v*r1, c2+v*r2});
    }
    if (h2==0) res.pop_back();
    return res;
}

vector<P> circleLine(P c, D r, P a, P b) {
    P ab = b-a, p = a+ab*dot(c-a,ab)/len2(ab);
    D s = det(a,b,c), h2 = r*r*-s*s/len2(ab);
    if (h2 < 0) return {};
    if (h2 == 0) return {p};
    P h = unit(ab) * sqrt(h2);
    return {p-h, p+h};
}

pair<P,D> circumCircle(P a, P b, P c) {
    P v = c-a, w = b-a;
    P o = a + rot90(v*len2(w)-w*len2(v))/det(v,w)/2;
    return {o,dist(a,o)}; 
}

pair<P, D> enclosingCircle(vector<P> p) {
	shuffle(all(p), mt19937(2137));
	P o = pts[0];
	D r = 0, EPS = 1 + 1e-8;
	rep(i,0,sz(p)) if (dist(o, p[i]) > r * EPS) {
		o = p[i], r = 0;
		rep(j,0,i) if (dist(o, p[j]) > r * EPS) {
			o = (p[i] + p[j]) / 2;
			r = dist(o, p[i]);
            rep(k,0,j) if (dist(o, p[k]) > r * EPS) {
                tie(o, r) = circumCircle(p[i], p[j], p[k]);
			}
		}
	}
	return {o, r};
}

D circlesUnionArea(vector<pair<P, D>> c) {
	sort(all(c)); c.erase(unique(all(c)), c.end());
	D res = 0;
	for(auto &[p, r]: c) {
		int cnt = 0, cover = 0;
		vector<pair<D, int>> eve = {{-pi, 0}};
		for(auto &[q, s]: c) if(make_pair(p, r) != make_pair(q, s)) {
			D dst = (p - q).dist();
			if(r + dst <= s) { cover = 1; break; }
			pair<P, P> inters;
			if(!circleInter(p, q, r, s, &inters)) continue;
			D le = angle(inters.st - p);
			D re = angle(inters.nd - p);
			cnt += le > re;
			eve.pb({le, 1}), eve.pb({re, -1});
		}
		if(cover) continue;
		sort(eve.begin() + 1, eve.end());
		eve.pb({pi, 0});
		D loc = 0;
		rep(i, 1, sz(eve)) {
			if(!cnt) {
				T a = eve[i-1].st, b = eve[i].st;
				loc += r * (b - a) +
					p.cross(P(cos(b)-cos(a), sin(b)-sin(a)));
			}
			cnt += eve[i].nd;
		}
		res += r * loc;
	}
	return res / 2;
}