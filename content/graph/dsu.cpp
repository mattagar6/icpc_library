/*
 * Author: Matthew Agar
 * Date: 2021-08-02
 * Source: Own work
 * Description: Union-find with path compression and union by rank
 * Time: O(alpha(N)) for find and union, alpha(N) is inverse Ackermann function
 * Status: stress-tested
 */
typedef vector<int> vi;
struct DSU {
	int N;
	vi p, sz;
	void init(int _N) { N = _N;
		p.assign(N, 0); sz.assign(N,1);
		iota(all(p),0); }
	
	int find(int v) { return p[v] = v == p[v] ? v : find(p[v]); }
	
	bool uni(int u, int v) {
		int pu = find(u), pv = find(v);
		if(pu == pv) return false;
		if(sz[pu] < sz[pv]) swap(pu, pv);
		p[pv] = pu;
		sz[pu] += sz[pv];
		return true;
	}
};
