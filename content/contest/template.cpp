#include "bits/stdc++.h"
using namespace std;

#define int long long
#define ll long long
#define ld long double

#define endl '\n'
#define st first
#define nd second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define sz(x) (int)(x).size()
#define all(x) begin(x),end(x)
#define FOR(i,l,r) for(int i=(l);i<=(r);i++)
#define ROF(i,r,l) for(int i=(r);i>=(l);i--)

#define _$ auto operator<<(auto&o,auto x)->decltype
_$(x.st,o){return o<<"("<<x.st<<", "<<x.nd<<")";}
_$(end(x),o){o<<"{";for(int i=0;auto e:x)o<<","+!i++<<e;return o<<"}";}

#ifdef LOCAL
#define debug(x...) cerr<<"["#x"]: ",[](auto...$){\
  ((cerr<<$<<"; "),...)<<'\n';}(x)
#else
#define debug(...)
#endif

#define rep(i,a,b) for(int i=(a);i<(b); i++)
using pii=pair<int,int>;
using vi=vector<int>;

const int inf = 1e9+7;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  
  return 0;
}
