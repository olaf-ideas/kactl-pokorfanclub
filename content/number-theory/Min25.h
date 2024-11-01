/**
 * Author: Kacper Topolski
 * Date: 2024-07-31
 * License: N/A
 * Source: https://codeforces.com/blog/entry/92703
 * Description: Calculates prefsums of multiplicative function at each floor(N/i). keys[id(N/i)]=N/i.
 * Remember about overflows. See example below.
 * Time: O(\frac{n^{3/4}}{\log n})
 * Status: Stress-tested
 */
#pragma once

vector<ll> global_primes; // global_primes[-1]>sqrt(N)

template<typename T>
struct Min25 {
	ll N;
	vector<ll> keys, primes;
	Min25(ll N_) : N(N_) {
		for (ll l = 1; l <= N; ++l)
			keys.pb(l = N / (N / l));
		for (int i = 0; global_primes[i] * global_primes[i] <= N; ++i)
			primes.pb(global_primes[i]);
	}
	ll id(ll x) {
		ll id = x < N / x ? x - 1 : sz(keys) - N / x;
		assert(keys[id] == x);
		return id;
	}
// f has to be TOTALLY multiplicative
// pref(x) is regular prefix sum function of f
	vector<T> overPrimes(auto pref) {
		vector<T> dp(sz(keys));
		rep(i, sz(keys))
			dp[i] = pref(keys[i]) - T(1);
		for (ll p : primes) {
			auto fp = dp[p - 1] - dp[p - 2];
			for (int i = sz(keys) - 1; i >= 0 && p * p <= keys[i]; --i)
				dp[i] = dp[i] - (dp[id(keys[i] / p)] - dp[p - 2]) * fp;
		}
		return dp;
	}
// dp are prefix sums of f over primes
// f(p, k, p**k) calculates f on primes powers
	void fullSum(vector<T> &dp, auto f) {
		for (ll p : primes | views::reverse) {
			for (int i = sz(keys) - 1; i >= 0 && p * p <= keys[i]; --i) {
				for (ll k = 1, q = p; q * p <= keys[i]; ++k, q *= p)
					dp[i] = dp[i] + f(p, k + 1, q * p) + f(p, k, q) * (dp[id(keys[i] / q)] - dp[p - 1]);
			}
		}
		for (auto &v : dp) v = v + T(1);
	}
};

vector<ll> exampleUsage(Min25<ll> &m) { // OVERFLOWS!
	auto primeCnt = m.overPrimes([](ll x){return x; });
	auto primeSum = m.overPrimes([](ll x){return x*(x+1)/2; });
	vector<ll> phi; rep(i, sz(m.keys))
		phi.pb(primeSum[i] - primeCnt[i]);
	m.fullSum(phi, [](int p,int k,ll pk){return pk-pk/p; });
	return phi; }
