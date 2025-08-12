/*A number is called boring if all digits at even pos are even and all digits at odd pos are odd.
Given L and R,find how many boring numbers are there in [L,R]*/
#include<bits/stdc++.h>
using namespace std;
long long int Countnumbers(string &s,int N,int pos,bool tight,vector<vector<vector<long long int>>>&dp){
    if(N==0){
        if(pos!=0)
            return 1LL;
        return 0LL;
    }
    if(dp[N][pos][tight]!=-1){
        return dp[N][pos][tight];
    }
    int sz=s.size();
    int ub=tight?s[sz-N]-'0':9;
    long long int ans=0;
    if(pos%2){
        for(int digit=0;digit<=ub;digit+=2){
            ans+=Countnumbers(s,N-1,pos+1,tight&(digit==ub),dp);
        }
    }
    else{
        if(pos==0){
            ans+=Countnumbers(s,N-1,0,0,dp);
        }
        for(int digit=1;digit<=ub;digit+=2){
            ans+=Countnumbers(s,N-1,pos+1,tight&(digit==ub),dp);
        }
    }
    return dp[N][pos][tight]=ans;
}
int main(){
    long long int L,R;
    cin>>L>>R;
    L--;
    string num1=to_string(R);
    string num2=to_string(L);
    vector<vector<vector<long long int>>>dp1(30,vector<vector<long long int>>(30,vector<long long int>(2,-1)));
    vector<vector<vector<long long int>>>dp2(30,vector<vector<long long int>>(30,vector<long long int>(2,-1)));
    cout<<Countnumbers(num1,num1.size(),0,1,dp1)-Countnumbers(num2,num2.size(),0,1,dp2)<<endl;
}