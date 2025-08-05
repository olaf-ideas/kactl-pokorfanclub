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

#define rep(i,a,b) for(int i=(a);i<(b);i++)
using pii = pair<int, int>;
using vi = vector<int>;

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

bool cmp(P a, P b) {
    return sgn(a.x-b.x)==0?sgn(a.y-b.y)<0:sgn(a.x-b.x)<0; }

int half(P v) { return sgn(v.y)>0||(sgn(v.y)==0&&sgn(v.x)>=0); }
bool angle_cmp(P a, P b) {
    return half(a)!=half(b)?half(a)>half(b):sgn(det(a,b))>0; }

P intersect(P a, P b, P c, P d) {
    return a+(b-a)*(det(c-a,d-c)/det(b-a,d-c)); } // git
D lineDist(P a, P b, P p) { return abs(det(a,b,p))/len(b-a); } // git
P project(P a, P b, P p) {
    return a+(b-a)*(dot(p-a,b-a)/dot(b-a,b-a)); }
P reflect(P a, P b, P p) { return project(a,b,p) * 2 - p; }

bool onSegment(P a, P b, P p) { // git
    return side(a, b, p)==0 && sgn(dot(a-p, b-p))<=0;
}
vector<P> intersectSegment(P a, P b, P c, P d) { // git
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
D segDist(P a, P b, P p) { // git
    if (dot(b-a, p-a) < 0)
        return dist(a, p);
    if (dot(a-b, p-b) < 0)
        return dist(b, p);
    return lineDist(a, b, p);
}

const D pi = acos(-1);

vector<P> intersect(P a, D r, P b, D R) { // git
    if (sgn(dist2(a,b))==0) return {};
    P v = b-a;
    D d2 = len2(v), sum = r+R, dif = r-R,
      p = (d2+r*r-R*R)/(d2*2), h2 = r*r-p*p*d2;
    if (sum*sum < d2 || dif*dif > d2) return {};
    P m = a+v*p, per = rot90(v) * sqrt(fmax(0, h2)/d2);
    return {m+per, m-per};
}

D intersectArea(P a, D r, P b, D R) { // git
    if (r < R) swap(a, b), swap(r, R);
    D d = len(a-b);
    if(sgn(d-r-R)>=0) return 0;
    if(sgn(d-r+R)<=0) return pi*R*R;
    D u = 2*acos((d*d+r*r-R*R)/(2*d*r));
    D v = 2*acos((d*d+R*R-r*r)/(2*d*R));
    return 0.5*(r*r*(u-sin(u))+R*R*(v-sin(v)));
}

D intersectArea(P c, D r, vector<P> poly) {
    auto arg = [&](P p, P q) { return atan2(det(p,q),dot(p,q)); };
    auto tri = [&](P p, P q) {
        P w =q-p;
        auto r2 = r*r/2;
        auto a= dot(w,p)/dot(w,w), b=(dot(p,p)-r*r)/dot(w,w);
        auto d=a*a-b;
        if(d<=0)return arg(p,q)*r2;
        auto s=fmax(0,-a-sqrt(d)), t=fmin(1,-a+sqrt(d));
        if (t<0||1<=s) return arg(p,q)*r2;
        P u=p+w*s, v=p+w*t;
        return arg(p,u)*r2+det(u,v)/2+arg(v,q)*r2;
    };
    D res=0;
    rep(i,0,sz(poly))
        res += tri(poly[i]-c,poly[(i+1)%sz(poly)]-c);
    return res;
}

// external R > 0, internal R < 0, point R = 0
vector<pair<P,P>> tangents(P a, D r, P b, D R) { // git
    P d = b-a;
    D dr = r-R, d2 = len2(d), h2 = d2-dr*dr;
    if (sgn(d2) == 0 || h2 < 0) return {};
    vector<pair<P,P>> res;
    for (D sign : {-1, +1}) {
        P v = (d*dr+rot90(d)*sqrt(h2)*sign)/d2;
        res.pb({a+v*r, b+v*R});
    }
    if (h2==0) res.pop_back();
    return res;
}

vector<P> circleLine(P c, D r, P a, P b) {
    P ab = b-a, p = a+ab*dot(c-a,ab)/len2(ab);
    D s = det(a,b,c), h2 = r*r-s*s/len2(ab);
    if (h2 < 0) return {};
    if (h2 == 0) return {p};
    P h = unit(ab) * sqrt(h2);
    return {p+h, p-h};
}

// vector<P> circleLine(P c, D r, P a, P b) {
//     P p = project(a,b,c);
//     D h2 = r*r-len2(p-c);
//     if (sgn(h2)<0) return {};
//     if (sgn(h2)==0)return {p};
//     P v = unit(b-a)*sqrt(h2);
//     return {p+v,p-v};
// }

pair<P,D> circumCircle(P a, P b, P c) {
    P v = c-a, w = b-a;
    P o = a + rot90(v*len2(w)-w*len2(v))/det(v,w)/2;
    return {o,len(a-o)}; 
}

pair<P, D> enclosingCircle(vector<P> p) {
	shuffle(all(p), mt19937(2137));
	P o = p[0]; D r = 0;
	rep(i,0,sz(p)) if (sgn(dist(o, p[i])-r) > 0) {
		o = p[i], r = 0;
		rep(j,0,i) if (sgn(dist(o, p[j])-r) > 0) {
			o = (p[i] + p[j]) / 2, r = dist(o, p[i]);
            rep(k,0,j) if (sgn(dist(o, p[k])-r) > 0)
                tie(o, r) = circumCircle(p[i], p[j], p[k]);
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
		for(auto &[q, s]: c) if(mp(p, r) != mp(q, s)) {
			D dst = len(p-q);
            if(r + dst <= s) { cover = 1; break; }
            vector<P> inters=intersect(p,r,q,s);
            if (inters.empty()) continue;
			D le = angle(inters[0] - p);
			D re = angle(inters[1] - p);
			cnt += le > re;
			eve.pb({le, 1}), eve.pb({re, -1});
		}
		if(cover) continue;
		sort(eve.begin() + 1, eve.end());
		eve.pb({pi, 0});
		D loc = 0;
		rep(i, 1, sz(eve)) {
			if(!cnt) {
				D a = eve[i-1].st, b = eve[i].st;
				loc += r * (b - a) +
                    det(p, P(cos(b)-cos(a), sin(b)-sin(a)));
			}
			cnt += eve[i].nd;
		}
		res += r * loc;
	}
	return res / 2;
}

bool inCircle(P c, D r, P p) {
    return sgn(len(p-c)-r)<=0;
}

const int inf = 1e9+7;

const int X = 1000 + 7;

mt19937 rng(2137);
int randint(int a, int b) {
    return uniform_int_distribution<int>(a,b)(rng);
}

signed main() {
	cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(10);

    vi cnt(5);
    rep(tt, 0, 100000000) {
        P a, b, c;

        do {
            a = P{randint(-X,+X),randint(-X,+X)};
            b = P{randint(-X,+X),randint(-X,+X)};
            c = P{randint(-X,+X),randint(-X,+X)};
        } while (sgn(len(a-b))==0||sgn(len(a-c))==0||sgn(len(b-c))==0||side(a,b,c)==0);

        auto [cc, r] = circumCircle(a,b,c);

        assert(sgn(len(a-cc)-r)==0);
        assert(sgn(len(b-cc)-r)==0);
        assert(sgn(len(c-cc)-r)==0);
    }
    cerr << cnt<< '\n';

    return 0;
}
