/*
 * Description: Fast flow. After computing flow, edges (u, v) such that 
	* lev[u] != 0, lev[v] == 0 are part of min cut.
 * Time: O(N^2M) flow
 * Source: GeeksForGeeks, Chilli
 	* https://codeforces.com/contest/1416/submission/94013395
 * Verification: 
	* https://codeforces.com/contest/498/submission/129685752
 */

struct Dinic {
	using F = long long; // flow type
	struct Edge { int to, rev; F cap; };
	int N; vector<vector<Edge>> adj;
	void init(int _N) { N = _N; adj.resize(N); }
	void add_edge(int a, int b, F cap, F rcap = 0) { 
		assert(min(cap,rcap) >= 0); // saved me > once
		adj[a].pb({b,sz(adj[b]),cap});
		adj[b].pb({a,sz(adj[a])-1,rcap});
	}
	vector<int> lev, ptr;
	bool bfs(int s, int t) { // level = shortest dist from source
		lev = ptr = vector<int>(N);
		lev[s] = 1; queue<int> q({s});
		while (sz(q)) { int u = q.front(); q.pop();
			for(const auto& e: adj[u]) if (e.cap && !lev[e.to]) {
				q.push(e.to), lev[e.to] = lev[u]+1;
				if (e.to == t) return true;
			}
		}
		return false;
	}
	F dfs(int v, int t, F flo) {
		if (v == t) return flo;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lev[e.to]!=lev[v]+1||!e.cap) continue;
			if (F df = dfs(e.to,t,min(flo,e.cap))) { 
				e.cap -= df; adj[e.to][e.rev].cap += df;
				return df; } // saturated >= 1 one edge
		}
		return 0;
	}
	F max_flow(int s, int t) {
		F tot = 0; 
		while (bfs(s,t)) while (F df = 
			dfs(s,t,numeric_limits<F>::max())) tot += df;
		return tot;
	}
};
