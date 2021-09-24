/*
 * Author: Matthew Agar
 * Date: Unknown.
 * Source: Own work
 * Description: Sparse table for range minimum query
 * Time: O(n * log(n)) for build, O(1) for get.
 * Status: stress-tested
 */

int msb(int nn) {
    assert(nn > 0);
    return 31 - __builtin_clz(nn);
}

template<typename T>
struct SparseTable {
    int n;
    vector<vector<T>> tab;
    void build(vector<T> a) {
        n = a.size();
        int B = msb(n) + 1;
        tab.resize(B);
        for(int b = 0; b < B; b++) {
            tab[b].resize(n);
            int len = 1<<b;
            for(int i = 0; i <= n-len; i++) {
                if(len == 1) 
                    tab[b][i] = a[i];
                else 
                    tab[b][i] = min(tab[b-1][i], tab[b-1][i+len/2]);
            }
        }
    }
    T get(int L, int R) const { // [l, r]
        int b = msb(R - L + 1);
        return min(tab[b][L], tab[b][R-(1<<b)+1]);
    }
};
