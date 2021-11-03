/*
 * Author: Matthew Agar
 * Date: 2021-07-29
 * Source: Own work
 * Description: Aho-Corasick Algorithm for string matching
 * Time: O(L * C), where L is the total length of all strings, C is alphabet size 
 * Status: stress-tested
 */
typedef vector<int> vi;
#define pb push_back
struct Aho {
    const int C = 26; //XXX
    vector<vi> tr;
    vi match;
    int N = 0;
    
    Aho() { neww(); }
    
    int neww() {
        tr.pb(vi(C)); match.pb(0); adj.pb({});
        return N++;
    }
    
    void insert(string s) {
        int v = 0;
        for(char c : s) {
            if(!tr[v][c-'a'])
                tr[v][c-'a'] = neww();
            v = tr[v][c-'a'];
        }
        ++match[v];
    }
    
    void go() { // call this!!!
        queue<int> qu;
        vi f(N);
        rep(i, 0, C) if(tr[0][i]) qu.push(tr[0][i]);
        while(sz(qu)) {
            int v = qu.front(); qu.pop();
            rep(i, 0, C) {
                if(tr[v][i]) 
                    f[tr[v][i]] = tr[f[v]][i],
                    qu.push(tr[v][i]);
                else
                    tr[v][i] = tr[f[v]][i];
            }
        }
        rep(i, 1, N) adj[f[i]].pb(i);
        dfs(0);
    }
    
    vector<vi> adj;
    void dfs(int v) {
        for(int u : adj[v]) {
            match[u] += match[v];
            dfs(u);
        }
    }
};
