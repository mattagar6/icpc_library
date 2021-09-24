#include "line.h"
#include "vec.h"

int insideCircle(point_i p, point_i c, long long r) {	// all integer version
	long long dx = p.x - c.x, dy = p.y - c.y;
	long long Euc = dx * dx + dy * dy, rSq = r * r;
	return Euc > rSq ? 0 : Euc == rSq ? 1 : 2; } // 0/1/2 - outside/border/inside
	
int insideCircle(point p, point c, double r) {	// double version, be careful!
	double dx = p.x - c.x, dy = p.y - c.y;
	double Euc = dx * dx + dy * dy, rSq = r * r;
	return Euc > rSq + EPS ? 0 : fabs(Euc - rSq) < rSq ? 1 : 2; } // 0/1/2 - outside/border/inside

bool circle2PtsRad(point p1, point p2, double r, point& c) {
	double d2 = (p1.x - p2.x) * (p1.x - p2.x) +
				(p1.y - p2.y) * (p1.y - p2.y);
	double det = r * r / d2 - 0.25;
	if (det < 0.0) return false;
	double h = sqrt(det);
	c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
	c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
	return true; }	// to get the other center, swap p1 and p2


//////////////// Triangle + Circle Stuff ////////////////////////////////////////

// perimiter of a triangle with 3 sides
long long perimiter(long long ab, long long bc, long long ca) {		// all integer version
	return ab + bc + ca; }

double perimiter(double ab, double bc, double ca) {
	return ab + bc + ca; }

// area of triangle with sides ab, bc, ca
double area(double ab, double bc, double ca) {	// Heron's formula
	double s = perimiter(ab, bc, ca) * 0.5;
	return sqrt(s * (s - ab)) * sqrt((s - bc) * (s - ca)); }
	
// incircle of a triangle = unique circle inscribed in a triangle, touching all 3 sides
double rInCircle(double ab, double bc, double ca) {
	return area(ab, bc, ca) / (0.5 * perimiter(ab, bc, ca)); }
	
double rInCircle(point a, point b, point c) {
	return rInCircle(dist(a, b), dist(b, c), dist(c, a)); }

// returns true if there is an incircle (valid triangle)
// c will be center of incircle, r will be the radius
bool inCircle(point p1, point p2, point p3, point& c, double& r) {
	r = rInCircle(p1, p2, p3);
	if(fabs(r) < EPS) return false;
	
	line l1, l2; 	// center is meeting point of angle bisectors
	double ratio = dist(p1, p2) / dist(p1, p3);
	point p = translate(p2, scale(toVec(p2, p3), ratio / (1 + ratio)));
	pointsToLine(p1, p, l1);
	
	ratio = dist(p2, p1) / dist(p2, p3);
	p = translate(p1, scale(toVec(p1, p3), ratio / (1 + ratio)));
	pointsToLine(p2, p, l2);
	
	bool inter = areIntersect(l1, l2, c); assert(inter);
	return true; }

// circumcircle of a triangle = unique circle that touches all 3 verices of the triangle
double rCircumCircle(double ab, double bc, double ca) {
	return ab * bc * ca / (4.0 * area(ab, bc, ca)); }

double rCircumCircle(point a, point b, point c) {
	return rCircumCircle(dist(a, b), dist(b, c), dist(c, a)); }

// returns true if there is an circumcircle (valid triangle)
// c will be center of incircle, r will be the radius
bool circumCircle(point p1, point p2, point p3, point& c, double& r) {
	r = rCircumCircle(p1, p2, p3);
	if(fabs(r) < EPS) return false;
	
	line l1, l2; 	// center is intersection of perpendicular bisectors
	point p = translate(p1, scale(toVec(p1, p2), 0.5));
	point q = translate(p, rotate(scale(toVec(p1, p2), 0.5), PI / 2));
	pointsToLine(p, q, l1);
	
	p = translate(p1, scale(toVec(p1, p3), 0.5));
	q = translate(p, rotate(scale(toVec(p1, p3), 0.5), PI / 2));
	pointsToLine(p, q, l2);
	
	bool inter = areIntersect(l1, l2, c); assert(inter);
	return true; }
