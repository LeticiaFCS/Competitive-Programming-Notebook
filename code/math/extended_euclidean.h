#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll extGcd(ll a, ll b, ll &x, ll &y){
	if (b == 0){
		x = 1, y = 0;
		return a;
	}else{
		ll g = extGcd(b, a % b, y, x);
		y -= (a / b) * x;
		return g;
	}
}
ll inv(ll a, ll mod){
	ll inv_x, y;
	extGcd(a, mod, inv_x, y);
	return (inv_x%mod + mod)%mod;		
}
//a*x + b*y = g
//a*(x-(b/g)*k) + b*(y+(a/g)*k) = g
bool dioEq(ll a, ll b, ll c, ll &x0, ll &y0, ll &g){
	g = extGcd(abs(a), abs(b), x0, y0);
	if (c % g) return false;
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0) x0 = -x0;
	if (b < 0) y0 = -y0;
	return true;
}
inline void shift_solution(ll &x, ll &y, ll a, ll b, ll cnt){
	x += cnt * b;
	y -= cnt * a;
}
ll findAllSolutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy){
	ll x, y, g;
	if (!dioEq(a, b, c, x, y, g))
		return 0;
	a /= g;
	b /= g;
	int sign_a = a > 0 ? +1 : -1;
	int sign_b = b > 0 ? +1 : -1;
	shift_solution(x, y, a, b, (minx - x) / b);
	if (x < minx)
		shift_solution(x, y, a, b, sign_b);
	if (x > maxx)
		return 0;
	ll lx1 = x;
	shift_solution(x, y, a, b, (maxx - x) / b);
	if (x > maxx)
		shift_solution(x, y, a, b, -sign_b);
	ll rx1 = x;
	shift_solution(x, y, a, b, -(miny - y) / a);
	if (y < miny)
		shift_solution(x, y, a, b, -sign_a);
	if (y > maxy)
		return 0;
	ll lx2 = x;
	shift_solution(x, y, a, b, -(maxy - y) / a);
	if (y > maxy)
		shift_solution(x, y, a, b, sign_a);
	ll rx2 = x;
	if (lx2 > rx2)
		swap(lx2, rx2);
	ll lx = max(lx1, lx2);
	ll rx = min(rx1, rx2);
	if (lx > rx)
		return 0;
	return (rx - lx) / abs(b) + 1;
}
