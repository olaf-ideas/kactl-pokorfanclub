/**
 * Author: none
 * Date: 2017-04-18
 * Source: none
 * Description: assumes n >= 2, O(n).
 * Time: O(n^2)
 * Status: tested on SPOJ CH3D
 */
#include "../convex-hull/main.cpp"

pair<P, P> furthest_pair(vector<P> in) {
	in = hull(in);
	int n = ssize(in), j = 1;
	pair<D, pair<P, P>> ret;
	REP(i, j)
		for(;; j = (j + 1) % n) {
			ret = max(ret, {dist(in[i], in[j]), {in[i], in[j]}});
			if (sign(cross(in[(j + 1) % n] - in[j], in[i + 1] - in[i])) <= 0)
				break;
		}
	return ret.second;
}