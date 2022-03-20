#include <bits/stdc++.h>
using namespace std;

#define sz(x) ((int)(x.size()))
#define all(x) x.begin(), x.end()

using ll = long long;
using ld = long double;

ld read_double() {
	string s;
	cin >> s;
	return stod(s);
}

struct P {
	ll x, y;
	void read() {
		cin >> x >> y;
	}

	ll cross(const P& a, const P& b) const {
		return (a.x - x) * (b.y - y) - (a.y - y) * (b.x - x);
	}
	bool operator<(const P& a) const {
		return make_pair(x, y) < make_pair(a.x, a.y);
	}
};

// change > to >= to allow collinear points
vector<P> convexHull(vector<P> pts) {
	sort(all(pts));
	if(sz(pts) <= 2) return pts;
	vector<P> hull;
	for(int rep = 0; rep < 2; rep++) {
		const int S = sz(hull);
		for(P c : pts) {
			while(sz(hull) >= S+2) {
				P a = hull.end()[-2];
				P b = hull.end()[-1];
				if(a.cross(b, c) >= 0) {
					break;
				}
				hull.pop_back();
			}
			hull.push_back(c);
		}
		hull.pop_back();
		reverse(all(pts));
	}
	return hull;
}

// assumes poly is oriented clockwise or ccw
// returns 2*A, where A is the area of poly
ll polygonArea(vector<P> poly) {
	ll A = 0;
	int N = sz(poly);
	for(int i = 0; i < N; i++) {
		int j = i + 1 == N ? 0 : i + 1;
		A += poly[i].x * poly[j].y - poly[i].y * poly[j].x;
	}
	return abs(A);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
}
