// https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/description/?envType=daily-question&envId=2024-09-22
class Solution {
public:
    void dfs(int temp, int n, vector<int> &ans){
        if (temp > n){
            return;
        }

        ans.push_back(temp);
        dfs(temp * 10, n, ans);

        if (temp % 10 != 9){
            dfs(temp + 1, n, ans);
        }
    }
    int findKthNumber(int n, int k) {
        vector<int> ans;
        dfs(1, n, ans);
        return ans[k-1];
    }
};
