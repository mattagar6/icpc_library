#include <bits/stdc++.h>
using namespace std;

// Longest palindromic substring, O(n)
int manachers(string s) {
	int n = s.size();
	vector<int> d1(n); 
	// Odd length, d1[i] = half the length of the odd palindrome centered at i, rounded up
	// Get actual length by 2 * d1[i] - 1
	int ans = 0;
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
		while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) 
			k++;
		d1[i] = k--;
		ans = max(ans, 2 * d1[i] - 1);
		if (i + k > r) {
			l = i - k;
			r = i + k;
		}
	}	
	vector<int> d2(n);
	// Even length, d2[i] = half the length of the even palindrome right-centered at i
	// Get actual length by 2 * d2[i] 
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
		while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) 
			k++;
		d2[i] = k--;
		ans = max(ans, 2 * d2[i]);
		if (i + k > r) {
			l = i - k - 1;
			r = i + k;
		}
	}	
	return ans;
}

int main() {
	
	string s = "aabcbaca";
	cout << manachers(s) << "\n";
	
	return 0;
}
