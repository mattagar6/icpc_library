// all methods 0-indexed, intervals are [l,r]
struct Tree {
	using T = long long; 
	const T NONE = 0; // default
	vector<T> tree; int B = 0;
	
	T comb(T a, T b) { return a+b; }
	
	void init(int n) { 
		B = 1; while(B < n) B *= 2; 
		tree.assign(2*B, NONE);
	}
 
	void init(vector<T> a) {
		int n = a.size(); init(n);
		for(int i = 0; i < n; i++) tree[i+B] = a[i];
		for(int i = B-1; i > 0; i--) tree[i] = comb(tree[2*i], tree[2*i+1]);
	}
 
	void upd(int i, T x) { assert(B);
		tree[i += B] = x;
		for(i /= 2; i > 0; i /= 2) tree[i] = comb(tree[2*i], tree[2*i+1]);
	}
 
	T qry(int l, int r) { assert(B);
		T resl = NONE, resr = NONE;
		for(l += B, r += B; l <= r; l /= 2, r /= 2) {
			if(l % 2 == 1) resl = comb(resl, tree[l++]);
			if(r % 2 == 0) resr = comb(tree[r--], resr);
		}
		return comb(resl, resr);
	}
};
