/*
 * Author: Matthew Agar
 * Date: 2021-08-09
 * Source: Own work
 * Description: Matrix multiplication and power
 *              - Use std::array instead of std::vector if fixed sized matrices 
 *                (reduces memory usage by a lot!)
 * Time: O(n^3) for mul (square matrices), O(n^3 * log k) for pw
 * Status: stress-tested
 */

typedef mint num;
typedef vector<vector<num>> mat;

mat neww(int n, int m) {
	return vector<vector<num>>(n, vector<num>(m));
}

mat mul(const mat& a, const mat& b) {
	int n = sz(a), m = sz(b[0]);
	assert(sz(a[0]) == sz(b));
	mat c = neww(n, m);
	rep(i,0,n)
		rep(j,0,sz(a[0]))
			rep(k,0,m)
				c[i][k] += a[i][j] * b[j][k];
	return c;
}

mat pw(mat a, ll k) {
	assert(sz(a) == sz(a[0]));
	int n = sz(a);
	mat r = neww(n, n);
	rep(i,0,n) r[i][i] = 1;
	while(k) {
		if(k & 1) r = mul(r,a);
		a = mul(a,a);
		k >>= 1;
	}
	return r;
}
