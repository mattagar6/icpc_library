/*
 * Description: Minimum-cost maximum flow, assumes no negative cycles. 
	* Can do -w -> INF - w and adjust accordingly
 * Time: Ignoring first run of Dijkstra, O(FMlog M) 
 	* if caps are integers and F is max flow.
 * Source: GeeksForGeeks
 	* running time is only pseudo-polynomial; see https://codeforces.com/blog/entry/70740
 * Verification: 
 	* https://codeforces.com/contest/1572/submission/129688035
 */

struct MCMF { 
	using F = long long; using C = long long; // flow type, cost type
	struct Edge { int to, rev; F flo, cap; C cost; };
	int N; vector<C> dist; vector<pair<int,int>> pre; vector<vector<Edge>> adj;
	void init(int _N) { N = _N;
		adj.resize(N), dist.resize(N), pre.resize(N); }
	void add_edge(int u, int v, F cap, C cost) { assert(cap >= 0); 
		adj[u].pb({v,sz(adj[v]),0,cap,cost}); 
		adj[v].pb({u,sz(adj[u])-1,0,0,-cost});
	} // use asserts, don't try smth dumb
	bool path(int s, int t) { // send flow through lowest cost path
		const C inf = numeric_limits<C>::max(); dist.assign(N,inf);
		using T = pair<C,int>;
		priority_queue<T,vector<T>,greater<T>> todo; 
		todo.push({dist[s] = 0,s}); 
		while (sz(todo)) { // Dijkstra
			T x = todo.top(); todo.pop(); 
			if (x.F > dist[x.S]) continue;
			for(const auto& e: adj[x.S]) { // all weights should be non-negative
				if (e.flo < e.cap && smin(dist[e.to],
						x.F+e.cost))
					pre[e.to]={x.S,e.rev}, todo.push({dist[e.to],e.to});
			}
		} // if costs are doubles, add some EPS so you 
		// don't traverse ~0-weight cycle repeatedly
		return dist[t] != inf; // true if augmenting path
	}
	pair<F,C> max_flow(int s, int t) { assert(s != t);
		F totFlow = 0; C totCost = 0;
		while (path(s,t)) {
			F df = numeric_limits<F>::max();
			for (int x = t; x != s; x = pre[x].F) {
				Edge& e = adj[pre[x].F][adj[x][pre[x].S].rev]; 
				smin(df,e.cap-e.flo); }
			totFlow += df; totCost += dist[t] * df;
			for (int x = t; x != s; x = pre[x].F) {
				Edge& e = adj[x][pre[x].S]; e.flo -= df;
				adj[pre[x].F][e.rev].flo += df;
			}
		} // get max flow you can send along path
		return {totFlow,totCost};
	}
};
