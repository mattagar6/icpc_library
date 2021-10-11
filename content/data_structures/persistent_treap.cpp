/*
 * Author: Matthew Agar
 * Date: 2021-10-04
 * Source: Own
 * Description: Persistent Treap
 *              - Works just like a normal Treap, except you can make copies of it in O(1)
 *              - Supports all treap methods (split, merge) in O(log(n)) complexity:
 * 
 * Time: O(log(n)), for all treap methods (split/merge).
 * Status: tested on
 *         - https://dmoj.ca/problem/wac4p5
 *         - Submission: https://pastebin.com/UaK53Jyk
 *
 * WARNING: HIGH MEMORY USAGE!!! (sizeof(Node) > 24 Bytes, Be careful when N > 2 * 10^5 and ML is 256 MB)
 */

mt19937 rng;

class PersistentTreap {
private:
	
	struct Node {
		Node *l, *r;
		int size;
		int weight;
		ll mx, val, lazy;
		
		Node(ll v = 0) {
			l = r = nullptr;
			size = 1;
			weight = rng();
			val = v;
			mx = v;
			lazy = 0;
		}
		
		Node(const Node& he) {
			l = he.l; r = he.r;
			size = he.size;
			weight = he.weight;
			mx = he.mx; 
			lazy = he.lazy;
			val = he.val;
		}
	};
	
	Node* root;
	
	int size(Node* treap) { return treap ? treap->size : 0; }
	
	void apply(Node* treap, ll x) { // apply lazy propogation value x to treap
		if(!treap) return;
		treap->val += x;
		treap->mx += x;
		treap->lazy += x;
	}
	
	void prop(Node* treap) { // propogate lazy prop value to my children 
		if(treap->l) treap->l = new Node(*treap->l);
		if(treap->r) treap->r = new Node(*treap->r);
		ll& x = treap->lazy;
		apply(treap->l, x);
		apply(treap->r, x);
		x = 0;
	}
	
	void recalc(Node* treap) { // re-calculate subtree info for treap
		if(!treap) return;
		treap->size = 1 + size(treap->l) + size(treap->r);
		treap->mx = max({treap->val, maxVal(treap->l), maxVal(treap->r)});
	}
	
	pair<Node*, Node*> split(Node* treap, int k) { // k nodes on the left
		if(!treap) {
			assert(k == 0);
			return {nullptr, nullptr};
		}
		prop(treap);
		if(size(treap->l) >= k) {
			auto [l, r] = split(treap->l, k);
			treap->l = r;
			recalc(treap);
			return {l, treap};
		} else {
			auto [l, r] = split(treap->r, k - (1 + size(treap->l)));
			treap->r = l;
			recalc(treap);
			return {treap, r};
		}
	}
		
	Node* merge(Node* l, Node* r) {
		if(!l) return r;
		if(!r) return l;
		prop(l); prop(r);
		Node* ret = nullptr;
		if(l->weight < r->weight) {
			ret = new Node(*l);
			ret->r = merge(ret->r, r);	
		} else {
			ret = new Node(*r);
			ret->l = merge(l, ret->l);
		}
		recalc(ret);
		return ret;
	}
	
public:
	PersistentTreap(Node* R = nullptr) { root = R; }
	PersistentTreap(const PersistentTreap& he) {
        	root = new Node(*he.root);
    	}
	
	/*
		Add your functions here.
		IMPORTANT: 
			- Ensure that all Nodes passed into functions are "new",
			  Do split(new Node(*root), k); instead of split(root, k) 
	
	*/
};
