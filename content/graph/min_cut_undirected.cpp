// Description:
// Given a weighted, undirected graph G(V,E)
// Find the minimum edge cut to split the graph into 2 components
// https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm
// G[u][v] = G[v][u] = weight of edge (u,v)

// Time: O(N^3)
// Tested on: https://dmoj.ca/problem/checkercut

const int MX = 600;
const ll INF = 1e18;

ll N, G[MX][MX];

void addEdge(int a, int b, ll w) {
	G[a][b] += w; G[b][a] += w; 
}

bool gone[MX];
ll findCut(int& S, int& T) { // find arbitrary cut in G
	ll w[MX] = {0};
	bool vis[MX] = {0};
	ll cut = 0;
	for(int rep = 0; rep < N; rep++) {
		int nxt = -1;
		for(int v = 0; v < N; v++) 
			if(!gone[v] && !vis[v] && (nxt == -1 || w[v] > w[nxt])) 
				nxt = v;
		if(nxt == -1) return cut;
		S = T; T = nxt;
		vis[T] = true;
		cut = w[T];
		for(int v = 0; v < N; v++) 
			w[v] += G[T][v];
	}
	return cut;
}

ll minCut() { assert(N > 0);
	ll cut = INF;
	for(int rep = 0; rep < N-1; rep++) {
		int S = 0, T = 0;
		cut = min(cut, findCut(S, T));
		// if S-T is not a min cut, then S,T are on same side of min cut
		for(int v = 0; v < N; v++) // unite S,T
			G[S][v] = G[v][S] = G[S][v] + G[T][v];
		gone[T] = true;
	}
	return cut;
}

