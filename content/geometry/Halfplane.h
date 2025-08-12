/**
 * Author: Olaf Surgut
 * Date: 2025-07-29
 * License: CC0
 * Source: God
 * Description: Halfplane intersection
 * Time: O(n \log n)
 * Status: Tested with O(n^3) brute and on various problems
 */

#include "Point.h"
#include "Line.h"

using L=pair<P,P>;

#define dir(l) l.nd-l.st
vector<P> halfplaneIntersection(vector<L> ls) {
    sort(all(ls), [&](L a, L b){return angle_cmp(dir(a),dir(b));});
    auto bad = [&](L a, L b, L c) {
        return sgn(det(a.st, a.nd, intersect(b.st,b.nd,c.st,c.nd))) < 0; };
    deque<L> q; for (L h : ls) {
        while (sz(q)>=2 && bad(h,end(q)[-1],end(q)[-2])) q.pop_back();
        while (sz(q)>=2 && bad(h,q[0],q[1])) q.pop_front();
        if (sz(q) && sgn(det(dir(h),dir(q.back())))==0){
            if (sgn(dot(dir(h),dir(q.back())))<0)
                return {};
            if (side(h.st,h.nd,q.back().st)<0)
                q.back() = h;
        } else q.pb(h); }
    while (sz(q)>=3 && bad(q[0],end(q)[-1],end(q)[-2])) q.pop_back();
    while (sz(q)>=3 && bad(end(q)[-1],q[0],q[1])) q.pop_front();
    if(sz(q)<3)return{};
    vector<P> h;
    rep(i,0,sz(q)){
        int j=(i+1)%sz(q);
        h.pb(intersect(q[i].st,q[i].nd,q[j].st,q[j].nd)); }
    return h; }
