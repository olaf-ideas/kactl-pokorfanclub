/**
 * Author: kobor, Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2024-08-23
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

struct HLD {	// 0-indexed
	int N, tim = 0, VALS_EDGES = 0;	// change to 1 if needed
	vector<vi> adj; vi par, sz, depth, rt, pos;
	HLD(vector<vi> _adj) : N(SZ(_adj)), adj(_adj), par(N, -1),
		sz(N, 1), depth(N), rt(N), pos(N) { dfsSz(0); dfsHld(0); }
	void dfsSz(int v) {
		if(par[v] != -1) adj[v].erase(find(all(adj[v]), par[v]));
		for(int &u: adj[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfsSz(u); sz[v] += sz[u];
			if(sz[u] > sz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v) {
		pos[v] = tim++;
		for(int u: adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u); dfsHld(u); }
	}
	vector<pii> path(int u, int v) {
		vector<pii> paths;
		for(; rt[u] != rt[v]; v = par[rt[v]]) {
			if(depth[rt[u]] > depth[rt[v]]) swap(u, v);
			paths.pb({pos[rt[v]], pos[v]});
		}
		if(depth[u] > depth[v]) swap(u, v);
		paths.pb({pos[u] + VALS_EDGES, pos[v]});
		return paths;
	}
	pii subtree(int v) {
		return {pos[v] + VALS_EDGES, pos[v] + sz[v] - 1};
	}
};
