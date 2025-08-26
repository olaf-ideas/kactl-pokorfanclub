/**
 * Author: Krzysztof Olejnik
 * Date: 2025-07-13
 * License: CC0
 * Source: Folklore
 * Description: SCC's
 * Time: O(E + V)
 * Status: Tested on CSES
 */
#pragma once

vector<int> ord; int comp, id[N], vis[N];
void dfs(int v){ vis[v] = 1;
    for(auto u : adj[v]) if(!vis[u]) dfs(u); ord.push_back(v);
} void dfs2(int v){ vis[v] = 1; id[v] = comp;
    for(auto u : adjr[v]) if(!vis[u]) dfs2(u);
} void init(){
    fill(vis,vis+n,0);
    rep(i,0,n) if(!vis[i]) dfs(i);
    fill(vis,vis+n,0); rev(all(ord));
    for(auto v : ord) if(!vis[v]) dfs2(v), comp++;}
