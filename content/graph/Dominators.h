/**
 * Author: Krzysztof Potępa
 * Date: 2024
 * License: CC0
 * Description: Tarjan's dominators in directed graph
 * Returns tree (as array of parents) of immediate dominators idom.
 * idom[root] = root, idom[v] = -1 if v is unreachable from root
 * Time: O(|E| log |V|)
 */
vi dominators(vector<vi>& G, int root) {
	int n = sz(G); vector<vi> in(n), bucket(n);
	vi pre(n, -1), anc(n, -1), par(n), best(n);
	vi ord, idom(n, -1), sdom(n, n), rdom(n);
	auto dfs = [&] (auto f, int v, int p) -> void {
		if (pre[v] == -1) {
			par[v] = p; pre[v] = sz(ord);
			ord.pb(v);
			for (auto e :  G[v])
				in[e].pb(v), f(f, e, v);
		}
	};
	auto find = [&](auto f, int v) -> pii {
		if (anc[v] == -1) return {best[v], v};
		int b; tie(b, anc[v]) = f(f, anc[v]);
		if (sdom[b] < sdom[best[v]]) best[v] = b;
		return {best[v], anc[v]};
	};
	rdom[root] = idom[root] = root;
	iota(all(best), 0); dfs(dfs, root, -1);
	rep(i, sz(ord)) {
		int v = ord[sz(ord)-i-1], b = pre[v];
		for (auto e : in[v])
			b = min(b, pre[e] < pre[v] ? pre[e] :
			sdom[find(find, e).st]);
		for (auto u : bucket[v]) rdom[u]=find(find,u).st;
		sdom[v] = b; anc[v] = par[v];
		bucket[ord[sdom[v]]].pb(v);
	}
	for (auto v : ord) idom[v] = (rdom[v] == v ?
		ord[sdom[v]] : idom[rdom[v]]);
	return idom; }