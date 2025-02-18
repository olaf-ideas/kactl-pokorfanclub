/**
 * Author: kobor, Aeren1564
 * Date: 2024-08-23
 * License: CC0
 * Source: https://judge.yosupo.jp/submission/201334
 * Description: Weighted matching for general graphs.
 * Time: O(N^3), fast in practice
 * Status: tested on a few tasks
 */
#pragma once

namespace WeightedBlossom {	// 1-indexed
	#define d(x) (lab[x.u] + lab[x.v] - e[x.u][x.v].w * 2)
	const int N = 501 * 2;
	const ll INF = 1e18;
	struct Q { int u, v; ll w; } e[N][N]; vi p[N];
	int n, m = 0, id, h, t, lk[N], sl[N], sk[N], f[N], b[N][N];
	int s[N], ed[N], q[N]; ll lab[N];
	void upd(int u, int v) {
		if(!sl[v] || d(e[u][v]) < d(e[sl[v]][v])) sl[v] = u;
	}
	void ss(int v){
		sl[v] = 0;
		rep(u, 1, n)
			if(e[u][v].w > 0 && sk[u] != v && !s[sk[u]]) upd(u, v);
	}
	void ins(int u) {
		if(u <= n) q[++t] = u;
		else for(auto v: p[u]) ins(v);
	}
	void mdf(int u, int w) {
		sk[u] = w;
		if(u > n) for(auto v: p[u]) mdf(v, w);
	}
	int gr(int u,int v){
		if((v = find(all(p[u]), v) - p[u].begin()) & 1) {
			reverse(1 + all(p[u])); return SZ(p[u]) - v;
		}
		return v;
	}
	void stm(int u, int v){
		lk[u] = e[u][v].v;
		if(u <= n) return;
		Q w = e[u][v]; int x = b[u][w.u], y = gr(u,x);
		FOR(i, 0, y) stm(p[u][i], p[u][i ^ 1]);
		stm(x, v);
		rotate(p[u].begin(), p[u].begin() + y, p[u].end());
	}
	void aug(int u, int v){
		int w = sk[lk[u]]; stm(u, v); if(!w) return;
		stm(w, sk[f[w]]); aug(sk[f[w]], w);
	}
	int lca(int u, int v){
		for(++id; u|v; swap(u, v)){
			if(!u) continue;
			if(ed[u] == id) return u;
			ed[u] = id; if((u = sk[lk[u]])) u = sk[f[u]]; // not ==
		}
		return 0;
	}
	void add(int uu, int a, int vv){
		int x = n + 1; while(x <= m && sk[x]) x++;
		if(x > m) m++;
		lab[x] = s[x] = sk[x] = 0; lk[x] = lk[a];
		p[x].clear(); p[x].pb(a);
		for(auto i = uu, j = 0; i != a; i = sk[f[j]])
			p[x].pb(i), p[x].pb(j = sk[lk[i]]), ins(j);
		reverse(1 + all(p[x]));
		for(auto i = vv, j = 0; i != a; i = sk[f[j]])
			p[x].pb(i), p[x].pb(j = sk[lk[i]]), ins(j);
		mdf(x, x); rep(i, 1, m) e[x][i].w = e[i][x].w = 0;
		memset(b[x] + 1, 0, n * sizeof b[0][0]);
		for(auto u: p[x]){
			rep(v, 1, m) if(!e[x][v].w || d(e[u][v]) < d(e[x][v]))
				e[x][v] = e[u][v], e[v][x] = e[v][u];
			rep(v, 1, n) if(b[u][v]) b[x][v] = u;
		}
		ss(x);
	}
	void ex(int u) {	// s[u] == 1
		for(auto x: p[u]) mdf(x, x);
		int a = b[u][e[u][f[u]].u], r = gr(u, a);
		FOR(i, 0, r) {
			int x = p[u][i], y = p[u][i + 1];
			f[x] = e[y][x].u; s[x] = 1; s[y] = sl[x] = 0;
			ss(y); ins(y); i++;
		}
		s[a] = 1; f[a] = f[u];
		FOR(i, r + 1, SZ(p[u])) s[p[u][i]] = -1, ss(p[u][i]);
		sk[u] = 0;
	}
	bool on(const Q &ee) {
		int u = sk[ee.u], v = sk[ee.v], a;
		if(s[v] == -1) {
			f[v] = ee.u, s[v] = 1, a = sk[lk[v]];
			sl[v] = sl[a] = s[a] = 0, ins(a);
		}
		else if(!s[v]){
			a = lca(u, v);
			if(!a) return aug(u,v), aug(v,u), 1;
			else add(u,a,v);
		}
		return 0;
	}
	bool bfs() {
		memset(s + 1, -1, m * sizeof s[0]);
		memset(sl + 1, 0, m * sizeof sl[0]);
		h = 1; t = 0;
		rep(i, 1, m)
			if(sk[i] == i && !lk[i]) f[i] = s[i] = 0, ins(i);
		if(h > t) return 0;
		while(1){
			while(h <= t) {
				int u = q[h++];
				if(s[sk[u]] != 1) rep(v, 1, n) {
					if(e[u][v].w > 0 && sk[u] != sk[v]) {
						if(d(e[u][v])) upd(u, sk[v]);
						else if(on(e[u][v])) return 1;
					}
				}
			}
			ll x = INF;
			rep(i, n + 1, m) if(sk[i] == i && s[i] == 1)
				x = min(x, lab[i] >> 1);
			rep(i, 1, m) if(sk[i] == i && sl[i] && s[i] != 1)
				x = min(x, d(e[sl[i]][i]) >> (s[i] + 1));
			rep(i, 1, n) if(~s[sk[i]])
				if((lab[i] += (s[sk[i]] * 2 - 1) * x) <= 0) return 0;
			rep(i, n + 1, m) if(sk[i] == i && ~s[sk[i]])
				lab[i] += (2 - s[sk[i]] * 4) * x;
			h = 1; t = 0;
			rep(i, 1, m) if(sk[i] == i && sl[i] && sk[sl[i]] != i &&
				!d(e[sl[i]][i]) && on(e[sl[i]][i])) return 1;
			rep(i, n + 1, m) if(sk[i] == i && s[i] == 1 && !lab[i])
				ex(i);
		}
		return 0;
	}
	pair<ll, vector<pii>> run
	(int _n, vector<tuple<int, int, ll>> edges) {
		memset(ed + 1, 0, m * sizeof ed[0]);
		memset(lk + 1, 0, m * sizeof lk[0]);
		n = m = _n; id = 0; iota(sk + 1, sk + n + 1, 1);
		ll wm = 0, weight = 0;
		rep(i, 1, n) rep(j, 1, n) e[i][j] = {i, j, 0};
		for(auto [u, v, w]: edges)
			wm = max(wm, e[v][u].w = e[u][v].w = max(e[u][v].w, w));
		rep(i, 1, n) p[i].clear();
		rep(i, 1, n) rep(j, 1, n) b[i][j] = i * (i == j);
		fill_n(lab + 1, n, wm); while(bfs());
		vector<pii> matching;
		rep(i, 1, n) if(i < lk[i])
			weight += e[i][lk[i]].w, matching.pb({i, lk[i]});
		return {weight, matching};
	}
	#undef d
}
