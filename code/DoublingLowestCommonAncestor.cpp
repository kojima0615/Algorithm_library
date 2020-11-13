//#include <tourist>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <list>
#include <queue>
#include <tuple>
#include <deque>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <utility>
#include <complex>
#include <functional>
using namespace std;
const int MOD = 1000000007;
typedef long long ll;
typedef pair<ll, ll> p;
const int INF = (1 << 28);
const int dx[4] = {0, 1, 0, -1}, dy[4] = {-1, 0, 1, 0};
const int Dx[8] = {0, 1, 1, 1, 0, -1, -1, -1}, Dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
#define yes cout << "Yes" << endl
#define YES cout << "YES" << endl
#define no cout << "No" << endl
#define NO cout << "NO" << endl
#define REP(i, n) for (int i = 0; i < n; i++)
#define REPR(i, n) for (int i = n; i >= 0; i--)
#define FOR(i, m, n) for (int i = m; i < n; i++)
#define INF 2e9
#define ALL(v) v.begin(), v.end()
//setprecision(15)有効数字15桁
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b)
{
    return a * b / gcd(a, b);
}
template <typename T>
struct edge
{
    int src, to;
    T cost;

    edge(int to, T cost) : src(-1), to(to), cost(cost) {}

    edge(int src, int to, T cost) : src(src), to(to), cost(cost) {}

    edge &operator=(const int &x)
    {
        to = x;
        return *this;
    }

    operator int() const { return to; }
};

template <typename T>
using Edges = vector<edge<T>>;
template <typename T>
using WeightedGraph = vector<Edges<T>>;
using UnWeightedGraph = vector<vector<int>>;
template <typename T>
using Matrix = vector<vector<T>>;
template <typename G>
struct DoublingLowestCommonAncestor
{
    const int LOG;
    vector<int> dep;
    const G &g;
    vector<vector<int>> table;

    DoublingLowestCommonAncestor(const G &g) : g(g), dep(g.size()), LOG(32 - __builtin_clz(g.size()))
    {
        table.assign(LOG, vector<int>(g.size(), -1));
    }

    void dfs(int idx, int par, int d)
    {
        table[0][idx] = par;
        dep[idx] = d;
        for (auto &to : g[idx])
        {
            if (to != par)
                dfs(to, idx, d + 1);
        }
    }

    void build()
    {
        dfs(0, -1, 0);
        for (int k = 0; k + 1 < LOG; k++)
        {
            for (int i = 0; i < table[k].size(); i++)
            {
                if (table[k][i] == -1)
                    table[k + 1][i] = -1;
                else
                    table[k + 1][i] = table[k][table[k][i]];
            }
        }
    }

    int query(int u, int v)
    {
        if (dep[u] > dep[v])
            swap(u, v);
        for (int i = LOG - 1; i >= 0; i--)
        {
            if (((dep[v] - dep[u]) >> i) & 1)
                v = table[i][v];
        }
        if (u == v)
            return u;
        for (int i = LOG - 1; i >= 0; i--)
        {
            if (table[i][u] != table[i][v])
            {
                u = table[i][u];
                v = table[i][v];
            }
        }
        return table[0][u];
    }
};
int main()
{
    int N, Q;
    scanf("%d", &N);
    UnWeightedGraph g(N);
    for (int i = 0; i < N; i++)
    {
        int k;
        scanf("%d", &k);
        while (k--)
        {
            int c;
            scanf("%d", &c);
            g[i].push_back(c);
        }
    }
    DoublingLowestCommonAncestor<UnWeightedGraph> lca(g);
    //0がrootになっているので変えたいときはbuild()のdfsをいじりましょう
    lca.build();
    scanf("%d", &Q);
    while (Q--)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", lca.query(x, y));
    }
}