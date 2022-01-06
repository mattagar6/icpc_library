/*
 * Author: Matthew Agar
 * Date: 2021-10-11
 * Source: Own
 * Description: Persistent Segment tree (point update, range query)
 *              - Works just like a normal segtree, except you can make copies of it in O(1)
 *              - Supports methods:
 *                - segtree.query(l, r); // returns the sum of elements [l, r), O(log(n)) time
 *                - segtree.update(i, x); // set the value at position i to x, O(log(n)) time and space
 *              - Can be used to find: 
 *                - kth largest in range
 *                - number of distinct elements in a range
 * Usage:
 *  vector<PersistentSegtree> roots(n);
 *  roots[0].init(A);
 *  for(i = 1; i < n; i++) {
 *      roots[i] = roots[0]; // O(1) !!!
 *  }
 * 
 * Time: O(log(n)), for "query" and "update", O(1) for " = ", where n is the maximum size of the array.
 * Status: tested on
 *         - https://codeforces.com/contest/786/problem/C
 * 
 * WARNING: HIGH MEMORY USAGE!!! (sizeof(Node) ~ 24 Bytes, Be careful when N > 2 * 10^5 and ML is 256 MB)
 */
 
// TODO: Implement lazy propogation for range updates (see persistent_treap.cpp)

class PersistentSegtree {
private:
	
	using T = long long;
	static constexpr T DEF = 0;
	
	struct Node {
		Node *l, *r;
		T v;
		
		Node() { l = r = nullptr; v = DEF; }
		Node(const Node& he) {
			l = he.l; r = he.r; v = he.v;
		}
	};
	
	T merge(T a, T b) {
		return a + b;
	}
	
	void pull(Node* v) { assert(v->l); assert(v->r); // don't do smth dumb
		v->v = merge(v->l->v, v->r->v);
	}
	
	Node* root;
	int N;
	
	Node* init(int b, int e, const vector<T>& a) {
		Node* ret = new Node();
		if(e - b == 1) {
			ret->v = a[b];
		} else {
			int m = (b + e) / 2;
			ret->l = init(b, m, a);
			ret->r = init(m, e, a);
			pull(ret);
		}
		return ret;
	}
	
	Node* upd(Node* v, int b, int e, int i, const T& x) { assert(v);
		Node* ret = new Node(*v);
		if(e - b == 1) {
			ret->v = x;
			return ret;
		}
		int m = (b + e) / 2;
		if(i < m) ret->l = upd(ret->l, b, m, i, x);
		else ret->r = upd(ret->r, m, e, i, x);
		pull(ret);
		return ret;
	}
	
	T qry(Node* v, int b, int e, int l, int r) { assert(v);
		if(l >= r) return DEF;
		if(b == l && e == r) {
			return v->v;
		}
		int m = (b + e) / 2;
		return merge(qry(v->l, b, m, l, min(r, m)), qry(v->r, m, e, max(l, m), r));
	}
	
	int descend(Node* v, int b, int e, int k) { assert(v);
		if(e - b == 1) {
			return v->v > k ? b : e;
		}
		int m = (b + e) / 2;
		if(v->l->v <= k) {
			return descend(v->r, m, e, k - v->l->v);
		} else {
			return descend(v->l, b, m, k);
		}
	}
	
public:
	PersistentSegtree() { root = nullptr; }
	PersistentSegtree(const PersistentSegtree& he) {
		N = he.N; root = he.root;
	}

	void init(const vector<T>& a) {
		N = a.size();
		root = init(0, N, a);
	}
	
	void update(int i, const T& x) { // Set A[i] = x, O(log(n))
		root = upd(root, 0, N, i, x);
	}
	
	T query(int l, int r) { // [l, r)
		return qry(root, 0, N, l, r);
	}
	
	int lower_bound(T k) { // leftmost prefix with sum >= k
		return descend(root, 0, N, k);
	}
};
