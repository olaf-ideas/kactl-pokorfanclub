/**
 * Author: kobor
 * Date: 2024-07-15
 * License: CC0
 * Source: own work
 * Description: Computes (not necessarily convex) polygon tree structure.
 * 	Also for each query point computes its location (including boundaries).
 * Time: O(n \log n)
 * Status: tested on a few tasks
 */
#pragma once

#include "directedSegment.h"

template<class P>
pair<vi,vi> pointLoc(vector<vector<P>> polys, vector<P> pts) {
	vector<tuple<P, int, int>> eve;	// {point, event_type, id}
	vector<pair<dirSeg<P>, int>> segs;	// {s, e, poly_id}
	rep(i, sz(polys)) rep(j, sz(polys[i])) {
		dirSeg<P> seg(polys[i][j], polys[i][(j+1)%sz(polys[i])]);
		eve.pb({seg.s,0,sz(segs)}), eve.pb({seg.e,2,sz(segs)});
		segs.pb({seg, i});
	}
	rep(i, sz(pts)) eve.pb({pts[i], 1, i});
	sort(all(eve));
	vi par(sz(polys), -2), ans(sz(pts), -1);
	auto cmp = [](auto a, auto b) {
		return make_pair(a.st.cmp(b.st), a.nd) < make_pair(0, b.nd);
	};
	set<pair<dirSeg<P>, int>, decltype(cmp)> s(cmp);
	for(auto &[_, eve_tp, id]: eve) {
		if(eve_tp == 1) {	// point query
			P p = pts[id];
			auto it = s.lower_bound({dirSeg(p, p), 0});
			if(it != s.begin()) {	// on vertical segment?
				auto prv = prev(it);
				if(!sgn(p.cross(prv->st.s, prv->st.e))) it--;
			}
			if(it == s.end()) ans[id] = -1;
			else {
				auto [seg, seg_id] = *it;
				int poly_id = segs[seg_id].nd; // strictness there!
				ans[id] = !seg.rev && sgn(p.cross(seg.s, seg.e))
					? par[poly_id] : poly_id;
			}
		}
		if(eve_tp == 0) {	// add segment
			auto it = next(s.insert({segs[id].st, id}).st);
			int poly_id = segs[id].nd;
			if(par[poly_id] == -2) {
				if(it == s.end()) par[poly_id] = -1;
				else {
					int up_rev = it->st.rev, up_id = segs[it->nd].nd;
					par[poly_id] = !up_rev ? par[up_id] : up_id;
				}
			}
		}
		if(eve_tp == 2) s.erase({segs[id].st, id});	// del segment
	}
	return {par, ans};
}