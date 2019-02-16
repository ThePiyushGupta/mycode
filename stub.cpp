#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int Maxn = 100005;

int n;
ll tot;

int main()
{
    ll res[Maxn];
    for (int i = 2; i < Maxn; i++)
        for (int j = 2*i; j < Maxn; j += i)
            res[j] += j / i;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        tot += res[i];
    printf("%I64d\n", 4ll * tot);
    return 0;
}