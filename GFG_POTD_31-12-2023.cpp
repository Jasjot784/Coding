// https://www.geeksforgeeks.org/problems/good-by-2023/1
int dp[366][2025];
    
    public:
    int rec(int i,int sum,int n,int c[]){
        if((sum)&&(!(sum%20)||!(sum%24)||sum==2024))
            return 1;
        if(i>=n||sum>2024)
            return 0;
        if(dp[i][sum]!=-1)return dp[i][sum];
        int ans1=rec(i+1,sum+c[i],n,c);
        int ans2=rec(i+1,sum,n,c);
        int ans=ans1|ans2;
        dp[i][sum]=ans;
        return ans;
        
    }
    int isPossible(int N , int coins[]) 
    {
        memset(dp,-1,sizeof(dp));
        return rec(0,0,N,coins);
    }
