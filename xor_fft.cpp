/*
 * Author: AndreySergunin
 * Date: Unknown
 * Source: Bubble Cup 12 - Finals
 * Description: Given arrays A, B, compute
                C[i ^ j] = sum(A[i] * B[j]), 0 <= i < n, 0 <= j < n (n is a power of 2)
 * Time: O(n * log(n)) for xorProduct, xorConvolution
 * Status: tested on 
           - https://codeforces.com/contest/1218/submission/120311571
           - https://codeforces.com/gym/103202/submission/126719895 
 */
 
using T = long long;
const long long P = 1e9 + 7;
 
void mul(T &a, T b) {
    a = a * b % P;
}
 
void add(T &a, T b) {
    a += b;
    if (a >= P) {
        a -= P;
    }
}
 
void sub(T &a, T b) {
    a -= b;
    if (a < 0) {
        a += P;
    }
}
 
T binPow(T a, T b) {
    T res = 1;
    T x = a;
    for (; b > 0; b >>= 1) {
        if (b & 1) {
            mul(res, x);
        }
        mul(x, x);
    }
    return res;
}
 
vector<T> xorConvolution(vector<T> cur) {
    int n = sz(cur);
    vector<T> ncur(n);
    for (int len = 1; len < n; len <<= 1) {
        for (int pos = 0; pos < n; pos += len) {
            for (int i = 0; i < len; ++pos, ++i) {
                ncur[pos] = cur[pos];
                add(ncur[pos], cur[pos + len]);
 
                ncur[pos + len] = cur[pos];
                sub(ncur[pos + len], cur[pos + len]);
            }
        }
        cur.swap(ncur);
    }
    return cur;
}
 
vector<T> xorProduct(vector<T> a, vector<T> b) {
    int n = 1;
    for (; n < max(sz(a), sz(b)); n <<= 1);
    a.resize(n);
    b.resize(n);
    a = xorConvolution(a);
    b = xorConvolution(b);
    int rn = binPow(n, P - 2);
    for (int i = 0; i < n; ++i) {
        mul(a[i], b[i]);
        mul(a[i], rn);
    }
    return xorConvolution(a);
}
