#include <bits/stdc++.h>
#include <stack>

using namespace std;

int main()
{

    int n, m = 0, f = 1;
    cin >> n;
    int a[n], b[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    if (b[n - 1])
    {
        for (int i = 0; i < b[n - 1]; i++)
            if (b[n - 1 - i] != b[n - 1] - i)
            {
                f = 0;
                break;
            }
    }
    //cout<<n;
    for (int i = 0; i < n; i++)
    {
        if (b[i] > 0)
        {
            if (i + 2 + n - b[i] > m)
                m = i + 2 + n - b[i];
        }
    }
    //cout<<m<<endl;
    if (f)
    {
        for (int i = 0; i < n - b[n - 1]; i++)
        {
            if (i + 1 >= b[i] - b[n - 1] && (b[i]))
            {
                cout << m;
                return 0;
            }
        }
        cout << n - b[n - 1];
    }
    else
        cout << m;
    return 0;
}