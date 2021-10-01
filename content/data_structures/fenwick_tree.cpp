/*
 * Author: Matthew Agar
 * Date: 2021-08-16
 * Source: Own work
 * Description: Fenwick tree for either 
               (point update, range sum) or (range update, point query)
 * Time: O(log(n)) for all methods.
 * Status: stress-tested
 */

template<typename T> struct Fenwick {
	int n;
	vector<T> tree;
	
	Fenwick() {}
	Fenwick(int N) : n(N), tree(N + 1) {}
	
	void upd(int i, T x) { // 0-indexed!!!
		for(++i; i <= n; i += i&-i)
			tree[i] += x;
	}
	
	void addRange(int l, int r, T x) { // [l, r]
		upd(l, x);
		upd(r + 1, -1 * x);
	}
	
	T qry(int i) { // [0, i]
		T s = 0;
		for(++i; i > 0; i -= i&-i)
			s += tree[i];
		return s;
	}
	
	T sumRange(int l, int r) { // [l, r]
		return qry(r) - qry(l-1);
	}
};
