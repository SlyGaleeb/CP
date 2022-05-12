string convert_base(ll n, int base) {
	if (n==0)
		return "0";
	ll power = 1;
	while (power*base<=n)
		power *= base;
	string result;
	while (power>0) {
		ll k = n/power;
		result += k + '0';
		n -= power*k;
		power /= base;
	}
	return result;
}
