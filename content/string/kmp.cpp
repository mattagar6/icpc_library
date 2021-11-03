// USE Z.cpp INSTEAD!!!!

/*
 * Author: Matthew Agar
 * Date: 2021-08-20
 * Source: Own work
 * Description: KMP algortihm for string matching
                Computes T[i] = length of longest propper suffix of
                the prefix ending at W[i-1], that is a prefix of W
 * Time: O(N) for kmp, O(N + M) for matches
 * Status: tested on 
           - https://codeforces.com/contest/1466/submission/126574060
 */
typedef vector<int> vi;
vi kmp(string W) {       // T[i] = length of longest proper suffix of prefix ending at i-1, that is a prefix of W
	vi T(sz(W) + 1, -1); // T[0] = -1
	int cnd = 0;
	rep(pos,1,sz(W)) {
		if(W[pos] == W[cnd]) {
			T[pos] = T[cnd];
		} else {
			T[pos] = cnd;
			while(cnd >= 0 && W[pos] != W[cnd])
				cnd = T[cnd];
		}
		cnd += 1;
	}
	T[sz(W)] = cnd;
	return T; }

vi matches(string S, string P) { // where does P occur in S? (starting index)
	vi where, T = kmp(P);
	int i = 0, j = 0;
	while(i < sz(S)) {
		if(S[i] == P[j]) {
			i++; j++;
			if(j == sz(P)) { 
				where.pb(i-j);
				j = T[j];
			}
		} else {
			j = T[j];
			if(j == -1) {
				++i; ++j;
			}
		}
	}
	return where; }

int count_matches(string S, string P) { // how many times does P occur in S?
	return sz(matches(S, P)); }
