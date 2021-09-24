// Example submission: https://codeforces.com/contest/1558/submission/127638025
//~ mt19937 rng;
//~ mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int POOL_NODES = 100;
struct node {
	
	node *left, *right;
	int weight, size;
		
	node() : left(NULL), right(NULL), weight(rng()), size(1) {}
	
} pool[POOL_NODES];

int size(node *tr) {
	if (tr)
		return tr->size;
	return 0;
}

node *neww() {
	static int nt = 0;
	if(nt < POOL_NODES) return &pool[nt++];
	return new node();
}

void recalc(node *tr) {
	if (!tr)
		return;
	tr->size = 1 + size(tr->left) + size(tr->right);
	
}

pair<node *, node *> split(node *tr, int k) { // k nodes on left
	if (!tr) {
		assert(k == 0);
		return {NULL, NULL};
	}
	if (size(tr->left) >= k) {
		auto [l, r] = split(tr->left, k);
		tr->left = r;
		recalc(tr);
		return {l, tr};
	} else {
		auto [l, r] = split(tr->right, k - size(tr->left) - 1);
		tr->right = l;
		recalc(tr);
		return {tr, r};
	}
}

node *merge(node *l, node *r) {
	if (!l) return r;
	if (!r) return l;
	
	if (l->weight < r->weight) {
		l->right = merge(l->right, r);
		recalc(l);
		return l;
	} else {
		r->left = merge(l, r->left);
		recalc(r);
		return r;
	}
}
