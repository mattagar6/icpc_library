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

/*
	Flow Tricks and Common Ideas:
		- Max Flow = Min Cut
		- Doing some operation on a grid -> Min Cut
			- Example problem: https://dmoj.ca/problem/nwerc11f
			- Submission: https://pastebin.com/ced8JmG0
	
	Max Flow with lower bounds on edge capacities (Flows with demands):
		- See link: https://cp-algorithms.com/graph/flow_with_demands.html
		- Example problem: https://dmoj.ca/problem/wac4p6
		- Submission: https://pastebin.com/VmJ40jFc
		
		- Assume the flow through each edge has to be a certain amount (its demand),
		  The flow though every edge e has to satisfy:
			d(e) <= f(e) <= c(e), where d = demand, f = flow, c = capactiy
		
		- What are the MINIMUM and MAXIMUM flows from S to T that satisfy these requirements?
		
		- finding some ARBITRARY flow:
			- Create a new graph with a new source (S2) and a new sink (T2).
			- Draw an edge from S2 to all nodes in the original graph with capacity
			  c'({S2,v}) = sum of all d({u,v}) for all edges {u,v} in original graph (sum of input demands to v)
			- Draw an edge from each node in the original graph to T2 with capacity
			  c'({v,T2}) = sum of all d({v,u}) for all edges {v,u} in original graph (sum of output demands from v)
			- For each edge {u,v} in the old graph, draw edge {u,v} in the new graph with capacity
			  c'({u,v}) = c({u,v}) - d({u,v}) (extra flow we can send between u and v)
			- Finally, draw and edge {T,S} in the new graph with capacity INF
			
			- *** There exists a solution to the problem above iff the max flow from S2 -> T2 "saturates" all edges
			  coming out of S2 in the new graph (they all end up with capacity 0 at the end) ***
			
			- INTUITION: 
				- The outgoing edges from S2 "force" each node v to have the correct amount of flow coming out of them
				  (at least the amount from the demand constraints)
				- The incoming edges to T2 "force" each node v to have the correct amount of flow coming into them
				  (at least the amount from the demand constraints)
				- Imagine a path with d({u,v}) flow being pushed along it in the original graph. It's path looks like
					
					S -> (..P1..) -> u -> v -> (..P2..) -> T. in the new graph, its path looks like
					S2 -> v -> (..P2..) -> T -> S -> (..P1..) -> u -> T2
					
					This shows why the T -> S edge is needed in the new graph (with capacity INF)
		
		- From now on I assume there is a solution to the problem abive.
		
		- finding the MAXIMUM flow:
			- Create the Graph above. 
			- Run max_flow(S2, T2). This will saturate all edges from S2, and all edges going to T2
			- Run max_flow(S, T) on the residual graph from above. This flow is the answer.
				- We have ensured that all demands are met, now we can add on as much flow as possible.
		
		- finding the MINIMUM flow:
			- Create the Graph above, but DONT ADD THE EDGE T -> S!!!
			- The answer is sum(d(e) for all e) - max_flow(S2, T2).
				- The flow in the original graph is forced through the edge T -> S in the new graph. 
				- Thus, the minimum possible flow in the original graph is the minimum capacity
				  of the T -> S edge in the new graph such that there is a solution.
					- This is exactly what the expression above gives.

*/
