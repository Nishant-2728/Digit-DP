/*Given L and R with NL and NR digits respectively.Find sum of f(x) for
each x b/w L and R inclusive
where f(x) is defined as follows"
Consider the decimal representation of x.Split it into min number of contiguous subsequences
of digits such that in each subsequences all digits are identical.
f(388,822,442)=3*10^8+8*10^7+2*10^4+4*10^2+2*10^0*/
#include<bits/stdc++.h>
using namespace std;
const long long int M=1e9+7;
long long int powi(long long int x,long long int n){
    long long int ans=1LL;
    while(n){
        if(n%2==0){
            x=(x*x)%M;
            n/=2;
        }
        else{
            ans=(ans*x)%M;
            n--;
        }
    }
    return ans;
}
long long int cnt(string &s,int N,bool tight,vector<vector<long long int>>&cntdp){
    if(tight==0){
        return powi(10LL,N);
    }
    if(N==0){
        return 1LL;
    }
    if(cntdp[N][tight]!=-1){
        return cntdp[N][tight];
    }
    int ub=s[s.size()-N]-'0';
    long long int count=0;
    for(int dig=0;dig<=ub;dig++){
        count=(count+cnt(s,N-1,dig==ub,cntdp))%M;
    }
    return cntdp[N][tight]=count%M;
}
long long int Countnumbers(string &s,int N,bool tight,int prev,vector<vector<vector<long long int>>>&dp,vector<vector<long long int>>&cntdp){
    if(N==0){
        return 0;
    }
    if(dp[N][prev][tight]!=-1){
        return dp[N][prev][tight];
    }
    int ub=tight?s[s.size()-N]-'0':9;
    long long int ans=0;
    for(int dig=0;dig<=ub;dig++){
        if(dig!=prev){
            long long int contri=(dig*powi(10LL,N-1)*cnt(s,N-1,tight&(dig==ub),cntdp))%M;
            ans=(ans+contri)%M;
        }
        ans=(ans+Countnumbers(s,N-1,tight&(dig==ub),dig,dp,cntdp))%M;
    }
    return dp[N][prev][tight]=ans%M;
}
long long int bruteforce(string &s,int N){
    int prev=10;
    long long int res=0;
    for(int j=0;j<N;j++){
        if((s[j]-'0')!=prev){
            res=(res+(s[j]-'0')*powi(10LL,s.size()-j-1))%M;
        }
        prev=s[j]-'0';
    }
    return res%M;
}
int main(){
    int NL,NR;
    cin>>NL>>NR;
    string L,R;
    cin>>L>>R;
    vector<vector<vector<long long int>>>dp1(NR+5,vector<vector<long long int>>(11,vector<long long int>(2,-1)));
    vector<vector<long long int>>cntdp1(NR+5,vector<long long int>(2,-1));
    vector<vector<vector<long long int>>>dp2(NL+5,vector<vector<long long int>>(11,vector<long long int>(2,-1)));
    vector<vector<long long int>>cntdp2(NL+5,vector<long long int>(2,-1));
    long long int ans=Countnumbers(R,NR,1,10,dp1,cntdp1)%M;
    ans=(ans-Countnumbers(L,NL,1,10,dp2,cntdp2)+M)%M;
    ans=(ans+bruteforce(L,NL))%M;
    cout<<ans<<endl;
}