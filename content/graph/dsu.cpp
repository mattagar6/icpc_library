/*
 * Author: Matthew Agar
 * Date: 2021-08-02
 * Source: Own work
 * Description: Union-find with path compression and union by rank
 * Time: O(alpha(N)) for find and union, alpha(N) is inverse Ackermann function
 * Status: stress-tested
 */

struct DSU {
	int N;
	vi p, sz;
	
	DSU() {}
	DSU(int nn) : N(nn) {
		p.resize(N); sz.resize(N,1);
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
