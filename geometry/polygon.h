#include "vec.h"

/*
	Notes:
		* Assumes P[0] == P[n-1] 
		* Order vertices in counter-clockwise order!
		* Be careful with collinear points!!
*/

double perimeter(const vector<point>& P) {	
	double ans = 0.0;
	rep(i,0,sz(P)-1) ans += dist(P[i], P[i+1]);
	return ans; }
	
double area(const vector<point>& P) {	// shoelace formula
	double ans = 0.0;
	rep(i,0,sz(P)-1) ans += P[i].x * P[i+1].y - P[i+1].x * P[i].y;
	return fabs(ans) / 2; }

bool isConvex(const vector<point>& P) { // be careful with collinear points!!!
	int N = sz(P);
	if(N <= 3) return false; // a point (N = 2) or a line (N = 3) is not convex.
	bool isLeft = ccw(P[0], P[1], P[2]);
	rep(i,1,sz(P)-1)
		if(ccw(P[i], P[i+1], P[i+2 == N ? 0 : i+2) != isLeft)
			return false;
	return true; }

bool inPolygon(point pt, const vector<point>& P) {	// be careful if pt is on the sides of the polygon!
	double sum = 0.0;
	rep(i,0,sz(P)-1) {
		//~ point tmp;
		//~ if(distToLineSegment(pt, P[i], P[i+1], tmp) < EPS) return true; // On side of Polygon
		if(ccw(pt, P[i], P[i+1])) sum += angle(P[i], pt, P[i+1]);
		else sum -= angle(P[i], pt, P[i+1]);
	}
	return fabs(sum - 2 * PI) < EPS; }

vector<point> CH(vector<point> P) { 	// the content of P may be shuffled
	int n = sz(P);                      // Duplicate points are BAD!!!!
	if(n < 3) {
		if(!(P[0] == P[n-1])) P.pb(P[0]);
		return P; }
	
	int P0 = 0; // index of pivot, (lowest, then rightmost)
	rep(i,0,n) if(P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x)) P0 = i;
	swap(P[0],P[P0]);
	point pivot = P[0];
	sort(++P.begin(), P.end(), [&](point a, point b) {
		if(collinear(pivot, a, b)) return dist(pivot, a) < dist(pivot, b);
		double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
		double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
		return atan2(d1y, d1x) < atan2(d2y, d2x); }); // Sort by angle (counter clockwise)
	
	vector<point> S;
	S.pb(P[n-1]); S.pb(P[0]), S.pb(P[1]);
	int i = 2;
	while(i < n) {	// always turn left
		int j = sz(S)-1;
		if(ccw(S[j-1], S[j], P[i])) S.pb(P[i++]); // colinear points -> change ccw
		else S.pop_back();
	}
	return S; } // S[0] == S[n-1]

// line segment p-q intersect with line A-B. 
point lineIntersectSeg(point p, point q, point A, point B) {
	double a = B.y - A.y;
	double b = A.x - B.x;
	double c = B.x * A.y - A.x * B.y;
	double u = fabs(a * p.x + b * p.y + c);
	double v = fabs(a * q.x + b * q.y + c); assert(u + v > 0); // u + v = 0 => no intersect
	return point((p.x * v + q.x * u) / (u + v), (p.y * v + q.y * u) / (u + v)); }

// cuts polygon Q along the line formed by point a -> point b
// (note: the last point of Q must be the same as the first point)
array<vector<point>,2> cutPolygon(point a, point b, const vector<point>& Q) {
	array<vector<point>,2> P; // 0 = left, 1 = right
	rep(i,0,sz(Q)) {
		double l1 = cross(toVec(a,b), toVec(a, Q[i])), l2 = 0;
		if(i+1 != sz(Q)) l2 = cross(toVec(a,b), toVec(a, Q[i+1]));
		if(l1 > -EPS) P[0].pb(Q[i]); // on left
		if(l1 < EPS) P[1].pb(Q[i]); // on right
		if(l1 * l2 < -EPS) { // edge Q[i], Q[i+1] crosses line ab
			rep(j,0,2) P[j].pb(lineIntersectSeg(Q[i], Q[i+1], a, b));
		} 
	}
	rep(i,0,2) if(sz(P[i]) && !(P[i].back() == P[i][0])) P[i].pb(P[i][0]); // make first point == last point
	return P; }
