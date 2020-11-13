vector<string> split(string str, char del) //delは区切りたい文字
{
    int first = 0;
    int last = str.find_first_of(del);

    vector<string> result;

    while (first < str.size())
    {
        string subStr(str, first, last - first);

        result.push_back(subStr);

        first = last + 1;
        last = str.find_first_of(del, first);

        if (last == string::npos)
        {
            last = str.size();
        }
    }
    if (str == result[0])
    {
        result.pop_back();
    }
    return result;
}