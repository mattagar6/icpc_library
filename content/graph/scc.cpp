/*
 * Author: Matthew Agar
 * Date: 2021-07-29
 * Source: Own work
 * Description: Kosaraju's algorithm for strongly connected components
 * Time: O(V + E) for go and make_dag
 * Status: stress-tested
 */
#define pb push_back
#define rep(i,a,b) for(int i = a; i < int(b); i++)
typedef vector<int> vi;
struct SCC {
    int n;
    vector<vi> adj[2], scc;
    vi ord, used, comp, id;
    
    SCC(int nn) : n(nn) {
        rep(i,0,2) adj[i].resize(n);
        ord.resize(n); used.resize(n); comp.resize(n), id.resize(n);
    }
    
    void add_edge(int u, int v) { adj[0][u].pb(v); adj[1][v].pb(u); }
    
    void dfs(int t, int v) {
        used[v] = 1;
        if(t == 1) comp.pb(v);
        for(auto u: adj[t][v]) if(!used[u]) dfs(t,u);
        if(t == 0) ord.pb(v);
    }
    
    // Returns "id[v] = which SCC is v in"
    vi go() { // call this!!!
        used.assign(n,0);
        rep(v,0,n) if(!used[v]) dfs(0,v);
        used.assign(n,0);
        reverse(all(ord));
        for(auto v: ord) {
            if(used[v]) continue;
            comp.clear();
            dfs(1,v);
            for(auto u: comp) id[u] = sz(scc);
            scc.pb(comp);
        }
        return id;
    }
    
    // Make sure to call "go" first!!
    // Returns a new graph such that all SCCs are compressed into one node 
    // Only edges connecting two components are in the new graph.
    // DAG is already in top-sort, all edges in DAG (u, v) have u < v!
    vector<vi> make_dag() {
        int N = sz(scc); assert(N > 0);
        vector<vi> dag(N);
        used.assign(N, -1);
        rep(cc,0,N) 
            for(auto v: scc[cc])
                for(auto u: adj[0][v])
                    if(id[u] != cc && used[id[u]] != cc)
                        dag[cc].pb(id[u]), used[id[u]] = cc;
        return dag;
    }
};
