/**
 * Author: Krzysztof Potepa
 * Date: 2024
 * License: N/A
 * Description: Provides LCA, K-th ancestor and isAncestor queries in log(n) time with O(n) memory.
 */
struct LCA {
	vi par, jmp, depth, pre, post;
	int cnt = 0; LCA() {}
	LCA(vector<vi>& g, int v = 0) :
	par(sz(g), -1), jmp(sz(g), v),
	depth(sz(g)), pre(sz(g)), post(sz(g)) {
		dfs(g, v);
	}
	void dfs(vector<vi>& g, int v) {
		int j = jmp[v], k = jmp[j], x =
			depth[v]+depth[k] == depth[j]*2 ? k : v;
		pre[v] = ++cnt;
		for (auto e : g[v]) if (!pre[e]) {
			par[e] = v; jmp[e] = x;
			depth[e] = depth[v]+1;
			dfs(g, e);
		}
		post[v] = ++cnt;
	}
	int laq(int v, int d) {
		while (depth[v] > d)
			v = depth[jmp[v]] < d ? par[v] : jmp[v];
		return v;
	} // Lowest Common Ancestor; time: O(lg n)
	int operator()(int a, int b) {
		if (depth[a] > depth[b]) swap(a, b);
		b = laq(b, depth[a]);
		while (a != b) {
			if (jmp[a] == jmp[b])
				a = par[a], b = par[b];
			else
				a = jmp[a], b = jmp[b];
		}
		return a;
	} // Check if a is ancestor of b; time: O(1)
	bool isAncestor(int a, int b) {
		return pre[a] <= pre[b] &&
		       post[b] <= post[a];
	} // Get distance from a to b; time: O(lg n)
	int distance(int a, int b) {
		return depth[a] + depth[b] -
		       depth[operator()(a, b)]*2;
	} // Get k-th vertex on path from a to b,
	  // a is 0, b is last; time: O(lg n)
	  // Returns -1 if k > distance(a, b)
	int kthVertex(int a, int b, int k) {
		int c = operator()(a, b);
		if (depth[a]-k >= depth[c])
			return laq(a, depth[a]-k);
		k += depth[c]*2 - depth[a];
		return (k > depth[b] ? -1 : laq(b, k)); } };