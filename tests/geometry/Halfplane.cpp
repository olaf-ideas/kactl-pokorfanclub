#include "../template.h"

#include "../../content/geometry/new_geometry/Convex.h"
#include "../../content/geometry/new_geometry/Halfplane.h"
// #include "../../content/geometry/HalfplaneIntersection.h"
#include "../../content/geometry/HalfplaneIntersectionOnline.h"

D area(vector<P> pts) {
	D res = 0;
	rep(i,0,sz(pts)){
		res += det(pts[(i+1)%sz(pts)], pts[i]);
	}
	return abs(res) * 0.5;
}

vector<P> halfplaneIntersectionBrute(vector<L> ls,bool dbs=false) {
	vector<P> pts;
	rep(i,0,sz(ls)) rep(j,i+1,sz(ls)) if (sgn(det(ls[i].st-ls[i].nd,ls[j].st-ls[j].nd))!=0){
		pts.pb(intersect(ls[i].st,ls[i].nd,ls[j].st,ls[j].nd));
		if (dbs) debug(pts.back(),i,j);
		rep(k,0,sz(ls)) if (side(ls[k].st,ls[k].nd,pts.back())<0){
			if (dbs){
				debug("fail",k,side(ls[k].st,ls[k].nd,pts.back()));
				debug(det(ls[k].st, ls[k].nd, pts.back()));
				debug(ls[k].st, ls[k].nd, pts.back());
			}
			pts.pop_back();
			break;
		}
	}
	if (dbs) {
		debug("convex");
		debug(pts);
	}
	return convexHull(pts);
}

mt19937 rng(2137);

int randint(int a, int b) {
	return uniform_int_distribution<int>(a, b)(rng);
}

const int XX = 2e5;

P randpoint(int X=XX){
	return P{randint(-X,+X),randint(-X,+X)};
}

void print(vector<L> lines) {
	rep(i,0,sz(lines)){
		cerr << "Line(" << lines[i].st << "," << lines[i].nd << ")\n";
	}
}
int cmp2(P a, P b){
    return sgn(a.x-b.x)==0?sgn(a.y-b.y):sgn(a.x-b.x);
}

signed main() {

	rep(cc,0,100000) {
		int n = randint(2,200);
		vector<L> lines;
		// vector<Line> lines_kactl;

		rep(i,0,n) {
			L l;
			do {
				l = {randpoint(),randpoint()};
			} while (side(l.st,l.nd,P{0,0})<0||sgn(len2(l.st-l.nd))==0);
			lines.pb(l);
			// lines_kactl.pb({l.st,l.nd});
		}

		P p{XX,XX};
		rep(i,0,4){
			lines.pb({p,rot90(p)});
			// lines_kactl.pb({p,rot90(p)});
			p=rot90(p);
		}

		HalfplaneSet kobor;

		for (auto [a,b]:lines)
			kobor.add(a,b);

		auto ans = halfplaneIntersectionBrute(lines);
		auto res = halfplaneIntersection(lines);
		// auto kactl = halfplaneIntersection2(lines_kactl);

		// ans = convexHull(ans);
		// res = convexHull(res);
		// kactl = convexHull(kactl);

		rotate(begin(ans),min_element(all(ans),[&](P a,P b){return cmp2(a,b)<0;}),end(ans));
		rotate(begin(res),min_element(all(res),[&](P a,P b){return cmp2(a,b)<0;}),end(res));
		// rotate(begin(kactl),min_element(all(kactl),[&](P a,P b){return cmp2(a,b)<0;}),end(kactl));

		bool ok = true;

		ok &= (sgn(area(ans)-area(res))==0);
		ok &= (sgn(kobor.getArea()-area(ans))==0);
		// ok &= (sgn(area(ans)-area(kactl))==0);
		
		// ok &= (sz(ans)==sz(res));
		// rep(i,0,min(sz(res),sz(ans))){
		// 	ok &= (sgn(ans[i].x-res[i].x)==0);
		// 	ok &= (sgn(ans[i].y-res[i].y)==0);
		// }

		if (!ok) {
			debug(cc,n);
			debug(lines);
			debug(ans);
			debug(res);
			// debug(kactl);

			debug(area(ans));
			debug(area(res));
			debug(kobor.getArea());
			// debug(area(kactl));

			print(lines);

			assert(false);
		}

		debug("pass", cc, n);
	}

}
