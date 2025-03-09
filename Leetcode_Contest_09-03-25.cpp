// https://leetcode.com/problems/choose-k-elements-with-maximum-sum/
class Solution {
public:
    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        vector<long long> ans(n, 0);
        vector<pair<int, int>> p;
        
        // Store (nums1[i], index i) in a vector to sort based on nums1[i]
        for (int i = 0; i < n; i++) {
            p.push_back({nums1[i], i});
        }
        
        // Sort based on nums1 values
        sort(p.begin(), p.end());
        
        multiset<long long> ms; // Stores the k largest nums2 values encountered
        long long sum = 0; // Running sum of k largest nums2 values
        int le = 0;
        
        // Iterate through sorted nums1 values
        for (int i = 0; i < n; i++) {
            int a = p[i].first; // Current nums1 value
            int ind = p[i].second; // Original index in nums1
            
            // Process elements before index i whose nums1 values are smaller
            while (le < i && p[le].first < a) {
                long long val = nums2[p[le].second];
                
                if (ms.size() < k) { // If we have room, add it
                    sum += val;
                    ms.insert(val);
                } else if (*ms.begin() < val) { // Replace the smallest element if a larger one is found
                    sum -= *ms.begin();
                    ms.erase(ms.begin());
                    ms.insert(val);
                    sum += val;
                }
                le++;
            }
            
            ans[ind] = sum; // Store the maximum sum for the current index
        }
        
        return ans;
    }
};
