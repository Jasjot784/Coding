// https://leetcode.com/problems/count-non-decreasing-subarrays-after-k-operations/?slug=count-non-decreasing-subarrays-after-k-operations&region=global_v2
class Solution {
public:
    // The function countNonDecreasingSubarrays takes an array `nums` and an integer `k`
    // It returns the count of non-decreasing subarrays whose total number of distinct elements
    // is less than or equal to `k`.
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        // Create a copy of the original nums array to hold the necessary values
        vector<int> need = nums;
        
        // Get the size of the input array
        int n = nums.size();
        
        // Preprocessing step to fill the `need` array with values such that:
        // need[i] stores the number of steps by which the previous number needs to be decreased
        // in order for the sequence to remain non-decreasing.
        for (int i = 1; i < n; i++) {
            need[i] = max(0, nums[i - 1] - nums[i]);
        }
        
        // `pt` is a pointer used to manage the window of the subarray
        int pt = n - 1;
        
        // `cur` stores the current total number of distinct elements in the sliding window
        long long cur = 0;
        
        // `res` will store the final result, i.e., the number of non-decreasing subarrays
        long long res = 0;
        
        // `c` is a map to count the frequency of each element in the current window
        map<int, int> c;
        
        // Iterate through the array from right to left
        for (int i = n - 1; i >= 0; i--) {
            
            // If there are elements in the map and the first element in the map is less than `nums[i]`
            // it means we need to add those elements to the current subarray.
            while (!c.empty() && c.begin()->first < nums[i]) {
                // Add the frequency of elements from the map to the current count `cur`
                cur += 1ll * (nums[i] - c.begin()->first) * c.begin()->second;
                
                // Add the current element `nums[i]` into the map and update its frequency
                c[nums[i]] += c.begin()->second;
                
                // Remove the smallest element in the map since it's no longer useful
                c.erase(c.begin());
            }
            
            // Increment the frequency of `nums[i]` in the map
            c[nums[i]]++;
            
            // If the current number of distinct elements exceeds `k`, reduce the window from the left
            while (cur > k) {
                // Remove the difference from `cur` by moving the `pt` pointer
                cur -= c.rbegin()->first - nums[pt--];
                
                // Decrement the frequency of the element at the rightmost end
                if (--(c.rbegin()->second) == 0) {
                    // If the frequency becomes 0, remove the element from the map
                    c.erase(c.rbegin()->first);
                }
            }
            
            // Add the current valid subarrays count (from index i to pt) to the result
            res += pt - i + 1;
        }
        
        // Return the total number of valid subarrays found
        return res;
    }
};
