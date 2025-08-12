/*For a pair of integers a and b, the digit sum of the interval [a,b] is defined as sum
of all the digits ocurring in all numbers between a and b*/
#include<bits/stdc++.h>
using namespace std;
long long int powi(long long int x,long long int n){
    long long int ans=1;
    while(n){
        if(n%2==0){
            x=(x*x);
            n/=2;
        }
        else{
            ans=(ans*x);
            n--;
        }
    }
    return ans;
}
long long int cnt(string &s,int N,bool tight){
    if(tight==0){
        return powi(10LL,N);
    }
    if(N==0){
        return 1LL;
    }
    long long int num=0;
    int ub=tight?s[s.size()-N]-'0':9;
    for(int dig=0;dig<=ub;dig++){
        num+=cnt(s,N-1,tight&(dig==ub));
    }
    return num;
}
long long int solve(string &s,int N,bool tight,vector<vector<long long int>>&dp){
    if(N==0){
        return 0LL;
    }
    if(dp[N][tight]!=-1){
        return dp[N][tight];
    }
    int ub=tight?s[s.size()-N]-'0':9;
    long long int total=0;
    for(int dig=0;dig<=ub;dig++){
        total+=dig*cnt(s,N-1,tight&(dig==ub))+solve(s,N-1,tight&(dig==ub),dp);
    }
    return dp[N][tight]=total;
}
int main(){
    long long int L,R;
    cin>>L>>R;
    if(L){
        L--;
    }
    string num1=to_string(R);
    string num2=to_string(L);
    vector<vector<long long int>>dp1(20,vector<long long int>(2,-1));
    vector<vector<long long int>>dp2(20,vector<long long int>(2,-1));
    long long int sodR=solve(num1,num1.size(),1,dp1);
    long long int sodL=solve(num2,num2.size(),1,dp2);
    cout<<sodR-sodL<<endl;
}