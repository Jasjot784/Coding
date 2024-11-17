// https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/?envType=daily-question&envId=2024-11-17
class Solution {
public:
    int shortestSubarray(std::vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<long long> prefix(n + 1, 0);

        // Compute the prefix sum
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        // Monotonic deque (stores indices of the prefix sums)
        std::deque<int> dq;
        int ans = INT_MAX;

        // Iterate over all prefix sums
        for (int i = 0; i <= n; i++) {
            // Check if we can find a valid subarray
            while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
                ans = std::min(ans, i - dq.front());
                dq.pop_front(); // Remove the index from the deque
            }

            // Maintain a monotonic deque by removing indices of prefix sums
            // that are greater than the current prefix[i]
            while (!dq.empty() && prefix[i] <= prefix[dq.back()]) {
                dq.pop_back();
            }

            // Add the current index to the deque
            dq.push_back(i);
        }

        // If no valid subarray is found, return -1
        return ans == INT_MAX ? -1 : ans;
    }
};
