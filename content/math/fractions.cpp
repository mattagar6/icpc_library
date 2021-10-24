/*
 * Author: Matthew Agar
 * Date: 2021-09-29
 * Source: Own work
 * Description: Fraction class for exact calculations
 *              BE CAREFUL OF OVERFLOWS!!!
 * Time: O(1) for all methods (but quite slow)
 * Status: tested on
 *         - https://codeforces.com/contest/281/problem/B
 *         - https://atcoder.jp/contests/abc220/tasks/abc220_g
 */

string to_string(__int128 X) {
	if (X == 0) return "0";
	bool neg = X < 0; 
	if (X < 0) X *= -1;
	string s;
	while (X > 0) { s += '0' + X % 10; X /= 10; }
	if (neg) s += '-';
	reverse(s.begin(), s.end());
	return s;
}

struct Frac {
	// If input < 1e9, use T = long long
	// If input < 1e18, use T = __int128 or pray
	// fix() is called always after construction, don't worry about it.
	using T = long long;
	T num, den;
	
	T _gcd(T a, T b) { // okay if a == 0, b == 0
		if (a < 0) a *= -1;
		if (b < 0) b *= -1;
		if (b == 0) return a;
		return _gcd(b, a % b); }
	
	Frac(T _num = 0, T _den = 1) : num(_num), den(_den) { fix(); }
	
	void fix() { // make den > 0, reduce by gcd(num, den)
		assert(den != 0); // dont do smth dumb
		T g = _gcd(num, den);
		num /= g; den /= g;
		if (den < 0) den *= -1, num *= -1; }
	
	friend Frac operator +(const Frac& a, const Frac& b) { return Frac(a.num * b.den + a.den * b.num, a.den * b.den); }
	friend Frac operator -(const Frac& a, const Frac& b) { return Frac(a.num * b.den - a.den * b.num, a.den * b.den); }
	friend Frac operator *(const Frac& a, const Frac& b) { return Frac(a.num * b.num, a.den * b.den); }
	friend Frac operator /(const Frac& a, const Frac& b) { return Frac(a.num * b.den, a.den * b.num); }
	Frac& operator +=(const Frac& he) { return *this = *this + he; }
	Frac& operator -=(const Frac& he) { return *this = *this - he; }
	Frac& operator *=(const Frac& he) { return *this = *this * he; }
	Frac& operator /=(const Frac& he) { return *this = *this / he; }
	
	bool operator  ==(const Frac& he) const { return num == he.num && den == he.den; }
	bool operator  !=(const Frac& he) const { return !(*this == he); }
	bool operator   <(const Frac& he) const { return num * he.den < he.num * den; }
	bool operator  <=(const Frac& he) const { return num * he.den <= he.num * den; }
	
	friend ostream& operator <<(ostream& out, const Frac& f) { 
		return out << to_string(f.num) << "/" << to_string(f.den); }
	
	double to_double() const { return (double) num / den; }
};
