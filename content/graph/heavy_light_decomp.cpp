/*
 * Author: Matthew Agar
 * Date: 2021-08-19
 * Source: Own work
 * Description: Heavy-light decomposition of a tree
 * Time: The path from v -> root is decomposed into log(N) many contiguous ranges,
		 usually log^2(N) time using a segment tree
 * Status: Tested on https://dmoj.ca/problem/bfs19p5
 */

vector<int> adj[MX]; // heavy child is adj[v][0]
int siz[MX], par[MX];
int up[MX]; // up[v] = highest vertex on v's heavy path
int at[MX], tin[MX], tout[MX], tim;

void dfs_heavy(int v) {	// subtree sizes + heavy reordering 
	int sm = 0;
	for(int u : adj[v]) {
		if(u != par[v]) {
			par[u] = v;
			dfs_heavy(u);
			sm += siz[u];
	} }
	siz[v] = 1 + sm;
	sort(all(adj[v]), [](int a, int b) { return siz[a] > siz[b]; });
}
void dfs_order(int v) {	// calculate 'up', 'tin', 'tout', 'at' arrays
	tin[v] = tim;	at[tim++] = v; 
	rep(i,0,sz(adj[v])) {
		int u = adj[v][i];
		if(u == par[v]) {	assert(i+1 == sz(adj[v])); continue; } // sanity check
		if(i == 0) up[u] = up[v];
		else up[u] = u;
		dfs_order(u); }
	tout[v] = tim;
}

void go(int root = 0) {	// call this!!!
	memset(par, -1, sizeof(par));
	dfs_heavy(root);
	up[root] = root; dfs_order(root);
}

/*
	Notes:
		* Segment tree is built over dfs times
		* May need LCA if querying path u -> v
			* DONT include LCA(u, v) twice!
		* Do you really want to use this?? log^2(n) is SLOW!
	
	Example submission: https://pastebin.com/nAvfU8J2
*/
