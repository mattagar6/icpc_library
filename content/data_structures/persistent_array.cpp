/*
 * Author: Matthew Agar
 * Date: 2021-10-04
 * Source: Own
 * Description: Persistent Array
 *              - Works just like a normal array, except you can make copies of it in O(1)
 *              - Supports methods:
 *                - my_array.at(i); // returns the element at position i, O(log(n)) time and space
 *                - my_array.update(i, x); // set the value at position i to x, O(log(n)) time and space
 *              - Can be used to implement persistent DSU
 * Usage:
 *  vector<PersistentArray<int>> arrays(n);
 *  arrays[0].init(A);
 *  for(i = 1; i < n; i++) {
 *      arrays[i] = arrays[0]; // O(1) !!!
 *  }
 * 
 * Time: O(log(n)), for "at" and "update", O(1) for " = ", where n is the maximum size of the array.
 * Status: tested on
 *         - https://dmoj.ca/problem/wac4p5
 */

template<typename T>
class PersistentArray {
private:	
	struct Node {
		Node *l, *r;
		T v;
		Node() { l = r = nullptr; }
		Node(const Node& he) {
			l = he.l; r = he.r; v = he.v; 
		}
	};
	
	Node* root;
	int N;

	Node* init(int b, int e, const vector<T>& a) {
		Node* ret = new Node();
		if(e - b == 1) {
			ret->v = a[b];
		} else {
			int mid = (b + e) / 2;
			ret->l = init(b, mid, a);
			ret->r = init(mid, e, a);
		}
		return ret;
	}

	Node* upd(Node* v, int b, int e, int i, const T& x) {
		Node* ret = new Node(*v);
		if(e - b == 1) {
			ret->v = x;
			return ret;
		}
		int mid = (b + e) / 2;
		if(i < mid) ret->l = upd(ret->l, b, mid, i, x);
		else ret->r = upd(ret->r, mid, e, i, x);
		return ret;
	}
	
	T qry(Node *v, int i) {
		int b = 0, e = N;
		while(e - b > 1) {
			int mid = (b + e) / 2;
			if(i < mid) v = v->l, e = mid;
			else v = v->r, b = mid;
		}
		return v->v;
	}

public:
	void init(const vector<T>& a) {
		N = a.size();
		root = init(0, N, a);
	}

	void update(int i, const T& x) { // Set A[i] = x, O(log(n))
		assert(0 <= i && i < N);
		root = upd(root, 0, N, i, x);
	}
	
	T at(int i) { // return A[i], O(log(n))
		assert(0 <= i && i < N);
		return qry(root, i);
	}
};
