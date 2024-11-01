/**
 * Author: Antek Dlugosz
 * License: CC0
 * Source: folklore
 * Description: Optimize dp where you want "k things with minimal cost". The slope of f(k) must be
 non increasing. Provide a function g(lambda) that computes the best answer for any k with costs increased by lambda.
 * Status: tested on https://codeforces.com/contest/1197/problem/C and https://codeforces.com/contest/1279/problem/F
 */
#pragma once

ll aliens(ll k, auto g) { // returns f(k)
	ll l = 0, r = 1e11; // make sure lambda range [l, r) is ok (r > max slope etc)
	while (l + 1 < r) {
		ll m = (l + r) / 2;
		(g(m - 1) + k <= g(m) ? l : r) = m;
	}
	return g(l) - l * k; // return l if you want the optimal lambda
}