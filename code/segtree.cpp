
template <typename M>
struct SegmentTree
{
    using T = typename M::T;

    int size;
    vector<T> node;

    SegmentTree(int n) : SegmentTree(vector<T>(n, M::id)) {}
    SegmentTree(const vector<T> &v)
    {
        size = 1;
        while (size < v.size())
            size <<= 1;
        node.resize(2 * size, M::id);
        copy(v.begin(), v.end(), node.begin() + size);
        for (int i = size - 1; i > 0; i--)
            node[i] = M::op(node[2 * i], node[2 * i + 1]);
    }

    T operator[](int k) const
    {
        return node[k + size];
    }

    void update(int k, const T &x)
    {
        k += size;
        node[k] = x;
        while (k >>= 1)
            node[k] = M::op(node[2 * k], node[2 * k + 1]);
    }

    T fold(int l, int r)
    {
        T vl = M::id, vr = M::id;
        for (l += size, r += size; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                vl = M::op(vl, node[l++]);
            if (r & 1)
                vr = M::op(node[--r], vr);
        }
        return M::op(vl, vr);
    }

    int find_first(int l, const function<bool(T)> &cond)
    {
        T vl = M::id;
        int r = 2 * size;
        for (l += size; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
            {
                T nxt = M::op(vl, node[l]);
                if (cond(nxt))
                {
                    while (l < size)
                    {
                        nxt = M::op(vl, node[2 * l]);
                        if (cond(nxt))
                            l = 2 * l;
                        else
                            vl = nxt, l = 2 * l + 1;
                    }
                    return l - size;
                }
                vl = nxt;
                l++;
            }
        }
        return -1;
    }

    int find_last(int r, const function<bool(T)> &cond)
    {
        T vr = M::id;
        int l = size;
        for (r += size; l < r; l >>= 1, r >>= 1)
        {
            if (r & 1)
            {
                r--;
                T nxt = M::op(node[r], vr);
                if (cond(nxt))
                {
                    while (r < size)
                    {
                        nxt = M::op(node[2 * r + 1], vr);
                        if (cond(nxt))
                            r = 2 * r + 1;
                        else
                            vr = nxt, r = 2 * r;
                    }
                    return r - size;
                }
                vr = nxt;
            }
        }
        return -1;
    }
};

const int mod = 1e9 + 7;

struct AddMonoid
{
    using T = int;
    static inline T id = 0;
    static T op(T a, T b)
    {
        return (a + b) % mod;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<vector<int>> A(N);
    vector<int> all;
    for (int i = 0; i < N; i++)
    {
        int M;
        cin >> M;
        for (int j = 0; j < M; j++)
        {
            int a;
            cin >> a;
            A[i].push_back(a);
            all.push_back(A[i][j]);
        }
    }
    Compress<int> comp(all);
    for (int i = 0; i < N; i++)
    {
        sort(A[i].begin(), A[i].end());
        for (int j = 0; j < A[i].size(); j++)
            A[i][j] = comp.compress(A[i][j]);
    }
    int M = 1e5 + 1;
    SegmentTree<AddMonoid> dp(M);
    for (int i = N - 1; i >= 0; i--)
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            int x = (1 + dp.fold(A[i][j] + 1, M)) % mod;
            dp.update(A[i][j], dp[A[i][j]] + x);
        }
    }
    ll ans = 1 + dp.fold(0, M);
    cout << ans << endl;
}
