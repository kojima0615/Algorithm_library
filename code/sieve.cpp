const int N = pow(10, 5);

vector<bool> isp(N + 1, true);
//エラトステネスの篩
vector<bool> sieve(int n)
{
    vector<bool> isp(n + 1, true);
    isp[0] = false;
    isp[1] = false;
    for (int i = 2; pow(i, 2) <= n; i++)
    {
        if (isp[i])
            for (int j = 2; i * j <= n; j++)
                isp[i * j] = false;
    }
    return isp;
}