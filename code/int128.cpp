ostream &operator<<(ostream &dest, __int128_t value)
{
    ostream::sentry s(dest);
    if (s)
    {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = std::end(buffer);
        do
        {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);
        if (value < 0)
        {
            --d;
            *d = '-';
        }
        int len = end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len)
        {
            dest.setstate(ios_base::badbit);
        }
    }
    return dest;
}

__int128 parse(string &s)
{
    __int128 ret = 0;
    for (int i = 0; i < s.length(); i++)
        if ('0' <= s[i] && s[i] <= '9')
            ret = 10 * ret + s[i] - '0';
    return ret;
}
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    string s, ss, sss;
    cin >> s >> ss >> sss;
    __int128 x = parse(s);
    __int128 k = parse(ss);
    __int128 d = parse(sss);
    if (x < 0)
    {
        x = -x;
    }
    if (x > d * k)
    {
        x = x - d * k;
        cout << x << "\n";
    }
    else
    {
        __int128 ans = x % d;
        __int128 count = x / d;
        //cout<<ans<<" "<<count<<"\n";
        if ((k - count) % 2 == 0)
            cout << ans << "\n";
        else
            cout << d - ans << "\n";
    }
}