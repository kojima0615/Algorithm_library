#include <iostream>
#include <functional>
#include <vector>
#include <stack>

template <class Monoid, Monoid e>
struct SWAG
{
    std::function<Monoid(Monoid, Monoid)> op;
    std::vector<Monoid> v;
    Monoid front;
    std::stack<Monoid> back;
    size_t l, r;
    explicit SWAG(std::function<Monoid(Monoid, Monoid)> op)
        : op(std::move(op)), v(), front(e), back(), l(0), r(0){};
    SWAG(std::function<Monoid(Monoid, Monoid)> op, std::vector<Monoid> &v_)
        : op(std::move(op)), v(v_.size()), front(e), back(), l(0), r(0)
    {
        std::copy(v_.begin(), v_.end(), v.begin());
    };
    Monoid fold(size_t i, size_t j)
    {
        while (r < j)
            front = op(front, v[r++]);
        while (l < i)
        {
            if (back.empty())
            {
                Monoid tmp{e};
                for (size_t u = r; u-- > l;)
                    back.emplace(tmp = op(v[u], tmp));
                front = e;
            }
            back.pop();
            ++l;
        }
        if (back.empty())
            return front;
        return op(back.top(), front);
    }
};

template <class T>
T gcd(T n, T m)
{
    while (m)
    {
        n %= m;
        std::swap(n, m);
    }
    return n;
}

template <class T>
T lcm(T n, T m)
{
    T c = n * m / gcd(n, m);
    if (c > 1000000001)
        c = 1000000001;
    return c;
}

int main()
{
    using ll = long long;
    int n;
    ll x;
    std::cin >> n >> x;
    std::vector<ll> a(n);
    for (auto &i : a)
        std::cin >> i;
    std::function<ll(ll, ll)> op = [](ll i, ll j) { return lcm(i, j); };
    SWAG<ll, 1> sw(op, a);
    int r = 0, ans = 0, ansl = 0;
    for (int l = 0; l < n; ++l)
    {
        while (r < n && sw.fold(l, r + 1) < x)
            ++r;
        if (ans < r - l)
        {
            ans = r - l;
            ansl = l;
        }
    }
    std::cout << ansl + 1 << " " << ansl + ans << std::endl;
}
//https: //www.hackerrank.com/contests/tsg-live-4-programming-contest/challenges/tsg-live-4-procon-lcm-interval