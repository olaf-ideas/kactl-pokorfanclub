/**
 * Author: Tomek & Arek & Bartek
 * Date: 2024
 * License: ???
 * Source: https://raw.githubusercontent.com/tonowak/acmlib/master/code/graph/planarity-check/main.cpp
 * Description: Read desc below.
 */

/*
 * Opis: O(szybko) ale istnieja przyklady O(n2), przyjmuje graf nieskierowany bez petelek i multikrawedzi.
 */

bool is_planar(vector<vi> g) {
	int n = sz(g), m = 0;
	rep(v, n) m += sz(g[v]);
	m /= 2;
	if(n <= 3) return true;
	if(m > 3 * n - 6) return false;
	vector<vi> up(n), dn(n);
	vi low(n, -1), pre(n);
	rep(start, n)
		if(low[start] == -1) {
			vector<pii> e_up;
			int tm = 0;
			function<void (int, int)> dfs_low = [&](int v, int p) {
				low[v] = pre[v] = tm++;
				for(int u : g[v])
					if(u != p and low[u] == -1) {
						dn[v].eb(u);
						dfs_low(u, v);
						low[v] = min(low[v], low[u]);
					}
					else if(u != p and pre[u] < pre[v]) {
						up[v].eb(ssize(e_up));
						e_up.eb(v, u);
						low[v] = min(low[v], pre[u]);
					}
			};
			dfs_low(start, -1);
			vector<pair<int, bool>> dsu(sz(e_up));
			rep(v, sz(dsu)) dsu[v].first = v;
			function<pair<int, bool> (int)> find = [&](int v) {
				if(dsu[v].first == v)
					return pair(v, false);
				auto [u, ub] = find(dsu[v].first);
				return dsu[v] = pair(u, ub ^ dsu[v].second);
			};
			auto onion = [&](int x, int y, bool flip) {
				auto [v, vb] = find(x);
				auto [u, ub] = find(y);
				if(v == u)
					return not (vb ^ ub ^ flip);
				dsu[v] = {u, vb ^ ub ^ flip};
				return true;
			};
			auto interlace = [&](const vi &ids, int lo) {
				vi ans;
				for(int e : ids)
					if(pre[e_up[e].second] > lo)
						ans.eb(e);
				return ans;
			};
			auto add_fu = [&](const vi &a, const vi &b) {
				fwd(k, 1, sz(a))
					if(not onion(a[k - 1], a[k], 0))
						return false;
				fwd(k, 1, sz(b))
					if(not onion(b[k - 1], b[k], 0))
						return false;
				return a.empty() or b.empty() or onion(a[0], b[0], 1);
			};
			function<bool (int, int)> dfs_planar = [&](int v, int p) {
				for(int u : dn[v])
					if(not dfs_planar(u, v))
						return false;
				rep(i, sz(dn[v])) {
					fwd(j, i + 1, sz(dn[v]))
						if(not add_fu(interlace(up[dn[v][i]], low[dn[v][j]]),
									  interlace(up[dn[v][j]], low[dn[v][i]])))
							return false;
					for(int j : up[v]) {
						if(e_up[j].first != v)
							continue;
						if(not add_fu(interlace(up[dn[v][i]], pre[e_up[j].second]),
									  interlace({j}, low[dn[v][i]])))
							return false;
					}
				}
				for(int u : dn[v]) {
					for(int idx : up[u])
						if(pre[e_up[idx].second] < pre[p])
							up[v].eb(idx);
					exchange(up[u], {});
				}
				return true;
			};
			if(not dfs_planar(start, -1))
				return false;
		}
	return true;
}