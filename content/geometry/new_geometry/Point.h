/**
 * Author: Olaf Surgut
 * Date: 2025-07-13
 * License: CC0
 * Source: God
 * Description: Point primitives
 * Status: not tested
 */
#pragma once

using D=ld;
using P=pair<D,D>;
#define x st
#define y nd

const D eps = 1e-9L;
int sgn(D v){ return (v > +eps) - (v < -eps); }

P operator+(P a, P b){ return {a.x+b.x,a.y+b.y}; }
P operator-(P a, P b){ return {a.x-b.x,a.y-b.y}; }
P operator*(P a, D v){ return {a.x*v,a.y*v}; }
P operator/(P a, D v){ return {a.x/v,a.y/v}; }

D dot(P a, P b) { return a.x*b.x+a.y*b.y; }
D det(P a, P b) { return a.x*b.y-a.y*b.x; }
D det(P a, P b, P c) { return det(b-a, c-a); }
D len2(P v) { return dot(v, v); }
D dist2(P a, P b) { return len2(a-b); }
D len(P v) { return sqrt(len2(v)); }
D dist(P a, P b) { return len(a-b); }
P unit(P v) { return v / len(v); }
P rot90(P v) { return {-v.y, v.x}; }
P rotate(P v, D alpha) {
    D c = cos(alpha), s = sin(alpha);
    return {v.x*c-v.y*s, v.x*s+v.y*c};
}
D angle(P v) { return atan2(v.y, v.x); }
int side(P a, P b, P c) { return sgn(det(a,b,c)); }