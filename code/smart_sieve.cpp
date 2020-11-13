
// 負の数にも対応した mod (a = -11 とかでも OK)
inline long long mod(long long a, long long m)
{
    long long res = a % m;
    if (res < 0)
        res += m;
    return res;
}

// 拡張 Euclid の互除法
long long extGCD(long long a, long long b, long long &p, long long &q)
{
    if (b == 0)
    {
        p = 1;
        q = 0;
        return a;
    }
    long long d = extGCD(b, a % b, q, p);
    q -= a / b * p;
    return d;
}

// 逆元計算 (ここでは a と m が互いに素であることが必要)
long long modinv(long long a, long long m)
{
    long long x, y;
    extGCD(a, m, x, y);
    return mod(x, m); // 気持ち的には x % m だが、x が負かもしれないので
}

// Garner のアルゴリズム, x%MOD, LCM%MOD を求める (m は互いに素でなければならない)
// for each step, we solve "coeffs[k] * t[k] + constants[k] = b[k] (mod. m[k])"
//      coeffs[k] = m[0]m[1]...m[k-1]
//      constants[k] = t[0] + t[1]m[0] + ... + t[k-1]m[0]m[1]...m[k-2]
//n個x%y[i]=z[i]が与えられた時にxを求めるO(n^2)
long long Garner(vector<long long> b, vector<long long> m, long long MOD)
{
    m.push_back(MOD); // banpei
    vector<long long> coeffs((int)m.size(), 1);
    vector<long long> constants((int)m.size(), 0);
    for (int k = 0; k < (int)b.size(); ++k)
    {
        long long t = mod((b[k] - constants[k]) * modinv(coeffs[k], m[k]), m[k]);
        for (int i = k + 1; i < (int)m.size(); ++i)
        {
            (constants[i] += t * coeffs[i]) %= m[i];
            (coeffs[i] *= m[k]) %= m[i];
        }
    }
    return constants.back();
}

//10^6程度の区間を前処理ありでO(logn)素因数分解
class smart_sieve
{
    ll L, R, M;
    vector<int> small;        // 小さい篩
    vector<vector<ll>> large; // 大きい篩
    vector<ll> aux;           // aux[i] := large[i] の素因数の積

public:
    smart_sieve(ll L, ll R) : L(L), R(R), M(sqrt(R) + 1)
    {
        small.resize(M);
        iota(small.begin(), small.end(), 0);
        large.resize(R - L);
        aux.assign(R - L, 1);

        for (ll i = 2; i * i < R; ++i)
        {
            if (small[i] < i)
                continue;
            small[i] = i;
            for (ll j = i * i; j < M; j += i)
                if (small[j] == j)
                    small[j] = i;

            for (ll j = (L + i - 1) / i * i; j < R; j += i)
            {
                ll k = j;
                do
                {
                    // aux[j-L] > M で判定した方がいいかも？
                    // j / aux[j-L] < M の方がいい？（割り算したくない）
                    if (aux[j - L] * aux[j - L] > R)
                        break;

                    large[j - L].push_back(i);
                    aux[j - L] *= i;
                    k /= i;
                } while (k % i == 0);
            }
        }
    }

    vector<ll> factor(ll n)
    {
        assert(L <= n && n < R);
        vector<ll> res = large[n - L];
        n /= aux[n - L];
        if (n >= M)
        {
            // この場合，n は素数となることが示せる（はず）
            // n*n >= R だとオーバーフローしそう？
            res.push_back(n);
            return res;
        }
        while (n > 1)
        {
            res.push_back(small[n]);
            n /= small[n];
        }
        return res;
    }
};

int main()
{
    ll L, R;
    scanf("%jd %jd", &L, &R);

    smart_sieve ss(L, R);
    for (ll i = L; i < R; ++i)
    {
        auto f = ss.factor(i);
        printf("%jd:", i);
        for (auto j : f)
            printf(" %jd", j);
        printf("\n");
    }
}
