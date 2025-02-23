/**
 * Author: kobor
 * Date: 2024-07-12
 * License: CC0
 * Description: Finds one of segments intersections.
 *	You should change dirSeg's comparator, to compare segments at their left end.
 * Time: $O(N \log N)$
 * Status: tested on Timus:1469
 */
#pragma once

#include "SegmentIntersection.h"

template<class P>
struct dirSeg {
	P s, e; int rev;
	dirSeg(P _s, P _e) : s(_s), e(_e), rev(0) {
		if(e < s) swap(s, e), rev = 1;
	}
	P getY(P X) {	// takes x * 2, returns y * 2 as a fraction
		P d = (e - s);
		return !sgn(d.x) ? P(s.y+e.y, 1) : P(d.cross(s*2-X), d.x);
	}
	int cmp(dirSeg b) {	// needs ~64 * M^3 !
		P X(max(s.x, b.s.x) + min(e.x, b.e.x), 0);
		return sgn(getY(X).cross(b.getY(X)));
	}
};

template<class P>
pii segmentsIntersect(vector<pair<P, P>> segments) {
	vector<tuple<P, int, int>> eve; // {point, event_type, id}
	vector<dirSeg<P>> segs;
	for(auto &[s, e]: segments) {
		dirSeg<P> seg(s, e);
		eve.pb({seg.s,0,sz(segs)}), eve.pb({seg.e,1,sz(segs)});
		segs.pb(seg);
	}
	sort(all(eve));
	auto inter = [](auto a, auto b) {
		return sz(segInter(a->st.s, a->st.e, b->st.s, b->st.e));
	};
	auto cmp = [](auto a, auto b) {
		return mp(a.st.cmp(b.st), a.nd) < mp(0, b.nd);
	};
	set<pair<dirSeg<P>, int>, decltype(cmp)> s(cmp);
	for(auto &[_, eve_tp, id]: eve) {
		if(eve_tp == 0) {	// add segment
			auto it = s.insert({segs[id], id}).st;
			if(next(it) != s.end() && inter(it, next(it)))
				return {it->nd, next(it)->nd};
			if(it != s.begin() && inter(it, prev(it)))
				return {it->nd, prev(it)->nd};
		}
		if(eve_tp == 1) {	// del segment
			auto it = s.erase(s.find({segs[id], id}));
			if(it!=s.begin() && it!=s.end() && inter(it, prev(it)))
				return {it->nd, prev(it)->nd};
		}
	}
	return {-1, -1};
}