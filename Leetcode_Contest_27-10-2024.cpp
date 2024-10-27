// https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/description/
class Solution {
public:
    int dp[201][201][201];
    int MOD = 1e9 + 7;

    int rec(int i, int s1, int s2, std::vector<int>& a) {
        if (i >= a.size()) {
            return (s1 == s2 && s1 > 0) ? 1 : 0; 
        }
        if (dp[i][s1][s2] != -1) return dp[i][s1][s2];

        long long ans = 0;
        ans = (rec(i + 1, std::gcd(a[i], s1), s2, a) + rec(i + 1, s1, std::gcd(s2, a[i]), a)) % MOD;
        ans = (ans+rec(i+1,s1,s2,a))%MOD;
        return dp[i][s1][s2] = ans;
    }

    int subsequencePairCount(std::vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        int x =  rec(0, 0, 0, nums);
        return x;
        
        
    }
};
