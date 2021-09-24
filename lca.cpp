/*
 * Author: Matthew Agar
 * Date: 2021-07-31
 * Source: Own work
 * Description: Binary lifting for lowest common ancestor on a tree
 * Time: O(N * log(N)) for pre-process, O(log(N)) per lca query
 * Status: stress-tested
 */

vi adj[MX];
int par[MX][LOG];
int dep[MX];

void plant(int v, int p) {
    for(int i = 1; i < LOG; i++) {
        par[v][i] = par[par[v][i-1]][i-1];
    }
    for(int u : adj[v]) {
        if(u != p) {
            dep[u] = dep[v] + 1;
            par[u][0] = v;
            plant(u, v);
        }
    }
}

int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    int k = dep[a] - dep[b];
    for(int i = 0; i < LOG; i++)
        if(k >> i & 1)
            a = par[a][i];
    if(a == b) return a;
    for(int i = LOG-1; ~i; --i) {
        if(par[a][i] != par[b][i]) {
            a = par[a][i];
            b = par[b][i];
        }
    }
    return par[a][0];
}
