/**
 * Author: kobor
 * Date: 2024-07-21
 * License: CC0
 * Source: https://codeforces.com/blog/entry/61203
 * Description: Useful speed up for MoQueries.
 * Time: O(\log N)
 * Status: unknown
 */
#pragma once

ll hilbertOrder(int x, int y, int pow = 20, int rotate = 0) {
	if(pow == 0) return 0;
	int hpow = 1 << (pow - 1);
	int seg = x < hpow ? (y < hpow ? 0:3) : (y < hpow ? 1:2);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	ll subSquareSize = 1ll << (pow * 2 - 2);
	ll ans = seg * subSquareSize;
	ll add = hilbertOrder(nx, ny, pow - 1, nrot);
	ans += seg == 1 || seg == 2 ? add : (subSquareSize - add-1);
	return ans;
}
