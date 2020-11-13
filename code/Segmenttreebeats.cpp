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

template <typename T>
struct SegmentTreeBeats
{
    SegmentTreeBeats(int n) : SegmentTreeBeats(vector<T>(n)) {}
    SegmentTreeBeats(const vector<T> &v)
    {
        size = 1;
        while (size < v.size())
            size <<= 1;
        sum.resize(2 * size);//区間和
        lazy.resize(2 * size);
        max_val.resize(2 * size, NINF);//最大値
        smax_val.resize(2 * size, NINF);//二番目の最大値
        max_cnt.resize(2 * size);//最大値の個数
        min_val.resize(2 * size, INF);
        smin_val.resize(2 * size, INF);
        min_cnt.resize(2 * size);
        len.resize(2 * size);
        len[1] = size;
        for (int i = 2; i < 2 * size; i++)
            len[i] = len[i / 2] >> 1;
        for (int i = 0; i < v.size(); i++)
        {
            sum[size + i] = max_val[size + i] = min_val[size + i] = v[i];
            max_cnt[size + i] = min_cnt[size + i] = 1;
        }
        for (int i = size - 1; i > 0; i--)
            recalc(i);
    }
    //indexはそのままでアクセスできる
    T operator[](int k)
    {
        return fold_sum(k, k + 1);
    }
    //区間chminクエリ: i∈[l,r)i∈[l,r)について aiを min(ai,x)min(ai,x)に更新
    void chmin(int l, int r, T x) { update<CHMIN>(l, r, x, 1, 0, size); }
    void chmax(int l, int r, T x) { update<CHMAX>(l, r, x, 1, 0, size); }
    void add(int l, int r, T x) { update<ADD>(l, r, x, 1, 0, size); }
    //RMQ
    T fold_min(int l, int r) { return fold<MIN>(l, r, 1, 0, size); }
    T fold_max(int l, int r) { return fold<MAX>(l, r, 1, 0, size); }
    //RSQ
    T fold_sum(int l, int r) { return fold<SUM>(l, r, 1, 0, size); }

private:
    const T INF = numeric_limits<T>::max();
    const T NINF = numeric_limits<T>::min();

    int size;
    vector<T> sum, lazy;
    vector<T> max_val, smax_val;
    vector<T> min_val, smin_val;
    vector<int> len, max_cnt, min_cnt;

    enum OpType
    {
        CHMIN,
        CHMAX,
        ADD
    };

    enum QueryType
    {
        MIN,
        MAX,
        SUM
    };

    void recalc(int k)
    {
        sum[k] = sum[2 * k] + sum[2 * k + 1];

        if (max_val[2 * k] > max_val[2 * k + 1])
        {
            max_val[k] = max_val[2 * k];
            max_cnt[k] = max_cnt[2 * k];
            smax_val[k] = max(smax_val[2 * k], max_val[2 * k + 1]);
        }
        else if (max_val[2 * k] < max_val[2 * k + 1])
        {
            max_val[k] = max_val[2 * k + 1];
            max_cnt[k] = max_cnt[2 * k + 1];
            smax_val[k] = max(max_val[2 * k], smax_val[2 * k + 1]);
        }
        else
        {
            max_val[k] = max_val[2 * k];
            max_cnt[k] = max_cnt[2 * k] + max_cnt[2 * k + 1];
            smax_val[k] = max(smax_val[2 * k], smax_val[2 * k + 1]);
        }

        if (min_val[2 * k] < min_val[2 * k + 1])
        {
            min_val[k] = min_val[2 * k];
            min_cnt[k] = min_cnt[2 * k];
            smin_val[k] = min(smin_val[2 * k], min_val[2 * k + 1]);
        }
        else if (min_val[2 * k] > min_val[2 * k + 1])
        {
            min_val[k] = min_val[2 * k + 1];
            min_cnt[k] = min_cnt[2 * k + 1];
            smin_val[k] = min(min_val[2 * k], smin_val[2 * k + 1]);
        }
        else
        {
            min_val[k] = min_val[2 * k];
            min_cnt[k] = min_cnt[2 * k] + min_cnt[2 * k + 1];
            smin_val[k] = min(smin_val[2 * k], smin_val[2 * k + 1]);
        }
    }

