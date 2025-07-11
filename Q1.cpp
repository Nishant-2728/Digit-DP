/*Find count of numbers in the range [0,R] such that 
sum pf digits is X.
1<=L<=R<=1e18,1<=X<=180*/
#include<bits/stdc++.h>
using namespace std;
long long int Count(string &num,int N,int X,bool tight,vector<vector<vector<long long int>>>&dp){
    if(X<0){
        return 0LL;
    }
    if(N==0){
        if(X>=0)
            return 1LL;
        return 0LL;
    }
    if(dp[N][X][tight]!=-1){
        return dp[N][X][tight];
    }
    int ub=tight?num[num.size()-N]-'0':9;
    long long int ans=0;
    for(int digit=0;digit<=ub;digit++){
        ans+=Count(num,N-1,X-digit,tight&(digit==ub),dp);
    }
    return dp[N][X][tight]=ans;
}
int main(){
    string R;
    cin>>R;
    int X;
    cin>>X;
    vector<vector<vector<long long int>>>dp(100,vector<vector<long long int>>(181,vector<long long int>(2,-1)));
    cout<<Count(R,R.size(),X,1,dp)<<endl;
}