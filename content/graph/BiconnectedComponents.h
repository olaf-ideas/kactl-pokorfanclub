/**
 * Author: Krzysztof Olejnik
 * Date: 2025-07-12
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected graph.
 *  In a biconnected component there are at least two distinct paths between any 
 * 	two nodes. Note that a node can be in several components. An edge which is 
 *  not in a component is a bridge i.e., not part of any cycle. bls contains
 *  vertices of bbcs, edgs edges of bbcs, bl[i] = max id of bls vertex i belongs to.
 * Usage:
 *  for each edge (a,b) {
 *    adj[a].emplace_back(b, eid);
 *    adj[b].emplace_back(a, eid++); }
 *  for(int i=0;i<n;i++) if(!tin[i]) {tim=1;st.clear();dfs(i,-1)};
 * Time: O(E + V)
 * Status: tested on yosupo and XXIII POI task
 */
#pragma once

int tim=1, tin[N], low[N], isart[N], bl[N]; vi st;
vector<pii> ste, edgs[N]; vector<vi> bls;
void dfs(int v, int p){ st.pb(v); tin[v] = low[v] = tim++;
  if(!adj[v].size()) 
    bl[st.back()] = sz(bls)-1, bls.push_back({v}), st.pop_back();
  for(auto& [u, e] : adj[v]){ if(e == p) continue; // if(u == p)
    if(tin[u] < tin[v]) ste.eb(v,u);
    if(tin[u]) low[v] = min(low[v], tin[u]);
    else{ dfs(u, e); low[v] = min(low[v], low[u]);
      if(low[u] >= tin[v]){ isart[v] = (tin[v] > 1 || tin[u] > 2);
        edgs[sz(bls)].pb(ste.back()); ste.pop_back();
        while(edgs[sz(bls)].back() != mp(v,u)){
          edgs[sz(bls)].pb(ste.back()); ste.pop_back();
        } bls.pb({v});
        while(bls.back().back() != u){ bl[st.back()] = sz(bls)-1;
          bls.back().pb(st.back()); st.pop_back(); }}}}}