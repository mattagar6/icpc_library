/*
 * Author: Matthew Agar
 * Date: 2021-08-11
 * Source: Own work
 * Description: Maximum bipartite matching
 * Time: O(V * E) for max_matching, faster in practice
 * Status: stress-tested
 */

int n;
vector<int> adj[MX]; // adj[left] = vertices on right
int match[MX]; // match[right] = what am I matched to on left
bool vis[MX];

int aug(int l) {
	if(vis[l]) return 0;
	vis[l] = true;
	
	for(int r : adj[l]) {
		if(match[r] == -1 || aug(match[r])) {
			match[r] = l;
			return 1;
		}
	}
	
	return 0;
}

int max_matching() {
	memset(match, -1, sizeof(match));
	int mf = 0;
	for(int l = 0; l < n; l++) {
		memset(vis, 0, sizeof(vis));
		mf += aug(l);
	}
	return mf;
}
