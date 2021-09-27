/*
 * Author: Matthew Agar
 * Date: 2021-09-25
 * Source: crackersandjam
 * Description: Segment tree with lazy propogation
 *              - All ranges are [l, r)
 *              - ls = left child of node v
 *              - rs = right child of node v
 *              - md = midpoint of range
 * Usage:
 *  segtree tree;
 *  tree.build();
 *  min_val = tree.qry(l, r);
 *  upd(l, r, x); // add x to range
 * 
 * Time: O(log(MX)), where MX is the maximum size of the array.
 * Status: tested on
 *         - https://codeforces.com/edu/course/2/lesson/5/2/practice
 */
 
// TODO: add segment tree descent?

struct segtree {
	#define ls (v<<1)
	#define rs (v<<1^1)
	#define md ((b+e)>>1)
	#define rg int b = 0, int e = MX, int v = 1
	#define lrg b, md, ls
	#define rrg md, e, rs
	
	using T = long long; using L = long long;
	static const T DEF = 1e18; static const L DEFL = 0;
	
	struct node {
		T val; L lz;
		int len;
		
		void app(L x) { // XXX
			val += x;
			lz += x;
		}
		
	} tree[MX*4];
	
	T merge(T va, T vb) { // XXX
		return min(va, vb);
	}
	
	void pull(int v) {
		tree[v].val = merge(tree[ls].val, tree[rs].val);
	}
	
	void prop(int v) {
		if(tree[v].lz == DEFL) return;
		L& x = tree[v].lz; tree[ls].app(x); tree[rs].app(x); x = DEFL;
	}
	
	void build(rg) {
		tree[v].len = e - b;
		tree[v].val = DEF;
		tree[v].lz = DEFL;
		if(e - b == 1) {
			// XXX
			return;
		}
		build(lrg); build(rrg);
		pull(v);
	}
	
	void upd(int l, int r, L x, rg) {
		if(e <= l || b >= r) return;
		if(l <= b && e <= r) {
			tree[v].app(x);
			return; 
		}
		prop(v); upd(l, r, x, lrg); upd(l, r, x, rrg);
		pull(v); }
	
	T qry(int l, int r, rg) {
		if(e <= l || b >= r) return DEF;
		if(l <= b && e <= r) { 
			return tree[v].val; 
		}
		prop(v);
		return merge(qry(l, r, lrg), qry(l, r, rrg)); }
	
	#undef ls
	#undef rs
	#undef md
	#undef lrg
	#undef rrg
};
