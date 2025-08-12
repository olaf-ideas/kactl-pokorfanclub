/**
 * Author: Olaf Surgut
 * Date: 2025-07-29
 * License: CC0
 * Source: God
 * Description: 3D Point primitives
 * Status: not tested
 */

using D=ld;
struct P { 
    array<D, 3> v; 
    auto operator<=>(P const&p) const = default;
};
#define x v[0]
#define y v[1]
#define z v[2]

const D eps = 1e-9L;
int sgn(D v) { return (v > +eps) - (v < -eps); }

P operator+ (P a, P b) { rep(i,0,3) a.v[i] += b.v[i]; return a; }
P operator- (P a, P b) { rep(i,0,3) a.v[i] -= b.v[i]; return a; }
P operator* (P a, D v) { rep(i,0,3) a.v[i] *= v; return a; }
P operator/ (P a, D v) { rep(i,0,3) a.v[i] /= v; return a; }

D dot(P a, P b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
P det(P a, P b) { return { a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x }; }
D len(P v) { return sqrt(dot(a,a)); }
D phi(P v) { return atan2(v.y, v.x); }
D theta(P v) { return atan2(hypot(x,y),z); }
P unit(P v) { return v / len(v); }
P rotate(P v, P axis, P angle) {
    D s = sin(angle), c = cos(angle); P u = unit(axis);
    return u*dot(v,u)*(1-c)+v*c-det(v,u)*s; }