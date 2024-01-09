// https://www.geeksforgeeks.org/problems/longest-subarray-with-sum-divisible-by-k1259/1
int longSubarrWthSumDivByK(int arr[], int n, int k)
    {
        unordered_map<int,int>mp;
        mp.insert({0,-1});
        int ans=0,sum=0;
        for(int i=0;i<n;i++) {
            sum += arr[i];
            int rem = sum%k;
            if(rem<0) {
                rem += k;
            }
            if(mp.find(rem)==mp.end()) {
                mp.insert({rem,i});
            }
            else {
                ans = max(ans,i-mp[rem]);
            }
        }
        return ans;
    }
