/**
 * Author: kobor
 * Date: 2024-07-17
 * License: CC0
 * Source: https://github.com/ShahjalalShohag/code-library/blob/main/Game%20Theory/Green%20Hackenbush.cpp
 * Description: Given a rooted graph computes the nimber of Green Hackenbush game.
 *  Rule one: for a tree, nimber of a root is a xorsum of (son's nimber + 1).
 * 	Rule two: when u and v lies on a cycle, then they can be contracted.
 * Time: O(N)
 * Status: tested on spoj:PT07A
 */
#pragma once

struct GreenHack {
	vector<vi> G; vi pre, low; int T = 0;
	GreenHack(vector<vi> _G) : G(_G), pre(SZ(G)), low(SZ(G)) {}
	int dfs(int v, int p) {
		pre[v] = low[v] = ++T; int ans = 0;
		for(int u: G[v]) {
			if(u == p) { p += SZ(G) + 1; continue; }
			if(!pre[u]) {
				int son = dfs(u, v); low[v] = min(low[v], low[u]);
				if(pre[v] < low[u]) ans ^= (son + 1);
				else ans ^= son ^ 1;
			}
			else if(pre[v] <= pre[u]) ans ^= 1;
			else low[v] = min(low[v], pre[u]);
		}
		return ans;
	}
	int run() { return dfs(0, -1); }
};
