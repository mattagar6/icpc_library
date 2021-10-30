/*
 * Author: Matthew Agar
 * Date: 2021-08-30
 * Source: Own work
 * Description: Linear Sieve for computing primes and multiplicitave functions
 * Time: O(N) for init, O(1) for others
 * Status: tested on
 *         - https://www.spoj.com/problems/DIVFACT3/
 * Inspired by: https://codeforces.com/blog/entry/54090 (see how to do totient function in O(N))
 */

struct LinearSieve {
	vector<bool> is_composite;
	vector<int> prime;
	vector<int> pre;
	
	void init(int N) {
		is_composite.assign(N + 1, false);
		pre.assign(N + 1, 0);
		prime.clear();
		for(int i = 2; i <= N; i++) {
			if(!is_composite[i]) pre[i] = 1, prime.push_back(i);
			for(int j = 0; j < sz(prime) && i * prime[j] <= N; j++) {
				is_composite[i * prime[j]] = true;
				if(i % prime[j] == 0) break;
			}
			pre[i] += pre[i-1];
		}
	}
	
	bool is_prime(int N) {
		assert(N < sz(is_composite));
		return N > 1 && !is_composite[N];
	}
	
	int count_primes(int l, int r) { // [l, r]
		assert(l <= r); assert(r < sz(pre));
		return pre[r] - (l == 0 ? 0 : pre[l-1]);
	}
};
