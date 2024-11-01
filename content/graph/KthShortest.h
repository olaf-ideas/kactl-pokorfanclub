/**
 * Author: Krzysztof Potępa
 * Date: 2024
 * License: N/A
 * Description: Given directed weighted graph with non-negative edge weights gets K-th shortest walk (not necessarily simple) in O(log|E|). -1 if no next path (can only happen in DAG). WARNING: USES KLOGM memory and persistent heaps!
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
#pragma once
constexpr ll INF = 1e18;
struct Eppstein {
	using T = ll; using Edge = pair<int, T>;
	struct Node { int E[2] = {}, s = 0; Edge x; };
	T shortest; // Shortest path length
	priority_queue<pair<T, int>> Q;
	vector<Node> P{1}; vi h;
	Eppstein(vector<vector<Edge>>& G, int s, int t) {
		int n = sz(G); vector<vector<Edge>> H(n);
		rep(i,n) for(auto &e : G[i])
			H[e.st].pb({i,e.nd});
		vi ord, par(n, -1); vector<T> d(n, -INF);
		Q.push({d[t] = 0, t});
		while (!Q.empty()) {
			auto v = Q.top(); Q.pop();
			if (d[v.nd] == v.st) {
				ord.pb(v.nd);
				for(auto &e : H[v.nd])
				if (v.st-e.nd > d[e.st]) {
					Q.push({d[e.st] = v.st-e.nd, e.st});
					par[e.st] = v.nd;
				}
			}
		}
		if ((shortest = -d[s]) >= INF) return;
		h.resize(n);
		for(auto &v : ord) {
			int p = par[v]; if (p+1) h[v] = h[p];
			for(auto &e : G[v]) if (d[e.st] > -INF) {
				T k = e.nd - d[e.st] + d[v];
				if (k || e.st != p)
					h[v] = push(h[v], {e.st, k});
				else p = -1;
			}
		}
		P[0].x.st = s; Q.push({0, 0});
	}
	int push(int t, Edge x) {
		P.pb(P[t]);
		if (!P[t = sz(P)-1].s || P[t].x.nd >= x.nd)
			swap(x, P[t].x);
		if (P[t].s) {
			int i = P[t].E[0], j = P[t].E[1];
			int d = P[i].s > P[j].s;
			int k = push(d ? j : i, x);
			P[t].E[d] = k; // Don't inline k!
		}
		P[t].s++; return t;
	}
	ll nextPath() { // next length, -1 if no next path
		if (Q.empty()) return -1;
		auto v = Q.top(); Q.pop();
		for (int i : P[v.nd].E) if (i)
			Q.push({ v.st-P[i].x.nd+P[v.nd].x.nd, i });
		int t = h[P[v.nd].x.st];
		if (t) Q.push({v.st - P[t].x.nd, t });
		return shortest - v.st; } };