// https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/submissions/1437897276/?envType=daily-question&envId=2024-10-30
class Solution {
public:
    int minimumMountainRemovals(std::vector<int>& nums) {
        int n = nums.size();

        // Step 1: Compute the longest increasing subsequence (LIS) from the left
        std::vector<int> leftLIS(n, 1);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    leftLIS[i] = std::max(leftLIS[i], leftLIS[j] + 1);
                }
            }
        }

        // Step 2: Compute the longest decreasing subsequence (LDS) from the right
        std::vector<int> rightLDS(n, 1);
        for (int i = n - 2; i >= 0; --i) {
            for (int j = n - 1; j > i; --j) {
                if (nums[i] > nums[j]) {
                    rightLDS[i] = std::max(rightLDS[i], rightLDS[j] + 1);
                }
            }
        }

        // Step 3: Find the maximum length of a mountain
        int maxMountainLength = 0;
        for (int i = 1; i < n - 1; ++i) {
            if (leftLIS[i] > 1 && rightLDS[i] > 1) {
                maxMountainLength = std::max(maxMountainLength, leftLIS[i] + rightLDS[i] - 1);
            }
        }

        // Step 4: Return the number of removals
        return n - maxMountainLength;
    }
};
