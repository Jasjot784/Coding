//https://leetcode.com/problems/minimum-operations-to-sort-with-locked-indices/submissions/2186741155/
// A perfect prefix sum question which involves marking range by diff[l]++ and diff[r+1]--

 class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& locked, int k) {
        int n = nums.size();

        vector<int> diff(n + 1, 0);

        // Find all positions that must be unlocked
        for(int i = 0; i < n; i++) {
            int val = nums[i] - 1;

            if(val == i) continue;

            int l = min(i, val);
            int r = max(i, val);

            diff[l]++;
            diff[r + 1]--;
        }

        int opsun = 0;
        int cnt = 0;

        for(int i = 0; i < n; i++) {
            cnt += diff[i];

            if(cnt > 0 && locked[i] == 1) {
                opsun++;
            }
        }

        if(opsun > k) return -1;

        int opswp = 0;

for(int i = 0; i < n; i++) {
    for(int j = 0; j < n - 1; j++) {

        // If elements are in the wrong order
        if(nums[j] > nums[j + 1]) {

            // Swap adjacent elements
            swap(nums[j], nums[j + 1]);

            opswp++;
        }
    }
}

        return opsun + opswp;
    }
};
