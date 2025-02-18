/**
 * Author: kobor
 * Date: 2024-07-17
 * License: CC0
 * Source: https://codeforces.com/blog/entry/102085
 * Description: Given a non-negative weighted directed graph, computes lengths of K shortest walks (vertices can repeat).
 *  For graphs with negative weights, try your luck or change Dijkstra to SPFA.
 * Time: O((M + K) \log N)
 * Status: tested on a few tasks
 */
#pragma once

struct PersistentHeap {
	struct Node {
		int id, l = -1, r = -1; ll cost;
		Node(int _id, ll _cost) : id(_id), cost(_cost) {}
	};
	vector<Node> ds;
	int add(int id, ll cost) {
		ds.pb(Node(id, cost)); return SZ(ds) - 1;
	}
	int ins(int v, int u) {
		if(v == -1) return u;
		ds.pb(ds[v]); v = SZ(ds) - 1; swap(ds[v].l, ds[v].r);
		if(ds[v].cost > ds[u].cost) {
			swap(ds[v].cost, ds[u].cost), swap(ds[v].id, ds[u].id);
		}
		ds[v].r = ins(ds[v].r, u); return v;
	}
	void insert(int &v, int u) { v = ins(v, u); }
};

vector<ll> kWalk(vector<vector<pii>> G, int s, int t, int k) {
	int n = SZ(G); vector<vector<pii>> GR(n);
	FOR(v, 0, n) for(auto &[u, d]: G[v]) GR[u].pb({v, d});
	const ll INF = 1e18; vector<ll> dist(n, INF); vi par(n, -1);
	using T = pair<ll, int>; dist[t] = 0;
	priority_queue<T, vector<T>, greater<T>> q; q.push({0, t});
	while(!q.empty()) {
		auto [dv, v] = q.top(); q.pop();
		if(dv != dist[v]) continue;
		for(auto &[u, d]: GR[v]) if(dv + d < dist[u]) {
			par[u] = v; dist[u] = dv + d; q.push({dist[u], u});
		}
	}
	vector<vi> tree(n);
	FOR(v, 0, n) if(~par[v]) tree[par[v]].pb(v);
	PersistentHeap heap; vi head(n, -1);
	function<void(int)> dfs = [&](int v) {
		bool skip = 0;
		for(auto &[u, d]: G[v]) if(dist[u] != INF) {
			if(dist[v] == dist[u] + d && par[v] == u && !skip)
				skip = 1;
			else
				heap.insert(head[v], heap.add(u, dist[u]-dist[v]+d));
		}
		for(int u: tree[v]) head[u] = head[v], dfs(u);
	}; dfs(t);
	vector<ll> ans(k, -1); q.push({dist[s], heap.add(s, 0)});
	FOR(i, 0, k) {
		if(q.empty() || dist[s] == INF) break;
		auto [dv, v] = q.top(); q.pop();
		ans[i] = dv; auto &node = heap.ds[v]; ll diff = 0;
		for(int u: {head[node.id], node.l, node.r}) {
			if(~u) q.push({dv + heap.ds[u].cost - diff, u});
			diff = node.cost;
		}
	}
	return ans;
}
