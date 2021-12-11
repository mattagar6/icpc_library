// This will take a matrix A[N][N] and choose one item for each row 
// such that the sum of all items is minimized.
// Time: O(n^3)

const int N = 105;

using T = long long; // Cost Type
const T INF = numeric_limits<T>::max();

T A[N][N];
int n;

void hungarian() { // A is 1-Indexed!!! XXX
	vector<T> u(n+1), v(n+1);
	vector<int> p(n+1), way(n+1);
	for(int i = 1; i <= n; i++) {
		p[0] = i; int j0 = 0;
		vector<T> minv(n+1, INF);
		vector<bool> used(n+1, false);
		do {
			used[j0] = true;
			int i0 = p[j0], j1;
			T delta = INF;
			for(int j = 1; j <= n; j++) 
				if(!used[j]) {
					T cur = A[i0][j]-u[i0]-v[j];
					if(cur < minv[j])
						minv[j] = cur, way[j] = j0;
					if(minv[j] < delta)
						delta = minv[j], j1 = j;
				}
			for(int j = 0; j <= n; j++) 
				if(used[j])
					u[p[j]] += delta, v[j] -= delta;
				else
					minv[j] -= delta;
			j0 = j1;
		} while(p[j0] != 0);
		do {
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while(j0);
	}
	vector<int> ans(n+1);
	for(int j = 1; j <= n; j++) ans[p[j]] = j;
}
