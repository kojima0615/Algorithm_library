const ll M = pow(10, 9) + 7;

vector<ll> fac(1000001);  //n!(mod M)
vector<ll> ifac(1000001); //k!^{M-2} (mod M)
//conbination
ll comb(ll a, ll b)
{ //aCb(mod M)
    if (a == 0 && b == 0)
        return 1;
    if (a < b || a < 0)
        return 0;
    ll tmp = ifac[a - b] * ifac[b] % M;
    return tmp * fac[a] % M;
}
//素因数分解o√n
map<int, int> prime_factor(int n)
{
    map<int, int> res;
    for (int i = 2; i * i <= n; i++)
    {
        while (n % i == 0)
        {
            ++res[i];
            n /= i;
        }
    }
    if (n != 1)
        res[n] = 1;
    return res;
}
//n!
ll fact_mod(ll n)
{
    ll ret = 1;
    for (ll i = 2; i <= n; i++)
        ret = ret * (i % MOD) % MOD;
    return ret;
}

// 繰り返し二乗法
ll pow_mod(ll x, ll n)
{
    if (n == 0)
        return 1;
    ll ret = pow_mod((x * x) % MOD, n / 2);
    if (n & 1)
        ret = (ret * x) % MOD;
    return ret;
}

//nCr O(r) nがでかくても安心
ll combination_mod(ll n, ll r)
{
    if (r > n - r)
        r = n - r;
    if (r == 0)
        return 1;
    ll a = 1;
    //a=n!/(n-r)!=n~n-r+1までの総積->O(r)
    for (ll i = 0; i < r; i++)
        a = a * ((n - i) % MOD) % MOD;
    //b=inv(r!)
    ll b = pow_mod(fact_mod(r), MOD - 2);
    return (a % MOD) * (b % MOD) % MOD;
}

ll inv_mod(ll n)
{
    // フェルマーの小定理
    return pow_mod(n, MOD - 2);
}
//kが大きいときにO(n)でi+kCi (0<i<n)
vector<ll> comb_recur(ll n, ll k)
{
    vector<ll> res(n, 1);
    for (ll i = 1; i < n; i++)
    {
        res[i] *= (k + i);
        res[i] %= MOD;
        res[i] *= inv_mod(i);
        res[i] %= MOD;
        res[i] *= res[i - 1];
        res[i] %= MOD;
    }
    return res;
}
int main()
{
    fac[0] = 1;
    ifac[0] = 1;
    for (ll i = 0; i < 1000000; i++)
    {
        fac[i + 1] = fac[i] * (i + 1) % M;              // n!(mod M)
        ifac[i + 1] = ifac[i] * mpow(i + 1, M - 2) % M; // k!^{M-2} (mod M)
    }
}
