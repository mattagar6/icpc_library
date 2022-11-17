using C = complex<double>;

const double PI = acos(-1);

void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<C> R(2, 1);
	static vector<C> rt(2, 1);
	for(static int k = 2; k < n; k *= 2) {
		R.resize(n);
		rt.resize(n);
		auto x = polar(1.0, PI/k);
		for(int i = k; i < 2*k; i++) rt[i] = R[i] = i % 2 ? R[i/2] * x : R[i/2];
	}
	vector<int> rev(n);
	for(int i = 0; i < n; i++) rev[i] = (rev[i/2] | (i&1)<<L)/2;
	for(int i = 0; i < n; i++) if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int k = 1; k < n; k *= 2) {
		for(int i = 0; i < n; i += 2 * k) {
			for(int j = 0; j < k; j++) {
				C z = rt[j+k] * a[i+j+k];
				a[i+j+k] = a[i+j] - z;
				a[i+j] += z;
			}
		}
	}
}


vector<C> conv(vector<C> a, vector<C> b) {
	int n = 1;
	while(n < sz(a) + sz(b) - 1) n *= 2;
	a.resize(n);
	b.resize(n);
	fft(a);
	fft(b);
	vector<C> c(n);
	for(int i = 0; i < n; i++) c[i] = a[i] * b[i];
	for(int i = 0; i < n; i++) c[i] /= n;
	reverse(c.begin()+1, c.end());
	fft(c);
	return c;
}
