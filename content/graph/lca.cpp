/*
 * Author: Matthew Agar
 * Source: Own work
 * Description: Euler tour for LCA on a tree
 *              - uses RMQ
 * Time: O(n * log(n)) for preprocessing, O(1) for lca.
 * Status: tested on
 *         - https://dmoj.ca/problem/dmopc20c1p5
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

struct LCA {
	int N; bool _init = false;
	vector<vi> adj; vi par, dep, in;
	vector<pii> tour; RMQ<pii> rmq;
	void init(int _N) { N = _N;
		par.resize(N); adj.resize(N); dep.resize(N); in.resize(N);
	}
	void add_edge(int x, int y) { adj[x].push_back(y); adj[y].push_back(x); }
	void go(int R = 0) { par[R] = R; dfs(R); rmq.init(tour); _init = true; } // call this!!!
	
	void dfs(int v) {
		in[v] = tour.size(); tour.push_back({dep[v], v});
		for(auto& u : adj[v]) if(u != par[v]) dep[u] = dep[par[u] = v] + 1, 
			dfs(u), tour.push_back({dep[v],v});
	}
	int lca(int x, int y) { assert(_init); // call go()!
		if(in[x] > in[y]) swap(x,y);
		return rmq.qry(in[x], in[y]).second;
	}
	int dist(int x, int y) { return dep[x] + dep[y] - 2*dep[lca(x,y)]; }
};


/*
 * Author: Matthew Agar
 * Date: 2021-07-31
 * Source: Own work
 * Description: Binary lifting for lowest common ancestor on a tree
 * Time: O(N * log(N)) for pre-process, O(log(N)) per lca query
 * Status: tested on
 *          - https://dmoj.ca/problem/dmopc20c1p5
 */
typedef vector<int> vi;
struct LCA {
	int N; int lg = 1; bool _init = false;
	vector<vi> par, adj; vi dep;
	void init(int _N) { N = _N;
		while((1<<lg) < N) lg++;
		par.assign(lg, vi(N)); adj.resize(N), dep.resize(N);
	}
	void add_edge(int x, int y) { adj[x].push_back(y); adj[y].push_back(x); }
	void go(int R = 0) { par[0][R] = R; dfs(R); _init = true; } // call this!!!
	
	void dfs(int v) {
		for(int i = 1; i < lg; i++) par[i][v] = par[i-1][par[i-1][v]];
		for(auto& u : adj[v]) if(u != par[0][v])
			dep[u] = dep[par[0][u] = v] + 1, dfs(u);
	}
	int jmp(int v, int d) {
		for(int i = 0; i < lg; i++) if(d >> i & 1) v = par[i][v];
		return v;
	}
	int lca(int x, int y) { assert(_init); // call go()!
		if(dep[x] < dep[y]) swap(x,y);
		x = jmp(x, dep[x] - dep[y]);
		if(x == y) return x;
		for(int i = lg-1; i >= 0; --i) if(par[i][x] != par[i][y])
			x = par[i][x], y = par[i][y];
		return par[0][x];
	}
	int dist(int x, int y) { return dep[x] + dep[y] - 2*dep[lca(x,y)]; }
};
