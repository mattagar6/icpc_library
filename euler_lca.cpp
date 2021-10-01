/*
 * Author: Matthew Agar
 * Source: Own work
 * Description: Euler tour for LCA on a tree
 * Time: O(n * log(n)) for initLca, O(1) for lca.
 * Status: stress-tested
 */

int msb(int nn) {
    assert(nn > 0);
    return 31 - __builtin_clz(nn);
}

template<typename T>
struct SparseTable {
    int n;
    vector<vector<T>> tab;
    void build(vector<T> a) {
        n = a.size();
        int B = msb(n) + 1;
        tab.resize(B);
        for(int b = 0; b < B; b++) {
            tab[b].resize(n);
            int len = 1<<b;
            for(int i = 0; i <= n-len; i++) {
                if(len == 1) 
                    tab[b][i] = a[i];
                else 
                    tab[b][i] = min(tab[b-1][i], tab[b-1][i+len/2]);
            }
        }
    }
    T get(int L, int R) const {
        int b = msb(R - L + 1);
        return min(tab[b][L], tab[b][R-(1<<b)+1]);
    }
};

SparseTable<pii> tab;

vector<pii> tour;
vi adj[MX];
int in[MX], par[MX], dep[MX];

void dfs_pre(int v) {
	in[v] = sz(tour); tour.pb({dep[v], v});
	for(int u : adj[v]) {
		if(u != par[v]) {
			par[u] = v, dep[u] = dep[v] + 1;
			dfs_pre(u);
			tour.pb({dep[v], v});
		}
	}
}

// Assumes root of tree is 0
void initLca() { // Call This!!!
	dfs_pre(0);
	tab.build(tour);
}

int lca(int a, int b) {
	if(in[a] > in[b]) swap(a, b);
	return tab.get(in[a], in[b]).S;
}

int dist(int a, int b) { return dep[a] + dep[b] - 2 * dep[lca(a, b)]; }

// is c on path (a -> b)?
bool on_path(int a, int b, int c) { return dist(a, b) == dist(a, c) + dist(c, b); }
