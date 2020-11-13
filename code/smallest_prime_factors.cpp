//高速素因数分解 O(nlogn)
template <typename T>
vector<T> smallest_prime_factors(T n) //iの最小の素因数
{

    vector<T> spf(n + 1);
    for (int i = 0; i <= n; i++)
        spf[i] = i;

    for (T i = 2; i * i <= n; i++)
    {

        // 素数だったら
        if (spf[i] == i)
        {

            for (T j = i * i; j <= n; j += i)
            {

                // iを持つ整数かつまだ素数が決まっていないなら
                if (spf[j] == j)
                {
                    spf[j] = i;
                }
            }
        }
    }

    return spf;
}

template <typename T>
vector<T> factolization(T x, vector<T> &spf)
{
    vector<T> ret;
    while (x != 1)
    {
        ret.push_back(spf[x]);
        x /= spf[x];
    }
    sort(ret.begin(), ret.end());
    return ret;
}
constexpr int MAX = 1000000;

auto spf = smallest_prime_factors(MAX);

int Q;
cin >> Q;

while (Q--)
{
    int x;
    cin >> x;

    auto result = factolization(x, spf);
    //重複要素を含むので適当に消してください
    //r.erase(unique(ALL(r)), r.end());
    for (auto z : result)
        cout << z << " ";
    cout << endl;
}