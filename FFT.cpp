//#include <tourist>
#include <bits/stdc++.h>
//#include <atcoder/all>
using namespace std;
//using namespace atcoder;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<ll, ll> p;
const int INF = 1e9;
const ll LINF = ll(1e18);
const int MOD = 1000000007;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {-1, 0, 1, 0};
const int Dx[8] = {0, 1, 1, 1, 0, -1, -1, -1}, Dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
#define yes cout << "Yes" << endl
#define YES cout << "YES" << endl
#define no cout << "No" << endl
#define NO cout << "NO" << endl
#define rep(i, n) for (int i = 0; i < n; i++)
#define FOR(i, m, n) for (int i = m; i < n; i++)
#define ALL(v) v.begin(), v.end()
#define debug(v)          \
    cout << #v << ":";    \
    for (auto x : v)      \
    {                     \
        cout << x << ' '; \
    }                     \
    cout << endl;
template <class T>
bool chmax(T &a, const T &b)
{
    if (a < b)
    {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
bool chmin(T &a, const T &b)
{
    if (b < a)
    {
        a = b;
        return 1;
    }
    return 0;
}
//cout<<fixed<<setprecision(15);有効数字15桁
//-std=c++14
//g++ yarudake.cpp -std=c++17 -I .
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
namespace FastFourierTransform
{
    using real = double;

    struct C
    {
        real x, y;

        C() : x(0), y(0) {}

        C(real x, real y) : x(x), y(y) {}

        inline C operator+(const C &c) const { return C(x + c.x, y + c.y); }

        inline C operator-(const C &c) const { return C(x - c.x, y - c.y); }

        inline C operator*(const C &c) const { return C(x * c.x - y * c.y, x * c.y + y * c.x); }

        inline C conj() const { return C(x, -y); }
    };

    const real PI = acosl(-1);
    int base = 1;
    vector<C> rts = {{0, 0},
                     {1, 0}};
    vector<int> rev = {0, 1};

    void ensure_base(int nbase)
    {
        if (nbase <= base)
            return;
        rev.resize(1 << nbase);
        rts.resize(1 << nbase);
        for (int i = 0; i < (1 << nbase); i++)
        {
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
        }
        while (base < nbase)
        {
            real angle = PI * 2.0 / (1 << (base + 1));
            for (int i = 1 << (base - 1); i < (1 << base); i++)
            {
                rts[i << 1] = rts[i];
                real angle_i = angle * (2 * i + 1 - (1 << base));
                rts[(i << 1) + 1] = C(cos(angle_i), sin(angle_i));
            }
            ++base;
        }
    }

    void fft(vector<C> &a, int n)
    {
        assert((n & (n - 1)) == 0);
        int zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for (int i = 0; i < n; i++)
        {
            if (i < (rev[i] >> shift))
            {
                swap(a[i], a[rev[i] >> shift]);
            }
        }
        for (int k = 1; k < n; k <<= 1)
        {
            for (int i = 0; i < n; i += 2 * k)
            {
                for (int j = 0; j < k; j++)
                {
                    C z = a[i + j + k] * rts[j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] = a[i + j] + z;
                }
            }
        }
    }

    vector<int64_t> multiply(const vector<int> &a, const vector<int> &b)
    {
        int need = (int)a.size() + (int)b.size() - 1;
        int nbase = 1;
        while ((1 << nbase) < need)
            nbase++;
        ensure_base(nbase);
        int sz = 1 << nbase;
        vector<C> fa(sz);
        for (int i = 0; i < sz; i++)
        {
            int x = (i < (int)a.size() ? a[i] : 0);
            int y = (i < (int)b.size() ? b[i] : 0);
            fa[i] = C(x, y);
        }
        fft(fa, sz);
        C r(0, -0.25 / (sz >> 1)), s(0, 1), t(0.5, 0);
        for (int i = 0; i <= (sz >> 1); i++)
        {
            int j = (sz - i) & (sz - 1);
            C z = (fa[j] * fa[j] - (fa[i] * fa[i]).conj()) * r;
            fa[j] = (fa[i] * fa[i] - (fa[j] * fa[j]).conj()) * r;
            fa[i] = z;
        }
        for (int i = 0; i < (sz >> 1); i++)
        {
            C A0 = (fa[i] + fa[i + (sz >> 1)]) * t;
            C A1 = (fa[i] - fa[i + (sz >> 1)]) * t * rts[(sz >> 1) + i];
            fa[i] = A0 + A1 * s;
        }
        fft(fa, sz >> 1);
        vector<int64_t> ret(need);
        for (int i = 0; i < need; i++)
        {
            ret[i] = llround(i & 1 ? fa[i >> 1].y : fa[i >> 1].x);
        }
        return ret;
    }
}; // namespace FastFourierTransform
//FFT-0(nlogn)
//多項式乗算を行う
//二つの組み合わせに使った
//小数の誤差があるので注意
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    rep(i, n)
    {
        cin >> a[i + 1] >> b[i + 1];
    }
    auto c = FastFourierTransform::multiply(a, b);
    rep(i, n * 2)
    {
        cout << c[i + 1] << "\n";
    }
}