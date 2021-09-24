/*
   Suppose:
      t = a1 % n1 and
      t = a2 % n2, (n1, n2 not necessarily coprime)
    
    this implies:
      t = a1 + n1 * k1 and
      t = a2 + n2 * k2
    
    so 
      a1 + n1 * k1 = a2 + n2 * k2,
      n1 * (-k1) + n2 * k2 = a1 - a2, (dont forget -k1 !!!)
	
    so gcd(n1, n2) must divide a1 - a2 for a solution to exist

    let [x, y, g] = ex_gcd(n1, n2)
    multiply x by -(a1 - a2) / g,
    multiply y by  (a1 - a2) / g

    then t = a1 + x * m1
    if t is a solution, so is t + lcm(n1, n2)
    
    Example submission:
       - https://codeforces.com/contest/724/submission/126798990
*/

array<ll,3> ex_gcd(ll a, ll b) { // returns (x, y, g) such that a * x + b * y = g
	if(b == 0)
		return {1, 0, a};
	auto [x, y, g] = ex_gcd(b, a % b);
	return {y, x - (a/b)*y, g};
}

ll lcm(ll a, ll b) {
	return a / __gcd(a, b) * b;
}
