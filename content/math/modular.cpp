/*
 * Author: Matthew Agar
 * Date: 2021-07-29
 * Source: Own work
 * Description: Class for integer operations under modulo
 * Time: O(1) for add, subtract, multiply, O(log MOD) for division
 * Status: stress-tested
 */

template <int m>
struct ModInt {
    int v;
    static const int MOD = m;
    
    ModInt(ll val = 0) { v = (val % MOD + MOD) % MOD; }
    
    ModInt& operator +=(const ModInt& he) { v += he.v; if(v >= MOD) v -= MOD; return *this; }
    ModInt& operator -=(const ModInt& he) { v -= he.v; if(v < 0) v += MOD; return *this; }    
    ModInt& operator *=(const ModInt& he) { v = (ll) v * he.v % MOD; return *this; }
    
    friend ModInt pw(ModInt a, ll b) {
        ModInt r = 1; assert(b >= 0);
        while(b > 0) {
            if(b & 1) r *= a;
            a *= a; b >>= 1; 
        }
        return r;
    }
    
    friend ModInt inv(ModInt a) { return pw(a, MOD-2); }    
    ModInt& operator /= (const ModInt& he) { return *this *= inv(he); }
    
    friend ModInt operator +(ModInt a, const ModInt& b) { return a += b; }
    friend ModInt operator -(ModInt a, const ModInt& b) { return a -= b; }
    friend ModInt operator *(ModInt a, const ModInt& b) { return a *= b; }
    friend ModInt operator /(ModInt a, const ModInt& b) { return a /= b; }
    
    friend ostream& operator <<(ostream& out, const ModInt& a) { return out << a.v; }
    friend bool operator ==(const ModInt& a, const ModInt& b) { return a.v == b.v; }
    friend bool operator !=(const ModInt& a, const ModInt& b) { return !(a == b); }
};

const int MOD = 1000000007;
using mint = ModInt<MOD>;

vector<mint> fact, finv, I;
void initFact(int n) {
	fact.assign(n+1, 1); finv.assign(n+1, 1); I.assign(n+1, 1);
	for(int i = 2; i <= n; i++) {
		fact[i] = i * fact[i-1];
		I[i] = (MOD - MOD / i) * I[MOD % i];
		finv[i] = I[i] * finv[i-1];
	}
}

mint choose(int n, int k) {
    assert(n < sz(fact));
    if(n < k) return 0;
    return fact[n] * finv[n - k] * finv[k];
}

// Modulus is in the input -> Inverse not guaranteed!!!
int MOD;
int add(int a, int b) {
	return ((a + b) % MOD + MOD) % MOD;
}
int sub(int a, int b) {
	return ((a - b) % MOD + MOD) % MOD;
}
int mul(int a, int b) {
	return (long long) a * b % MOD;
}
