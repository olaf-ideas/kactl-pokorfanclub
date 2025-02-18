/**
 * Author: Benq, kobor
 * Date: 2024-07-12
 * License: CC0
 * Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/graphs%20(12)/Matching/GeneralMatchBlossom.h
 * Description: Unweighted matching for general graphs.
 * If \texttt{white[v] = 0} at the end, \texttt{v} is part of every max matching.
 * Time: O(NM), faster in practice
 * Status: tested on a few tasks
 */
#pragma once

struct MaxMatching {	// 1-indexed
	vector<vi> G; int n;
	vi mate, par, white; vector<pii> l;
	MaxMatching(vector<vi> _G) : G(_G), n(SZ(G)), mate(n),
		par(n), white(n), l(n) {}
	int group(int x) {
		return par[x] = (white[par[x]] ? group(par[x]) : par[x]);
	}
	void match(int p, int b) {
		swap(mate[p], b); if(mate[b] != p) return;
		if(!l[p].nd) mate[b] = l[p].st, match(l[p].st, b);
		else match(l[p].st, l[p].nd), match(l[p].nd, l[p].st);
	}
	bool augment(int a) {
		white[a] = 1; par[a] = 0; l[a] = {0, 0};
		queue<int> q; q.push(a);
		while(!q.empty()) {
			a = q.front(); q.pop();
			for(int b: G[a]) {
				if(white[b]) {
					int x = group(a), y = group(b), lca = 0;
					while(x || y) {
						if(y) swap(x, y);
						if(l[x] == mp(a, b)) { lca = x; break; }
						l[x] = {a, b}; x = group(l[mate[x]].st);
					}
					for(int v: {group(a), group(b)}) while(v != lca) {
						q.push(v); white[v] = 1; par[v] = lca;
						v = group(l[mate[v]].st);
					}
				} else if(!mate[b]) {
					mate[b] = a; match(a, b); fill(all(white), 0);
					return 1;
				} else if(!white[mate[b]]) {
					white[mate[b]] = 1; par[mate[b]] = b;
					l[b] = {0, 0}; l[mate[b]] = {a, 0};
					q.push(mate[b]);
				}
			}
		}
		return 0;
	}
	int max_matching() {
		int ans = 0;
		FOR(v, 1, n) if(!mate[v]) ans += augment(v);
		return ans;
	}
};
