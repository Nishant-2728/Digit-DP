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
        if(X==0)
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
    int sum;
    cin>>sum;
    vector<vector<vector<long long int>>>dp(100,vector<vector<long long int>>(181,vector<long long int>(2,0)));
    dp[0][0][1]=1LL;
    for(int sz=0;sz<R.size();sz++){
        for(int X=0;X<=sum;X++){
            for(int tight=0;tight<2;tight++){
                int ub=tight?(R[sz]-'0'):9;
                for(int digit=0;digit<=ub;digit++){
                    if(X+digit<=sum){
                        dp[sz+1][X+digit][tight&(digit==ub)]+=dp[sz][X][tight];
                    }
                }
            }
        }
    }
    cout<<dp[R.size()][sum][1]+dp[R.size()][sum][0]<<endl;
}