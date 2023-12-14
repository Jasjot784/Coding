// https://www.geeksforgeeks.org/problems/painting-the-fence3727/1
long long countWays(int n, int k){
        // code here
        long long s=k;
        if(n==1)return k;
        long long b[n];
        long long mod=1e9+7;
        b[0]=s;b[1]=(k*s)%mod;
        for(int i=2;i<n;i++)
        {
         b[i]=((b[i-1]%mod+b[i-2]%mod)*(s-1))%mod;
        }
        return b[n-1]%mod;
    }
