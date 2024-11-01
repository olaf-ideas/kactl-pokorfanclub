/**
 * Author: none
 * Date: 2016-07-23
 * License: CC0
 * Source: me
 * Description: $O(\log a)$, liczy $\sum_{i=0}^{n-1} \left\lfloor \frac{a\cdot i + b}{c} \right\rfloor$. Działa dla $0 \leq a, b < c$ oraz $1\leq c, n \leq 10^9$.
 * Status: tested
 */
LL floor_sum(LL n, LL a, LL b, LL c) {
	LL ans = 0;
	if (a >= c) {
		ans += (n - 1) * n * (a / c) / 2;
		a %= c;
	}
	if (b >= c) {
		ans += n * (b / c);
		b %= c;
	}
	LL d = (a * (n - 1) + b) / c;
	if (d == 0) return ans;
	ans += d * (n - 1) - floor_sum(d, c, c - b - 1, a);
	return ans;
}