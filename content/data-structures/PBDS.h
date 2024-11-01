/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: Policy Based Data Structures
 */
#pragma once

// Order Statistics Tree: Caution: Not a multiset!
#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

Tree<int> t, t2;
auto it = t.insert(10).first; // it == t.upper_bound(9);
t.order_of_key(10); // # of entries strictly smaller than key
t.join(t2); // fast only if max(T) < min(T2) or min(T) > max(T2)

// Hash Table: faster but can lead to MLE (1.5x worse performance), initial capacity must = 2^k
struct chash { // large odd number for C
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x * C); }
};
gp_hash_table<ll, int, chash> h({}, {}, {}, {}, {1 << 16}); // cc_hash_table also exists if needed
