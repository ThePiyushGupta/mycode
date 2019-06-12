#include <iostream>

using namespace std;

int main() {
    ll n,m;
    cin>>n>>m;
    int res=0;
    while(m%2==0){
        res++;
        m/=2;

    }
    while (m % 3 == 0)
    {
        res++;
        m/= 3;
    }
    while (n % 2 == 0)
    {
        res--;
        n /= 2;
    }
    while (m % 3 == 0)
    {
        res--;
        n /= 3;
    }
    if(m!=n||res<0)
}