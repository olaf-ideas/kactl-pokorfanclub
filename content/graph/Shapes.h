/**
 * Author: Antoni Długosz
 * Date: 2024
 * License: N/A
 * Description: Counts all subgraph shapes with at most 4 edges. No multiedges / loops allowed;
 * Time: O(m \sqrt{m})
 */

struct Shapes {
	ll tri = 0, rect = 0, path3 = 0, path4 = 0, star3 = 0, p = 0;
	__int128_t y = 0, star4 = 0;
	Shapes(vector<vi> &g) {
		int n = sz(g);
		vector<vi> h(n);
		vector<ll> f(n), c(n), s(n);
		rep(v, n) f[v] = (s[v] = sz(g[v])) * n + v;
		rep(v, n) {
			ll x = 0;
			star3 += s[v] * (s[v] - 1) * (s[v] - 2);
			star4 += __int128_t(s[v] - 1) * s[v] * (s[v] - 2) * (s[v] - 3);
			for (auto u : g[v]) {
				path4 += s[u] * x - x; x += s[u] - 1;
				y += (s[v] - 1) * (s[u] - 1) * (s[u] - 2) / 2;
				if (f[u] < f[v]) h[v].pb(u);
			}
		}
		rep(v, n) {
			for (int u : h[v])
				for (int w : g[u]) if (f[v] > f[w])
					rect += c[w] ++;
			for(int u : h[v]) {
				tri += c[u]; c[u] *= -1;
				path3 += (s[v] - 1) * (s[u] - 1);
				for(int w : g[u])
					if (c[w] < 0)
						p += s[v] + s[u] + s[w] - 6, c[w] ++;
					else if (c[w] > 0)
						c[w] --;
			}
		}
		path3 -= 3 * tri;
		y -= 2 * p;
		path4 -= 4 * rect + 2 * p + 3 * tri;
		star3 /= 6;
		star4 /= 24;
	}
};