#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("popcnt,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define ld long double

#define endl '\n'
#define st first
#define nd second
#define pb push_back
#define eb emplace_back
#define sz(x) (int)(x).size()
#define all(x) begin(x),end(x)
#define FOR(i,l,r) for(int i=(l);i<=(r);i++)
#define ROF(i,r,l) for(int i=(r);i>=(l);i--)

#ifdef DEBUG
auto&operator<<(auto&o,pair<auto,auto>p){return o<<"("<<p.first<<", "<<p.second<<")";}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<"{";int i=0;for(auto e:x)o<<","+!i++<<e;return o<<"}";}
#define debug(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X)
#else
#define debug(...){}
#endif

#define rep(i,a,b) for(int i = a; i < (b); i++)
typedef pair<int, int> pii;
typedef vector<int> vi;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	return 0;
}
