#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define sz(x) ((int)(x.size()))
#define all(x) x.begin(), x.end()
#define rep(i,a,b) for (int i = a; i < int(b); i++)
#define F first
#define S second
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound

template <typename T> int smin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <typename T> int smax(T& a, const T& b) { return b > a ? a = b, 1 : 0; }

mt19937_64 rng;
//~ mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

const int MX = 2e5 + 10;
const char nl = '\n';



void solve() {
	
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int te = 1;
    //~ cin >> te;
    while (te--) {
        solve();
    }

    return 0;
}
