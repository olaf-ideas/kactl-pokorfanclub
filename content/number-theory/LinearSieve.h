/**
 * Author: kobor
 * Date: 2024-07-21
 * Source: https://codeforces.com/blog/entry/54090
 * Description: Usefull for computing values of multiplicative function and its prefix sums.
 * Time: O(N)
 * Status: tested with PrefixSumMultiplicative
 */
#pragma once

struct LinearSieve {
	vector<bool> isComposite; vi prime, cnt;
	vector<ll> phi, prefPhi;
	ll dPhi(ll x, int p, int a) { // x / phi(p^(a-1)) * phi(p^a)
		return x * (a == 1 ? p - 1 : p);
	}
	LinearSieve(int n) : isComposite(n), cnt(n), phi(n) {
		if(n > 1) phi[1] = 1;
		FOR(i, 2, n) {
			if(!isComposite[i]) {
				prime.pb(i), cnt[i] = 1, phi[i] = dPhi(1, i, 1);
			}
			FOR(j, 0, SZ(prime)) {
				if(i * prime[j] >= n) break;
				isComposite[i * prime[j]] = 1;
				if(i % prime[j] == 0) {
					cnt[i * prime[j]] = cnt[i] + 1;
					phi[i*prime[j]] = dPhi(phi[i], prime[j], cnt[i]+1);
					break;
				}
				else {
					cnt[i * prime[j]] = 1;
					phi[i * prime[j]] = phi[i] * phi[prime[j]];
				}
			}
		}
		partial_sum(all(phi), back_inserter(prefPhi));
	}
};
