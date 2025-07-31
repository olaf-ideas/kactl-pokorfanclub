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

const D eps = 1e-6L;
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

int hf(P a) { return a.y < 0 || (a.y == 0 && a.x < 0); }
struct polarCmp {
	bool operator()(const P &a, const P &b) const {
		return hf(a) == hf(b) ? det(a, b) > 0 : hf(a) < hf(b);
	}
};

struct HalfplaneSet : map<P, P, polarCmp> {
	D INF = 1e6, area = 8 * INF * INF;
	HalfplaneSet() {
		P p(-INF, -INF), d(1, 0);
		rep(k, 0, 4) {
			insert({d, p}); p = p + d * 2 * INF; d = rot90(d); }
	}
	auto fix(auto it) { return it == end() ? begin() : it; }
	auto getNext(auto it) { return fix(next(it)); }
	auto getPrev(auto it) {
		return it == begin() ? prev(end()) : prev(it); }
	auto uSide(auto it, int change) {
		area += change * det(it->nd, getNext(it)->nd); }
	auto del(auto it) {
		uSide(getPrev(it), -1), uSide(it, -1);
		it = fix(erase(it));
		if(size()) uSide(getPrev(it), 1);
		return it;
	}
	void add(P s, P e) {
		auto eval = [&](auto it) { return sgn(det(s, e, it->nd)); };
		auto ii = [&](auto it) {
			return intersect(s, e, it->nd, it->st + it->nd); };
		auto it = fix(lower_bound(e - s));
		if(empty() || eval(it) >= 0) return;
		while(size() && eval(getPrev(it)) < 0) del(getPrev(it));
		while(size() && eval(getNext(it)) < 0) it = del(it);
		if(empty()) return;
		if(eval(getNext(it)) > 0) {
			uSide(getPrev(it), -1), uSide(it, -1);
			it->nd = ii(it);
			uSide(getPrev(it), 1), uSide(it, 1);
		}
		else it = del(it);
		it = getPrev(it);
		uSide(it, -1); insert(it, {e - s, ii(it)});
		uSide(it, 1), uSide(getNext(it), 1);
		if(eval(it) == 0) del(it);
	}
	D maxDot(P a) {
		return dot(a, fix(lower_bound(rot90(a)))->nd); }
	D getArea() { return area / 2; }
};

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
        int n, m;
        cin >> n >> m;
        vector<P> a(n), b(m);
        rep(i, 0, n) cin >> a[i].x >> a[i].y;
        rep(i,0,m) cin >> b[i].x >> b[i].y;

        HalfplaneSet ls;
        rep(i,0,n)ls.add(a[i],a[(i+1)%n]);
        rep(i,0,m)ls.add(b[i],b[(i+1)%m]);

        cout << fixed << setprecision(4);
        cout << ls.getArea() <<'\n';

    }

	return 0;
}
