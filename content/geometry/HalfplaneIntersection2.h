/**
 * Author: Olaf Surgut
 * Date: 1984-9-11
 * License: Boost Software License
 * Source: chyba z cp-algo
 * Description: Weszło na zadaniu gdzie trzeba bylo policzyc pole przeciecia
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 100;

typedef long double LD;

const LD inf = 500 + 7;

struct Point {
	LD x, y;
	
	void read() {
		int xx, yy;
		cin >> xx >> yy;
		x = xx;
		y = yy;
	}
};

Point operator- (const Point& A, const Point& B) { return Point{A.x - B.x, A.y - B.y}; }
Point operator+ (const Point& A, const Point& B) { return Point{A.x + B.x, A.y + B.y}; }
Point operator* (const Point& A, const LD& value) { return Point{A.x * value, A.y * value}; }

int half(const Point& v) {
	if (v.x < 0 && v.y < 0)
		return 1;
	if (v.x >= 0 && v.y < 0)
		return 2;
	if (v.x >= 0 && v.y >= 0)
		return 3;
	if (v.x < 0 && v.y >= 0)
		return 4;
	assert(false);
	return -1;
}

LD dot(const Point& A, const Point& B) { return A.x * B.x + A.y * B.y; }
LD det(const Point& A, const Point& B) { return A.x * B.y - A.y * B.x; }
LD det(const Point& A, const Point& B, const Point& C) { return det(B - A, C - A); }

struct Halfplane {
	Point P, v;

	bool inside(const Point& Q) const {
		return det(v, Q - P) > -1e-9;
	}

	bool operator< (const Halfplane& other) const {
		if (half(v) != half(other.v))
			return half(v) < half(other.v);
		return det(v, other.v) > 0;
	}
};

Point inter(const Halfplane& k, const Halfplane& l) {
	return k.P + k.v * (det(l.P - k.P, l.v) / det(k.v, l.v));
}

int n;
Point pts[N][2];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << fixed << setprecision(12);

	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j : {0, 1})
			pts[i][j].read();
	
	vector<Halfplane> hps;
	for (int i = 0; i < n; i++) {
		for (int j : {0, 1}) {
			for (int k = 0; k < n; k++) if (i != k) {
				for (int l : {0, 1}) {
					bool ok = true;
					for (int m = 0; m < n; m++) if (m != i && m != k) {
						if (det(pts[i][j], pts[k][l], pts[m][0]) < 0 &&
							det(pts[i][j], pts[k][l], pts[m][1]) < 0) {
							ok = false;
							break;
						}
					}

					if (ok) {
						hps.push_back(Halfplane{pts[i][j], pts[k][l] - pts[i][j]});
					}
				}
			}
		}
	}

	const Point box[4] = {
		Point{+inf, +inf},
		Point{+inf, -inf},
		Point{-inf, -inf},
		Point{-inf, +inf}
	};

	for (int i = 0, j = 3; i < 4; j = i++) {
		hps.push_back(Halfplane{box[i], box[j] - box[i]});
	}

	sort(hps.begin(), hps.end());
	deque<Halfplane> dq;

	for (const Halfplane& hp : hps) {
		while (dq.size() >= 2 && !hp.inside(inter(end(dq)[-1], end(dq)[-2])))
			dq.pop_back();
		
		while (dq.size() >= 2 && !hp.inside(inter(dq[0], dq[1])))
			dq.pop_front();

		if (dq.size() && fabsl(det(hp.v, dq.back().v)) < 1e-9L) {
			if (dot(hp.v, dq.back().v) < 0) {
				cout << 0.0L << '\n';
				return 0;
			}

			if (!hp.inside(dq.back().P)) {
				dq.pop_back();
				dq.push_back(hp);
			}
		}
		else {
			dq.push_back(hp);
		}
	}

	while (dq.size() >= 3 && !dq[0].inside(inter(end(dq)[-1], end(dq)[-2])))
		dq.pop_back();
	
	while (dq.size() >= 3 && !end(dq)[-1].inside(inter(dq[0], dq[1])))
		dq.pop_front();
	
	vector<Point> hull;
	for (int i = 0, j = (int) dq.size() - 1; i < (int) dq.size(); j = i++) {
		hull.push_back(inter(dq[j], dq[i]));
	}

	long double ans = 0;
	for (int i = 0, j = (int) hull.size() - 1; i < (int) hull.size(); j = i++) {
		ans += det(hull[i], hull[j]);
	}

	ans /= 2;
	
	cout << fabsl(ans) << '\n';

	return 0;
}