#include <iostream>

using namespace std;

int main() {
    int n;
    cin>>n;
    here:
    for(int c = 2; c < 10; c++){
        if (n%c==0){
            while(n>0){cout<<c<<' ';n-=c;}
            return 0;
        }
    }
    cout<<1<<' ';n--;goto here;
}