    template <OpType TYPE>
    void tag(int k, T x)
    {
        if (TYPE == CHMIN)
        {
            sum[k] += (x - max_val[k]) * max_cnt[k];
            if (max_val[k] == min_val[k])
                min_val[k] = x;
            else if (max_val[k] == smin_val[k])
                smin_val[k] = x;
            max_val[k] = x;
        }
        else if (TYPE == CHMAX)
        {
            sum[k] += (x - min_val[k]) * min_cnt[k];
            if (min_val[k] == max_val[k])
                max_val[k] = x;
            else if (min_val[k] == smax_val[k])
                smax_val[k] = x;
            min_val[k] = x;
        }
        else if (TYPE == ADD)
        {
            min_val[k] += x;
            if (smin_val[k] != INF)
                smin_val[k] += x;
            max_val[k] += x;
            if (smax_val[k] != NINF)
                smax_val[k] += x;
            sum[k] += x * len[k];
            lazy[k] += x;
        }
    }

    void push(int k)
    {
        if (lazy[k] != 0)
        {
            tag<ADD>(2 * k, lazy[k]);
            tag<ADD>(2 * k + 1, lazy[k]);
            lazy[k] = 0;
        }
        if (max_val[k] < max_val[2 * k])
            tag<CHMIN>(2 * k, max_val[k]);
        if (min_val[k] > min_val[2 * k])
            tag<CHMAX>(2 * k, min_val[k]);
        if (max_val[k] < max_val[2 * k + 1])
            tag<CHMIN>(2 * k + 1, max_val[k]);
        if (min_val[k] > min_val[2 * k + 1])
            tag<CHMAX>(2 * k + 1, min_val[k]);
    }

    template <OpType TYPE>
    inline bool break_cond(int k, T x)
    {
        if (TYPE == CHMIN)
            return max_val[k] <= x;
        if (TYPE == CHMAX)
            return min_val[k] >= x;
        if (TYPE == ADD)
            return false;
    }

    template <OpType TYPE>
    inline bool tag_cond(int k, T x)
    {
        if (TYPE == CHMIN)
            return smax_val[k] < x;
        if (TYPE == CHMAX)
            return smin_val[k] > x;
        if (TYPE == ADD)
            return true;
    }

    template <OpType TYPE>
    void update(int a, int b, T x, int k, int l, int r)
    {
        if (r <= a || b <= l || break_cond<TYPE>(k, x))
            return;
        if (a <= l && r <= b && tag_cond<TYPE>(k, x))
        {
            tag<TYPE>(k, x);
            return;
        }
        push(k);
        int m = (l + r) / 2;
        update<TYPE>(a, b, x, 2 * k, l, m);
        update<TYPE>(a, b, x, 2 * k + 1, m, r);
        recalc(k);
    }

    template <QueryType TYPE>
    T fold(int a, int b, int k, int l, int r)
    {
        if (r <= a || b <= l)
        {
            if (TYPE == MIN)
                return INF;
            if (TYPE == MAX)
                return NINF;
            if (TYPE == SUM)
                return 0;
        }
        if (a <= l && r <= b)
        {
            if (TYPE == MIN)
                return min_val[k];
            if (TYPE == MAX)
                return max_val[k];
            if (TYPE == SUM)
                return sum[k];
        }
        push(k);
        int m = (l + r) / 2;
        T vl = fold<TYPE>(a, b, 2 * k, l, m);
        T vr = fold<TYPE>(a, b, 2 * k + 1, m, r);
        if (TYPE == MIN)
            return min(vl, vr);
        if (TYPE == MAX)
            return max(vl, vr);
        if (TYPE == SUM)
            return vl + vr;
        return -1;
    }
};
//ABC179-F
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n, q;
    cin >> n >> q;
    vector<int> v(n - 2, n - 2);
    SegmentTreeBeats<int> t1(v), t2(v); //縦横の選ばれた時の取れる個数
    ll ans = (n - 2) * (n - 2);
    rep(i, q)
    {
        int t, x;
        cin >> t >> x;
        x -= 2;
        if (t == 1)
        {
            int c = t1[x];
            ans -= c;
            t2.chmin(0, c, x);
        }
        else
        {
            int c = t2[x];
            ans -= c;
            t1.chmin(0, c, x);
        }
    }
    cout<<ans<<"\n";
}