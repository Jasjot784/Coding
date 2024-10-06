// https://leetcode.com/problems/sorted-gcd-pair-queries/
const int N = 5e4 + 2; // Define a constant for the maximum possible value + 2

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        // Preallocate arrays to store counts and prefix sums
        vector<long long> pre(N, 0);  // To count occurrences of each number
        vector<long long> cnt(N, 0);  // To count multiples of each number
        vector<long long> pref(N, 0); // To store the prefix sums of pairs with a specific GCD

        int n = (int)nums.size(); // Get the size of nums
        // Count the occurrences of each number in nums
        for(auto &x : nums) {
            pre[x]++; // Increment the count for the specific number
            cnt[x]++; // Count this number in cnt
        }

        // Calculate how many numbers are multiples of each integer
        for(int i = 2; i < N; i++) {          
            for(int j = 2 * i; j < N; j += i) { // For each multiple of i
                pre[i] += cnt[j]; // Add the count of j to the count of i
            }
        }

        long long total = 0; // Initialize a variable to store the total number of pairs
        // Calculate the number of pairs for each GCD
        for(int i = 2; i < N; i++) {
            pref[i] = (pre[i] * (pre[i] - 1)) / 2LL; // Calculate combinations of pairs for GCD i
        }

        // Adjust counts to account for higher multiples
        for(int i = N - 1; i >= 2; i--) {
            for(int j = 2 * i; j < N; j += i) { // For each multiple of i
                pref[i] -= pref[j]; // Subtract the counts of pairs that have GCD of multiples of i
            }
            total += pref[i]; // Accumulate the total pairs with GCD i
        }

        // Calculate the total pairs of elements in nums
        long long all = (n * 1LL * (n - 1)) / 2LL; // Total combinations of pairs from n elements
        pref[1] = all - total; // Store the pairs with GCD 1

        // Create a prefix sum for the counts of pairs for each GCD value
        for(int i = 1; i < N; i++) {
            pref[i] += pref[i - 1]; // Accumulate the counts
        }

        vector<int> ans; // Initialize the result vector
        int mx = *max_element(nums.begin(), nums.end()); // Find the maximum value in nums

        // Process each query
        for(auto &x : queries) {
            ++x; // Increment query value by 1 to accommodate the GCD = 1 case
            int l = 0; // Initialize left bound for binary search
            int r = mx; // Initialize right bound for binary search
            
            // Perform binary search to find the maximum GCD with at least x pairs
            while(r > l + 1) {
                int m = (l + r) >> 1; // Calculate the mid-point
                if(pref[m] >= x) { // If the number of pairs with GCD m is at least x
                    r = m; // Narrow down to the left half
                } else {
                    l = m; // Otherwise, narrow down to the right half
                }
            }
            ans.push_back(r); // Store the result for this query
        }
        return ans; // Return the answers for all queries
    }
};
