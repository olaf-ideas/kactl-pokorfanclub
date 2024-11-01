
/**
 * Author: Benjamin Qi
 * Description: Schreier-Sims lets you
 * add a permutation to a group,
 * count number of permutations in a group,
 * test whether a permutation is a member of a group.
 * Works well for $n \le 15$, maybe for larger too.
 * Construct PermGroup() and run order() to get order of the group.
 * Time: O(n^6)
 * Source: MIT NULL
 * see Zlobober's post in Russian version
 * of https://codeforces.com/blog/entry/21335
 */


vi inv(vi v) { vi V(sz(v)); rep(i,sz(v)) V[v[i]]=i; return V; }
vi id(int n) { vi v(n); iota(all(v),0); return v; }
vi operator*(const vi& a, const vi& b) {
	vi c(sz(a)); rep(i,sz(a)) c[i] = a[b[i]];
	return c;
}

struct PermGroup {
	struct Group {
		vi flag;
		vector<vi> gen, sigma; 
		// sigma[t][k] = t, sigma[t][x] = x if x > k
		Group(int n, int p) : flag(n), sigma(n) {
				flag[p] = 1; sigma[p] = id(n);
		}
	};

	int n = 0; vector<Group> g;
	PermGroup() {}

	bool check(const vi& cur, int k) {
		if (!k) return 1;
		int t = cur[k];
		return g[k].flag[t] ? check(inv(g[k].sigma[t])*cur,k-1) : 0;
	}
	void updateX(const vi& cur, int k) {
		int t = cur[k]; // if flag, fixes k -> k
		if (g[k].flag[t]) ins(inv(g[k].sigma[t])*cur,k-1);
		else {
				g[k].flag[t] = 1, g[k].sigma[t] = cur;
				for(auto x: g[k].gen)
					updateX(x*cur,k);
		}
	}
	void ins(const vi& cur, int k) {
		if (check(cur,k)) return;
		g[k].gen.pb(cur);
		rep(i,n) if (g[k].flag[i]) updateX(cur*g[k].sigma[i],k);
	}

	ll order(vector<vi> gen) {
		if(sz(gen) == 0) return 1;
		n = sz(gen[0]);
		rep(i,n) g.pb(Group(n,i));
		for(auto a: gen)
				ins(a, n-1); // insert perms into group one by one
		ll tot = 1; // watch out for overflows, can be up to n!
		rep(i,n) {
				int cnt = 0;
				rep(j,i+1) cnt += g[i].flag[j];
				tot *= cnt;
		}
		return tot;
	}
};
