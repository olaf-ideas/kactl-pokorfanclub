/**
 * Author: Olaf Surgut
 * Date: 2025-07-13
 * License: CC0
 * Source: old kactl + own seg_dist
 * Description: Segment primitives
 * Status: not tested
 */
#pragma once

#include "Point.h"
#include "Line.h"

bool onSegment(P a, P b, P p) {
    return sgn(det(a, b, p))==0 && sgn(dot(a-p, b-p))<=0;
}
vector<P> intersect(P a, P b, P c, P d) {
    auto da = det(c,d,a), db = det(c,d,b),
         dc = det(a,b,c), dd = det(a,b,d);
    if (sgn(da) * sgn(db) < 0 && sgn(dc) * sgn(dd) < 0)
        return {intersect(a,b,c,d)};
    set<P> s;
    if (onSegment(a,b,c)) s.insert(c);
    if (onSegment(a,b,d)) s.insert(d);
    if (onSegment(c,d,a)) s.insert(a);
    if (onSegment(c,d,b)) s.insert(b);
    return {all(s)};
}
D seg_dist(P a, P b, P p) {
    if (dot(b-a, p-a) < 0)
        return dist(a, p);
    if (dot(a-b, p-b) < 0)
        return dist(b, p);
    return line_dist(a, b, p);
}