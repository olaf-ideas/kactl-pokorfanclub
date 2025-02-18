/**
 * Author: Anadi, kobor
 * Date: 2024-07-17
 * License: CC0
 * Source: Anadi
 * Description: Given a rooted tree computes the result of Red-Blue Hackenbush game.
 * 	If result != 0 then \{result\} always wins, otherwise the second player to go wins.
 * Time: O(N \log N)
 * Status: tested on codechef:GERALD08
 */
#pragma once

struct Surreal {
	int value = 0, offset = 0; set<int> powers;
	int sign() {
		int tmp = 2 * value + !powers.empty();
		return tmp < 0 ? -1 : (tmp > 0);
	}
	int add_power(int power) {
		while(power) {
			if(!powers.count(power - offset)) {
				powers.insert(power - offset); break; }
			powers.erase(power - offset); power--;
		}
		return !power;
	}
	void operator+=(const Surreal &v) {
		value += v.value;
		for(int power: v.powers)
			value += add_power(power + v.offset);
	}
	void divide(int power) {
		offset += power; int to_add = 0;
		FOR(i, 0, power) {
			if(value & 1) to_add += add_power(power - i);
			value >>= 1;
		}
		value += to_add;
	}
	void get_next(int t) {
		int power = max(0, -t * value); value += t * (power + 1);
		if(value == -1 || (value == 1 && powers.empty())) {
			power++, value += t; }
		divide(power);
	}
};

struct RedBlueHack { /* Weights on edges should be -1 or 1 */
	vector<vector<pii>> G; vector<Surreal> ans;
	RedBlueHack(vector<vector<pii>> _G) : G(_G), ans(SZ(G)) {}
	void dfs(int u, int p) {
		for(auto &[v, w]: G[u]) if(v != p) {
			dfs(v, u); ans[v].get_next(w);
			if(SZ(ans[u].powers) < SZ(ans[v].powers)) {
				swap(ans[u], ans[v]); }
			ans[u] += ans[v];
		}
	}
	int run() { dfs(0, 0); return ans[0].sign(); }
};
