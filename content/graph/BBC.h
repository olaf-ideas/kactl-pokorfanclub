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
 *  rep(i,0,n) if(!tin[i]) {tim=1;st.clear();dfs(i,-1);}
 * Time: O(E + V)
 * Status: tested on yosupo and XXIII POI task
 */
#pragma once

int tim=1, tin[N], low[N], art[N]; vi st;
vector<pii> ste, edgs[N]; vector<vi> bl;
void dfs(int v, int p){ st.pb(v); tin[v] = low[v] = tim++;
  if(!adj[v].size()) bl.pb({v}), st.pop_back();
  for(auto& [u, e] : adj[v]){ if(e == p) continue; // if(u == p)
    if(tin[u] < tin[v]) ste.eb(v,u); 
    if(tin[u]) low[v] = min(low[v], tin[u]);
    else{ dfs(u, e); low[v] = min(low[v], low[u]);
      if(low[u] >= tin[v]){ art[v] = (tin[v] > 1 || tin[u] > 2);
        do{edgs[sz(bl)].pb(ste.back()); ste.pop_back();}
        while(edgs[sz(bl)].back() != mp(v,u)); bl.pb({v});
        while(bl.back().back() != u){bl.back().pb(st.back()); st.pop_back();}}}}}