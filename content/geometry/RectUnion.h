/**
 * Author: none
 * License: CC0
 * Source: 
 * Description: Rectangle union
 * Status:
 */

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

struct rectangle { int xl, yl, xh, yh; };
long long rectangle_area(vector<rectangle> rs) {
  vector<int> ys; // coordinate compression
  for (int i = 0; i < rs.size(); ++i) {
    ys.push_back(rs[i].yl);
    ys.push_back(rs[i].yh);
  }
  sort(all(ys)); ys.erase(unique(all(ys)), ys.end());

  int n = ys.size(); // measure tree
  vector<int> C(8*n), A(8*n);
  function<void (int,int,int,int,int,int)> aux = 
  [&](int a, int b, int c, int l, int r, int k) {
    if ((a = max(a,l)) >= (b = min(b,r))) return;
    if (a == l && b == r) C[k] += c;
    else {
      aux(a, b, c, l, (l+r)/2, 2*k+1);
      aux(a, b, c, (l+r)/2, r, 2*k+2);
    }
    if (C[k]) A[k] = ys[r] - ys[l];
    else      A[k] = A[2*k+1] + A[2*k+2];
  };

  struct event { int x, l, h, c; }; // plane sweep
  vector<event> es;
  for (auto r: rs) {
    int l = distance(ys.begin(), lower_bound(all(ys), r.yl));
    int h = distance(ys.begin(), lower_bound(all(ys), r.yh));
    es.push_back({r.xl, l, h, +1});
    es.push_back({r.xh, l, h, -1});
  }
  sort(all(es), [](event a, event b) { return a.x != b.x ? a.x < b.x : a.c > b.c; });
  long long area = 0, prev = 0;
  for (auto &e: es) {
    area += (e.x - prev) * A[0];
    prev = e.x;
    aux(e.l,e.h,e.c,0,n,0);
  }
  return area;
}