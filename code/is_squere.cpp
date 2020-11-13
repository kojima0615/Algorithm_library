//平方数判定
bool is_squere(long long N)
{
    long long r = (long long)floor(sqrt((long double)N)); // 切り捨てした平方根
    return (r * r) == N;
}
//平方数判定, 多分大丈夫O(logn)
bool is_squere2(long long N)
{
    ll l = 0, r = INF;
    while (r - l > 1)
    {
        ll mid = (r + l) / 2;
        if (pow(mid, 2) <= N)
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    return N == pow(l, 2);
}