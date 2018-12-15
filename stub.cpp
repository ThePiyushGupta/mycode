// ABHISHEK JAISWAL
#include <bits/stdc++.h>
#include <math.h>
#include <string>

using namespace std;

typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll n;
    cin >> n;

    ll arr0[n + 1];

    for (ll i = 1; i < n + 1; i++) {
        cin >> arr0[i];
    }

    ll arr1[n];
    ll arr2[n];
    ll arr3[n];

    for (ll i = 1; i < n; i++) {

        cin >> arr1[i] >> arr2[i] >> arr3[i];
    }

    for (ll i = 1; i < n; i++) {
        arr3[i] = arr0[arr1[i]] + arr0[arr2[i]] - arr3[i];
    }

    ll max_index = 1;

    for (ll i = 1; i < n; i++) {
        if (arr3[i] > arr3[max_index])
            max_index = i;
    }

    ll a = arr1[max_index];
    ll b = arr2[max_index];

    ll ans = arr3[max_index];
    ll add = 0;

    for (ll i = 1; i < n; i++) {
        if (i == max_index)
            continue;

        if (arr1[i] == a) {
            add = (add > (arr3[i] - arr0[a])) ? add : (arr3[i] - arr0[a]);
        } else if (arr1[i] == b) {
            add = (add > (arr3[i] - arr0[b])) ? add : (arr3[i] - arr0[b]);
        } else if (arr2[i] == a) {
            add = (add > (arr3[i] - arr0[a])) ? add : (arr3[i] - arr0[a]);
        } else if (arr2[i] == b) {
            add = (add > (arr3[i] - arr0[b])) ? add : (arr3[i] - arr0[b]);
        }
    }

    cout << ans + add << endl;

    return 0;
}