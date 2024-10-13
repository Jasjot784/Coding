// https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/?envType=daily-question&envId=2024-10-13

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        int currentMax = numeric_limits<int>::min();

        // Step 1: Push the first element of each list into the priority queue
        for (int i = 0; i < nums.size(); i++) {
            pq.push({nums[i][0], i}); // Push each number with its list index
            currentMax = max(currentMax, nums[i][0]); // Update currentMax
        }

        vector<int> result = {0, 0}; // To store the smallest range
        int minRange = numeric_limits<int>::max();
        vector<int> indices(nums.size(), 0); // To track the index of elements from each list

        // Step 2: Process the priority queue
        while (true) {
            int currentMin = pq.top().first; // Get the current minimum
            int listIndex = pq.top().second;  // Get the list index
            pq.pop();

            // Step 3: Update the range if we have one element from each list
            if (pq.size() + 1 == nums.size()) {
                // Update the range if the current range is smaller
                if (currentMax - currentMin < minRange) {
                    minRange = currentMax - currentMin;
                    result = {currentMin, currentMax};
                }
            }

            // Move to the next element in the same list
            indices[listIndex]++;
            if (indices[listIndex] < nums[listIndex].size()) {
                int nextVal = nums[listIndex][indices[listIndex]];
                pq.push({nextVal, listIndex});
                currentMax = max(currentMax, nextVal); // Update currentMax if necessary
            } else {
                // If we run out of elements in any list, we can stop
                break;
            }
        }
        
        return result;
    }
};
