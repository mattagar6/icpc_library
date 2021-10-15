/*
 * Author: Matthew Agar
 * Date: 2021-10-14
 * Source: Own
 * Description: Solves the problem:
 *               - "Is it possible to choose some subset of weights such that their sum is T?"
 *               - Normal DP approach is O(N * T) time complexity
 *               - This code is O(N * W), where W is the maximum wieght value
 *                  - Useful in cases when N = 2_000, T = 1_000_000, and all weights are < 1000
 * 
 * Time: O(N * W), Where N = weights.size(), W = max(weights)
 * 
 * Status: tested on
 *         - https://atcoder.jp/contests/abc221/tasks/abc221_g
 */

/*
 * Returns vector<bool> taken, where taken[i] = true iff weights[i] is used in the subset.
 * taken.size() == 0 if no solution exists!!!
 * target can be really big!! (1e9 is ok)
 */
vector<bool> subset_sum(const vector<int>& weights, int maxVal, int target) {
	assert(maxVal > 0);
	assert(*max_element(weights.begin(), weights.end()) <= maxVal);
	int n = weights.size();
	int b = 0, sum_break = 0;
	while(b < n && sum_break + weights[b] <= target) {
		// greedy until sum is too big
		sum_break += weights[b++];
	}
	if(b == n && sum_break < target) { // Sum of weights is too small
		return {};
	}
	const int OFFSET = target - (maxVal - 1);
	const int TAKE = -2, NONE = -1;
	vector<int> last(2 * maxVal, NONE);
	// last[i][S] = Rightmost index j <= b such that there exists a subset with sum = S,
	//              obtained by removing some elements within [j, b), keeping all elements in [0, j),
	//              and adding elements some within [b, i].
	vector<vector<int>> parent(n, vector<int>(2 * maxVal, NONE));
	last[sum_break - OFFSET] = b;
	for(int i = b; i < n; i++) {		
		vector<int> new_last = last;
		auto consider = [&](int x, int y, int who) {
			if(new_last[x] < y) {
				new_last[x] = y;
				parent[i][x] = who;
			}
		};
		for(int w = 0; w < maxVal; w++) {
			consider(w + weights[i], last[w], TAKE);
		}
		for(int w = 2 * maxVal - 1; w >= maxVal; w--) {
			for(int j = new_last[w] - 1; j >= max(0, last[w]); j--) { // O(n * maxVal) total
				consider(w - weights[j], j, j);
			}
		}
		last = move(new_last);
	}
	if(last[maxVal - 1] == NONE) {
		return {};
	}
	vector<bool> taken(n, false);
	int i = n-1, cur = maxVal - 1;
	while(i >= b) {
		int p = parent[i][cur];
		if(p == TAKE) {
			taken[i] = !taken[i];
			cur -= weights[i--];
		} else if(p == NONE) {
			i--;
		} else {
			taken[p] = !taken[p];
			cur += weights[p];
		}
	}
	while(i >= 0) {
		taken[i] = !taken[i];
		i--;
	}
	return taken;
}
