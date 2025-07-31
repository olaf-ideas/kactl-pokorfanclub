// https://www.codechef.com/problems/ALLPOLY

#include "bits/stdc++.h"
using namespace std;

#define int long long
#define ll long long
#define ld long double

#define endl '\n'
#define st first
#define nd second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define sz(x) (int)(x).size()
#define all(x) begin(x),end(x)
#define FOR(i,l,r) for(int i=(l);i<=(r);i++)
#define ROF(i,r,l) for(int i=(r);i>=(l);i--)

auto& operator<<(auto &o, pair<auto, auto> p) {
	return o << "(" << p.st << ", " << p.nd << ")";}
auto operator<<(auto &o, auto x)->decltype(end(x), o) {
	o << "{"; int i=0; for (auto e : x) o << ","+!i++ << e;
	return o << "}"; }

#ifdef LOCAL
#define debug(x...) cerr << "[" #x "]: ", [](auto...$) { \
	((cerr << $ << "; "),...) << endl; }(x)
#else
#define debug(...)
#endif

#define rep(i,a,b) for(int i = a; i < (b); i++)
using pii = pair<int, int>;
using vi = vector<int>;

const int inf = 1e9+7;


/**
 * Author: Olaf Surgut
 * Date: 2025-07-13
 * License: CC0
 * Source: God
 * Description: Point primitives
 * Status: not tested
 */

using D=ld;
using P=pair<D,D>;
#define x st
#define y nd

const D eps = 1e-11L;
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

bool cmp(P a, P b) {
    return sgn(a.x-b.x)==0?sgn(a.y-b.y)<0:sgn(a.x-b.x)<0; }

int half(P v) { return sgn(v.y)>0||(sgn(v.y)==0&&sgn(v.x)>=0); }
bool angle_cmp(P a, P b) {
    return half(a)!=half(b)?half(a)>half(b):sgn(det(a,b))>0; }

/**
 * Author: Olaf Surgut
 * Date: 2025-07-13
 * License: CC0
 * Source: God
 * Description: Line primitives
 * Status: not tested
 */

P intersect(P a, P b, P c, P d) {
    return a+(b-a)*(det(c-a,d-c)/det(b-a,d-c)); }
D lineDist(P a, P b, P p) { return abs(det(a,b,p))/len(b-a); }
P project(P a, P b, P p) {
    return a+(b-a)*(dot(p-a,b-a)/dot(b-a,b-a)); }
P reflect(P a, P b, P p) { return project(a,b,p) * 2 - p; }

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

D area(vector<P> p){
    D res=0;
    rep(i,0,sz(p))
        res+=det(p[i],p[(i+1)%sz(p)]);
    return res;
}

signed main() {
	cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<P> p(n);
        rep(i,0,n){
            cin>>p[i].x>>p[i].y;
            p[i].x/=2e5;
            p[i].y/=2e5;
        }

        if (area(p)<0)
            reverse(all(p));

        vector<L>ls;
        rep(i,0,n)ls.pb({p[i],p[(i+1)%n]});

        // const D X=1e7;
        // P q{X,X};
        // rep(i,0,4){
        //     ls.pb({q,rot90(q)});
        //     q=rot90(q);
        // }

        cout<<fixed<<setprecision(11);
        cout << fabs(area(halfplaneIntersection(ls)))/2/1e4<<'\n';
    }

	return 0;
}
