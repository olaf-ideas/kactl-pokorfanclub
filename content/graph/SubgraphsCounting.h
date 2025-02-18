/**
 * Author: tonowak, kobor
 * Date: 2024-07-19
 * License: MIT
 * Source: https://github.com/tonowak/acmlib/blob/master/code/graph/triangles/main.cpp
 * Description: Given simple undirected graph, counts all 3- and 4-edges subgraphs.
 * Time: O(E \sqrt E)
 * Status: unknown
 */
#pragma once

struct Subgraphs {
	int triangles3 = 0;
	ll stars3 = 0, paths3 = 0;
	ll ps4 = 0, rectangles4 = 0, paths4 = 0;
	__int128 ys4 = 0, stars4 = 0;
	Subgraphs(vector<vi> &G) {
		int n = SZ(G); vector<pii> deg(n);
		FOR(i, 0, n) deg[i] = {SZ(G[i]), i};
		sort(all(deg)); vi id(n), cnt(n);
		FOR(i, 0, n) id[deg[i].nd] = i;
		FOR(v, 0, n) {
			for(int u: G[v]) if(id[v] > id[u]) cnt[u] = 1;
			for(int u: G[v]) if(id[v] > id[u])
				for(int w: G[u]) if(id[w] > id[u] && cnt[w]) {
					triangles3++;
					for(int x: {v, u, w}) ps4 += SZ(G[x]) - 2;
				}
			for(int u: G[v]) if(id[v] > id[u]) cnt[u] = 0;
			for(int u: G[v]) if(id[v] > id[u])
				for(int w: G[u]) if(id[v] > id[w]) {
					rectangles4 += cnt[w]++;
				}
			for(int u: G[v]) if(id[v] > id[u])
				for(int w: G[u]) cnt[w] = 0;
		}
		paths3 = -3 * triangles3;
		FOR(v, 0, n) for(int u: G[v])
			if(v < u) paths3 += ll(SZ(G[v]) - 1) * (SZ(G[u]) - 1);
		ys4 = -2 * ps4;
		auto choose2 = [&](int x) { return x * ll(x - 1) / 2; };
		FOR(v, 0, n) for(int u: G[v]) {
			ys4 += (SZ(G[v]) - 1) * choose2(SZ(G[u]) - 1);
		}
		paths4 = -(4 * rectangles4 + 2 * ps4 + 3 * triangles3);
		FOR(v, 0, n) {
			int x = 0;
			for(int u: G[v]) {
				x += SZ(G[u]) - 1;
				paths4 -= choose2(SZ(G[u]) - 1);
			}
			paths4 += choose2(x);
		}
		FOR(v, 0, n) {
			int s = SZ(G[v]);
			stars3 += s * ll(s - 1) * (s - 2);
			stars4 += s * (__int128)(s - 1) * (s - 2) * (s - 3);
		}
		stars3 /= 6; stars4 /= 24;
	}
};
