/*
 * Author: Matthew Agar
 * Source: Own work
 * Description: Sparse table for range minimum query
 * Time: O(n * log(n)) for build, O(1) for get.
 * Status: stress-tested
 */
typedef vector<int> vi;
template<typename T> struct RMQ {
	int lvl(int x) { return 31-__builtin_clz(x); }
	vector<T> v; vector<vi> tab; 
	int cmb(int x, int y) { // default = min
		return v[x] == v[y] ? min(x,y) : (v[x] < v[y]) ? x : y; }
	
	void init(const vector<T>& _v) { v = _v;
		int N = v.size(), B = lvl(N) + 1; tab.resize(B, vi(N,-1));
		iota(all(tab[0]), 0);
		for(int i = 1; i < B; i++) for(int j = 0; j+(1<<i) <= N; j++)
			tab[i][j] = cmb(tab[i-1][j], tab[i-1][j+(1<<(i-1))]);
	}
	int index(int l, int r) { assert(l <= r);
		int d = lvl(r-l+1);
		return cmb(tab[d][l], tab[d][r-(1<<d)+1]); }
	T qry(int l, int r) { // [l, r]
		return v[index(l,r)]; }
};

// Range GCD qry
struct RGQ {
	int lvl(int x) { return 31-__builtin_clz(x); }
	vector<ll> v; vector<vector<ll>> tab;
	ll cmb(ll x, ll y) { // default = gcd
		return __gcd(x,y); }
	
	void init(const vector<ll>& _v) { v = _v;
		int N = v.size(), B = lvl(N) + 1; tab.resize(B, vector<ll>(N));
		tab[0] = v;
		for(int i = 1; i < B; i++) for(int j = 0; j+(1<<i) <= N; j++)
			tab[i][j] = cmb(tab[i-1][j], tab[i-1][j+(1<<(i-1))]);
	}
	ll qry(int l, int r) { assert(l <= r); // [l, r]
		int d = lvl(r-l+1);
		return cmb(tab[d][l], tab[d][r-(1<<d)+1]); }
};
