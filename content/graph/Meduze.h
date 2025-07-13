/**
 * Author: Krzysztof Olejnik
 * Date: 2025-07-13
 * License: CC0
 * Source: Folklore
 * Description: Utility for functional graphs. 
 *  Computes following tables: cs - vertices of ith comp's cycle,
 *  ci - index of comp, ti - index of tree in comp, idx - same
 *  as ti but -1 if not on cycle (i.e. not root), cl - length of
 *  ith component's cycle
 * Time: O(V) or O(VlogV) if lca 
 * Status: Tested on CSES
 */

#pragma once

vector<int> adjr[N], cs[N];
int vis[N], cn, tn, ci[N], id[N], ti[N], cl[N];
// int h[N], tin[N], tout[N], tim, up[N][K]; // lca
void dfs(int v, int p){
  ci[v] = cn; ti[v] = tn;
  // if(v != adj[p]) h[v] = h[p]+1; tin[v] = tim++; // lca
  // up[v][0] = (v == adj[p] ? v : p); // lca
  // for(int k=1;k<K;k++) up[v][k] = up[up[v][k-1]][k-1]; // lca
  for(auto u : adjr[v]){
    if(u == p) continue;
    dfs(u, v);
  } // tout[v] = tim++; // lca
} void init(){
  fill(ci,ci+n,-1); fill(id,id+n,-1);
  rep(i,0,n) adjr[adj[i]].push_back(i);
  rep(i,0,n) if(!vis[i]) {
    int v = i;
    while(!vis[v]) { vis[v] = 1; v = adj[v]; }
    if(ci[v] == -1){
      int u = adj[v]; tn = 0;
      do{dfs(u,v); id[u]=tn++; cs[cn].push_back(u); v=u; u=adj[u];}
        while(ci[u]==-1); cl[cn++] = tn; }}}