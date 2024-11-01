/**
 * Author: Krzysztof Potępa
 * Date: 2022-10-27
 * License: ???
 * Source: ???
 * Description: Computes plaindromic tree: for each end position in the string
 * we store longest palindrome ending in that position. \texttt{link} is the
 * suffix palindrome links, eg ababa -> aba. Can be used to compute shortest
 * decomposition of strings to palindromes in O(n log n) time - use [DP] lines.
 * Time: O(N)
 */
#pragma once

constexpr int ALPHA = 26;
struct PalTree {
	vi txt; //;Node 0=empty pal (root of even), 1="-1" pal (of odd)
	vi len{0, -1}; // Lengths of palindromes
	vi link{1, 0}; // Suffix palindrome links, eg [ababa] -> [aba]
	vector<array<int, ALPHA>> to{{}, {}}; // egdes, ex: aba -c> cabac
	int last{0}; // Current node (max suffix pal)
	vi diff{0, 0};  //[DP] len[i]-len[link[i]]
	vi slink{0, 0}; //[DP] like link but to having different `diff`
	vi series{0, 0};//[DP] dp for series (groups of pals with =diff)
	vi ans{0};      //[DP] ans for prefix
	int ext(int i) {
		while(len[i]+2>sz(txt) || txt[sz(txt)-len[i]-2]!=txt.back())
			i = link[i];
		return i;
	}
	void add(int x) {//x in [0,ALPHA), time O(1) or O(lg n) for DP
		txt.pb(x); last = ext(last);
		if(!to[last][x]) {
			len.pb(len[last] + 2);
			link.pb(to[ext(link[last])][x]);
			to[last][x] = sz(to);
			to.pb({});
			diff.pb(len.back() - len[link.back()]); //[DP]
			slink.pb(diff.back() == diff[link.back()] ? slink[link.back()] : link.back()); //[DP]
			series.pb(0); //[DP]
		}
		last = to[last][x];
		ans.pb(INT_MAX); //[DP]
		for(int i = last; len[i] > 0; i = slink[i]) { //[DP]
			series[i] = ans[sz(ans) - len[slink[i]] - diff[i] - 1]; //[DP]
			if(diff[i] == diff[link[i]]) //[DP]
				series[i] = min(series[i], series[link[i]]); //[DP]
			//For even only palindromes set ans only for even sz(txt) //[DP]
			ans.back() = min(ans.back(), series[i] + 1); //[DP]
		}
	}
};
