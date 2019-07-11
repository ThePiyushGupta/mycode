#include <bits/stdc++.h>
using namespace std;
/* 
 *  ext_eucl(int a,int b)
 *      if(b==0)        return (1,0);
 *      x_p,y_p = ext_excl(b,a%b)
 *      X=y_p
 *      Y=x_p-floor(a/b)y_p
 *      return (X,Y)     
 *     
 *  modular_inverse( b,M):
 *      x,y = ext_eucl(b,M)
 *      X = (Y+M)%M
 *      return X;
 */

long long inv(long long a, long long b) {
	return 1 < a ? b - inv(b % a, a) * b / a : 1;
}


void modular_inverse(b,M){
    
}