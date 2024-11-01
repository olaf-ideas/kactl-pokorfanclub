/**
 * Author: Tomek & Arek & Bartek
 * Date: 2024
 * License: ???
 * Source: https://raw.githubusercontent.com/tonowak/acmlib/master/code/graph/planar-graph-faces/main.cpp
 * Description: Read desc below.
 */

/*
 * complexity mlogm, assumes that you are given an embedding
 * graph is drawn straightline non-intersecting
 * returns combinatorial embedding (inner face vertices clockwise, outer counter clockwise).
 * WAZNE czasem trzeba zlaczyc wszystkie sciany zewnetrzne (chodzi o kmine do konkretnego zadania)
 * (ktorych moze byc kilka, gdy jest wiele spojnych) w jedna sciane.
 * Zewnetrzne sciany moga wygladac jak kaktusy, a wewnetrzne zawsze sa niezdegenerowanym wielokatem.
 */
struct Edge {
	int e, from, to;
	// face is on the right of "from -> to"
};
ostream& operator<<(ostream &o, Edge e) {
	return o << vector{e.e, e.from, e.to};
}
struct Face {
	bool is_outside;
	vector<Edge> sorted_edges;
	// edges are sorted clockwise for inside and cc for outside faces
};
ostream& operator<<(ostream &o, Face f) {
	return o << pair(f.is_outside, f.sorted_edges);
}
vector<Face> split_planar_to_faces(vector<pii> coord, vector<pii> edges) {
	int n = sz(coord);
	int E = sz(edges);
	vector<vi> graph(n);
	rep(e, E) {
		auto [v, u] = edges[e];
		graph[v].eb(e);
		graph[u].eb(e);
	}
	vi lead(2 * E);
	iota(lead.begin(), lead.end(), 0);
	function<int (int)> find = [&](int v) {
		return lead[v] == v ? v : lead[v] = find(lead[v]);
	};
	auto side_of_edge = [&](int e, int v, bool outward) {
		return 2 * e + ((v != min(edges[e].first, edges[e].second)) ^ outward);
	};
	rep(v, n) {
		vector<pair<pii, int>> sorted;
		for(int e : graph[v]) {
			auto p = coord[edges[e].first ^ edges[e].second ^ v];
			auto center = coord[v];
			sorted.eb(pair(p.first - center.first, p.second - center.second), e);
		}
		sort(all(sorted), [&](pair<pii, int> l0, pair<pii, int> r0) {
			auto l = l0.first;
			auto r = r0.first;
			bool half_l = l > pair(0, 0);
			bool half_r = r > pair(0, 0);
			if(half_l != half_r)
				return half_l;
			return l.first * LL(r.second) - l.second * LL(r.first) > 0;
		});
		rep(i, sz(sorted)) {
			int e0 = sorted[i].second;
			int e1 = sorted[(i + 1) % sz(sorted)].second;
			int side_e0 = side_of_edge(e0, v, true);
			int side_e1 = side_of_edge(e1, v, false);
			lead[find(side_e0)] = find(side_e1);
		}
	}
	vector<vi> comps(2 * E);
	rep(i, 2 * E)
		comps[find(i)].eb(i);
	vector<Face> polygons;
	vector<vector<pii>> outgoing_for_face(n);
	rep(leader, 2 * E)
		if(sz(comps[leader])) {
			for(int id : comps[leader]) {
				int v = edges[id / 2].first;
				int u = edges[id / 2].second;
				if(v > u)
					swap(v, u);
				if(id % 2 == 1)
					swap(v, u);
				outgoing_for_face[v].eb(u, id / 2);
			}
			vector<Edge> sorted_edges;
			function<void (int)> dfs = [&](int v) {
				while(sz(outgoing_for_face[v])) {
					auto [u, e] = outgoing_for_face[v].back();
					outgoing_for_face[v].pop_back();
					dfs(u);
					sorted_edges.eb(e, v, u);
				}
			};
			dfs(edges[comps[leader].front() / 2].first);
			reverse(all(sorted_edges));
			LL area = 0;
			for(auto edge : sorted_edges) {
				auto l = coord[edge.from];
				auto r = coord[edge.to];
				area += l.first * LL(r.second) - l.second * LL(r.first);
			}
			polygons.eb(area >= 0, sorted_edges);
		}
	// Remember that there can be multiple outside faces.
	return polygons;
}