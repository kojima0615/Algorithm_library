typedef vector<ll> Array;
typedef vector<Array> Matrix;
ll mod_pow(ll x, ll n, ll mod)
{
    ll res = 1LL;
    while (n > 0)
    {
        if (n & 1)
            res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

ll mod_inv(ll x, ll mod)
{
    return mod_pow(x, mod - 2, mod);
}

Matrix mIdentity(ll n)
{
    Matrix A(n, Array(n));
    for (int i = 0; i < n; ++i)
        A[i][i] = 1;
    return A;
}

Matrix mMul(const Matrix &A, const Matrix &B, ll mod)
{
    Matrix C(A.size(), Array(B[0].size()));
    for (int i = 0; i < C.size(); ++i)
        for (int j = 0; j < C[i].size(); ++j)
            for (int k = 0; k < A[i].size(); ++k)
                (C[i][j] += (A[i][k] % mod) * (B[k][j] % mod)) %= mod;
    return C;
}
// O( n^3 log e )
Matrix mPow(const Matrix &A, ll e, ll mod)
{
    return e == 0 ? mIdentity(A.size()) : e % 2 == 0 ? mPow(mMul(A, A, mod), e / 2, mod) : mMul(A, mPow(A, e - 1, mod), mod);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m, k, p, q;
    cin >> n >> m >> k >> p >> q;
    ll pq = (p * mod_inv(q, MOD)) % MOD;
    ll pq_ = (1 - pq + MOD) % MOD;

    Matrix x(2, Array(2, pq));
    REP(i, 2)
    x[i][i] = pq_;

    Matrix f = mPow(x, k, MOD);

    ll ans = 0;
    REP(i, m)
    {
        ll b;
        cin >> b;
        Matrix dp0({{b}, {0}});
        Matrix dp = mMul(f, dp0, MOD);
        (ans += dp[0][0]) %= MOD;
    }

    rep(i, m, n)
    {
        ll b;
        cin >> b;
        Matrix dp0({{0}, {b}});
        Matrix dp = mMul(f, dp0, MOD);
        (ans += dp[0][0]) %= MOD;
    }
    cout << ans << en;
}
//https://yukicoder.me/problems/no/995
//a(n+1)=2*a(n)+3*a(n-1)
//((2,3)(1,0))の累乗で求める
//https://www.simplex-soft.com/pdf/Formula_of_Fibonacci_number_using_the_golden_number.pdf